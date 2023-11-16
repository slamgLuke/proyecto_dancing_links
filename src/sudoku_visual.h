#pragma once

#include "sudoku_tile.h"

using namespace std;

// Singleton Visual Class
class SudokuVisual {
   private:
    static SudokuVisual instance;
    Tile** matrix;

    SudokuVisual() {
        matrix = new Tile*[SUDOKU_SIZE];
        for (int x = 0; x < SUDOKU_SIZE; x++) {
            matrix[x] = new Tile[SUDOKU_SIZE];
            for (int y = 0; y < SUDOKU_SIZE; y++) {
                matrix[x][y] = Tile(x, y);
            }
        }
    }
    SudokuVisual(const SudokuVisual&) = delete;
    SudokuVisual& operator=(const SudokuVisual&) = delete;

   public:
    static SudokuVisual& getInstance() {
        static SudokuVisual instance;  // Inicializado solo una vez
        return instance;
    }

    void setTile(int x, int y, int val) { matrix[x][y].setValue(val); }
    Tile& getTile(Vec2d pos) { return matrix[pos.x][pos.y]; }

    void clear() {
        for (int x = 0; x < SUDOKU_SIZE; x++) {
            for (int y = 0; y < SUDOKU_SIZE; y++) {
                matrix[x][y].setValue(0);
            }
        }
    }

    void draw(sf::RenderWindow& window) {
        for (int x = 0; x < SUDOKU_SIZE; x++) {
            for (int y = 0; y < SUDOKU_SIZE; y++) {
                matrix[x][y].draw(window);
            }
        }
    }

    int** export_matrix() {
        int** output = new int*[SUDOKU_SIZE];
        for (int x = 0; x < SUDOKU_SIZE; x++) {
            output[x] = new int[SUDOKU_SIZE];
            for (int y = 0; y < SUDOKU_SIZE; y++) {
                output[x][y] = matrix[x][y].value;
            }
        }
        return output;
    }
};
