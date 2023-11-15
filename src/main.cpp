#include "sudoku_visual.h"

using namespace std;

Vec2d getMouseCoords(sf::RenderWindow& window) {
    auto mousePos = sf::Mouse::getPosition(window);
    auto translatedPos = window.mapPixelToCoords(mousePos);
    Vec2d output = Vec2d(translatedPos.x / TILE_SIZE, translatedPos.y / TILE_SIZE);
    return output;
}

int main() {
    auto& sudoku = SudokuVisual::getInstance();

    auto window = sf::RenderWindow{{TILE_SIZE * 9, TILE_SIZE * 12}, "Sudoku DLx Solver"};
    window.setFramerateLimit(144);

    while (window.isOpen()) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    Vec2d mousePos = getMouseCoords(window);
                    sudoku.setTile(mousePos.x, mousePos.y, 1);
                }
            }
        }


        window.clear();
        sudoku.draw(window);
        window.display();
    }
}
