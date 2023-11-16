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

void solve(bool compare) {
    SudokuVisual& sudoku = SudokuVisual::getInstance();
    int** matrix = sudoku.export_matrix();

    auto dlx = dlx_solve(matrix);
    auto brute = brute_force_solve(matrix);
    if (compare) { 
        compare_result(dlx, brute);
    }

    for (int i = 0; i < SUDOKU_SIZE; i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

int main() {
    optional<Vec2d> awaitingTile = nullopt;
    SudokuVisual& sudoku = SudokuVisual::getInstance();

    thread solving_thread;
    bool compare = false;
    bool is_solving = false;

    unsigned int window_width = TILE_SIZE * 9 + LINE_THICKNESS * 2;
    unsigned int window_height = TILE_SIZE * 12 + LINE_THICKNESS * 2;
    auto window = sf::RenderWindow{{window_width, window_height}, "Sudoku DLx Solver"};
    window.setFramerateLimit(144);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // mouse handling
            if (event.type == sf::Event::MouseButtonPressed) {
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
                }
                if (event.key.code == sf::Keyboard::Space) {
                    is_solving = true;
                    // solve in a new thread
                    if (!solving_thread.joinable()) {
                        solving_thread = thread(solve, compare);
                    }
                }
                if (event.key.code == sf::Keyboard::BackSpace) {
                    sudoku.clear();
                }
                if (event.key.code == sf::Keyboard::C) {
                    compare = !compare;
                }
            }
        }

        window.clear();
        sudoku.draw(window);
        window.display();
    }

    if (solving_thread.joinable()) {
        solving_thread.join();
    }

    return 0;
}
