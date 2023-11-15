#define TILE_SIZE 64
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

struct Vec2d {
    int x;
    int y;

    Vec2d() : x(0), y(0) {}
    Vec2d(int x, int y) : x(x), y(y) {}
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

        if (!isFontLoaded) {
            if (!font.loadFromFile("assets/Boxy-Bold.ttf")) {
                throw std::runtime_error("Error loading font");
            } else {
                isFontLoaded = true;
            }
        }
        text.setFont(font);
        text.setString(" ");
        text.setCharacterSize(50);
        text.setColor(sf::Color::Black);
        text.setPosition(pos.x * TILE_SIZE + 15, pos.y * TILE_SIZE + 5);

        if (!isTextureLoaded) {
            if (!texture.loadFromFile("assets/Sudoku-Tile.png")) {
                throw std::runtime_error("Error loading texture");
            } else {
                isTextureLoaded = true;
            }
        }
        sprite.setTexture(texture);
        sprite.setPosition(pos.x * TILE_SIZE, pos.y * TILE_SIZE);
    }

    void setValue(int val) {
        value = val;
        if (val == 0) {
            text.setString(" ");
        } else {
            text.setString(to_string(val));
        }

    }

    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
        window.draw(text); 
    }

};
