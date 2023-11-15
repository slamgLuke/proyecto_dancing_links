#pragma once

#include "sudoku_tile.h"

using namespace std;

// Singleton Visual Class
class SudokuVisual {
   private:
    static SudokuVisual instance;
    int size;
    Tile** matrix;

    SudokuVisual(int _size) : size(_size) {
        matrix = new Tile*[size];
        for (int x = 0; x < size; x++) {
            matrix[x] = new Tile[size];
            for (int y = 0; y < size; y++) {
                matrix[x][y] = Tile(x, y);
            }
        }
    }
    SudokuVisual(const SudokuVisual&) = delete;
    SudokuVisual& operator=(const SudokuVisual&) = delete;

   public:
    static SudokuVisual& getInstance() {
        static SudokuVisual instance(9);  // Inicializado solo una vez
        return instance;
    }

    void setTile(int x, int y, int val) { matrix[x][y].setValue(val); }
    Tile& getTile(int x, int y) { return matrix[x][y]; }

    void draw(sf::RenderWindow& window) {
        for (int x = 0; x < size; x++) {
            for (int y = 0; y < size; y++) {
                matrix[x][y].draw(window);
            }
        }
    }
};
