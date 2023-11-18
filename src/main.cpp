#include "sudoku_visual.h"
#include "algorithms.h"
#include <optional>
#include <thread>

using namespace std;

Vec2d getMouseCoords(sf::RenderWindow& window) {
    auto mousePos = sf::Mouse::getPosition(window);
    auto translatedPos = window.mapPixelToCoords(mousePos);
    Vec2d output = Vec2d(translatedPos.x, translatedPos.y).index();
    return output;
}

void solve(bool* is_solving) {
    SudokuVisual& sudoku = SudokuVisual::getInstance();
    int** matrix = sudoku.export_matrix();
    sudoku.start_timer();
    if (sudoku.get_algorithm() == 1) {
        auto dlx = dlx_solve(matrix);
    } else {
        auto brute = brute_force_solve(matrix);
    }
    sudoku.stop_timer();

    for (int i = 0; i < SUDOKU_SIZE; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    cout << "DONE!" << endl;
    *is_solving = false;
}

int main() {
    cout << "Hello!" << endl;

    optional<Vec2d> awaitingTile = nullopt;
    SudokuVisual& sudoku = SudokuVisual::getInstance();

    thread solving_thread;
    bool is_solving = false;

    auto window = sf::RenderWindow{{WINDOW_WIDTH, WINDOW_HEIGHT}, "Sudoku DLx Solver"};
    window.setFramerateLimit(144);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // mouse handling
            if (event.type == sf::Event::MouseButtonPressed && !is_solving) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    Vec2d mousePos = getMouseCoords(window);
                    if (mousePos.x < 9 && mousePos.y < 9) {
                        if (awaitingTile) {
                            sudoku.getTile(awaitingTile.value()).text.setFillColor(sf::Color::Black);
                        }
                        awaitingTile = mousePos;
                        sudoku.getTile(mousePos).text.setFillColor(sf::Color::Red);
                    }
                }
            }

            // change number
            if (event.type == sf::Event::TextEntered) {
                if (awaitingTile) {
                    if (event.text.unicode >= '0' && event.text.unicode <= '9') {
                        sudoku.getTile(awaitingTile.value()).text.setFillColor(sf::Color::Black);
                        sudoku.getTile(awaitingTile.value()).setValue(event.text.unicode - '0');
                        awaitingTile = nullopt;
                    }
                }
            }

            // keyboard handling
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                } else if (!is_solving) {
                    if (event.key.code == sf::Keyboard::Space) {
                        is_solving = true;
                        sudoku.change_string(EXECUTING);
                        // solve in a new thread
                        if (!solving_thread.joinable()) {
                            solving_thread = thread(solve, &is_solving);
                        }
                    }
                    if (event.key.code == sf::Keyboard::BackSpace) {
                        sudoku.clear();
                    }
                    if (event.key.code == sf::Keyboard::D) {
                        sudoku.change_algorithm(1);
                    }
                    if (event.key.code == sf::Keyboard::B) {
                        sudoku.change_algorithm(2);
                    }
                }
            }
        }
        if (!is_solving && solving_thread.joinable()) {
            solving_thread.join();
            sudoku.change_string(PLACEHOLDER);
        }

        window.clear();
        sudoku.draw(window);
        window.display();
    }

    if (solving_thread.joinable()) {
        solving_thread.join();
    }

    cout << "Bye!" << endl;

    return 0;
}
