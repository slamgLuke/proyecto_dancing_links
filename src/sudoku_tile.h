#include "definitions.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

struct Vec2d {
    int x;
    int y;

    Vec2d() : x(0), y(0) {}
    Vec2d(int x, int y) : x(x), y(y) {}
    Vec2d(const Vec2d& v) : x(v.x), y(v.y) {}
    Vec2d& operator=(const Vec2d& v) {
        x = v.x;
        y = v.y;
        return *this;
    }

    Vec2d sprite_pos() { // convert index to sprite position
        int x_offset = x / LINE_POS * LINE_THICKNESS;
        int y_offset = y / LINE_POS * LINE_THICKNESS;

        return Vec2d(x * TILE_SIZE + x_offset, y * TILE_SIZE + y_offset);
    }

    Vec2d index() { // convert sprite position to index
        int x_offset = (x / (LINE_POS * TILE_SIZE)) * LINE_THICKNESS;
        int y_offset = (y / (LINE_POS * TILE_SIZE)) * LINE_THICKNESS;

        int x_index = (x - x_offset) / TILE_SIZE;
        int y_index = (y - y_offset) / TILE_SIZE;

        return Vec2d(x_index, y_index);
    }
};

struct Tile {
    int value;
    Vec2d pos;
    sf::Text text;
    sf::Sprite sprite;

    static sf::Font font;
    static bool isFontLoaded;
    static sf::Texture texture;
    static bool isTextureLoaded;

    Tile() {
        static sf::Font font;
        static bool isFontLoaded = false;
        static sf::Texture texture;
        static bool isTextureLoaded = false;

        value = 0;
        pos = Vec2d();
        text = sf::Text();
        sprite = sf::Sprite();
    }

    Tile (int x, int y) : pos(Vec2d(x, y)) {
        static sf::Font font;
        static bool isFontLoaded = false;
        static sf::Texture texture;
        static bool isTextureLoaded = false;

        value = 0;
        text = sf::Text();
        sprite = sf::Sprite();

        Vec2d sprite_pos = pos.sprite_pos();

        if (!isFontLoaded) {
            if (!font.loadFromFile("assets/Boxy-Bold.ttf")) {
                throw std::runtime_error("Error loading font");
            } else {
                isFontLoaded = true;
            }
        }
        text.setFont(font);
        text.setString(DEFAULT);
        text.setCharacterSize(50);
        text.setFillColor(sf::Color::Black);
        text.setPosition(sprite_pos.x + TILE_SIZE/6, sprite_pos.y + TILE_SIZE/30);

        if (!isTextureLoaded) {
            if (!texture.loadFromFile("assets/Sudoku-Tile.png")) {
                throw std::runtime_error("Error loading texture");
            } else {
                isTextureLoaded = true;
            }
        }
        sprite.setTexture(texture);
        sprite.setPosition(sprite_pos.x, sprite_pos.y);
    }

    void setValue(int val) {
        value = val;
        if (val == 0) {
            text.setString(DEFAULT);
        } else {
            text.setString(to_string(val));
        }

    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
        window.draw(text); 
    }

};
