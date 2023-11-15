#include "sudoku_visual.h"
#include <optional>

using namespace std;

Vec2d getMouseCoords(sf::RenderWindow& window) {
    auto mousePos = sf::Mouse::getPosition(window);
    auto translatedPos = window.mapPixelToCoords(mousePos);
    Vec2d output = Vec2d(translatedPos.x / TILE_SIZE, translatedPos.y / TILE_SIZE);
    return output;
}

int main() {
    optional<Vec2d> awaitingTile = nullopt;
    SudokuVisual& sudoku = SudokuVisual::getInstance();

    auto window = sf::RenderWindow{{TILE_SIZE * 9, TILE_SIZE * 12}, "Sudoku DLx Solver"};
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
                    // sudoku.solve();
                }
                if (event.key.code == sf::Keyboard::BackSpace) {
                    sudoku.clear();
                }
            }
        }

        window.clear();
        sudoku.draw(window);
        window.display();
    }
}
