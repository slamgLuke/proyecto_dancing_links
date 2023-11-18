#include "sudoku_tile.h"
#include "definitions.h"
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

struct HUD {
    sf::RectangleShape* bg;
    sf::Text placeholder;
    sf::Text algorithm;
    int selector = 1;
    static sf::Font font;

    void color_set(sf::Color hue) {
        int min_r = hue.r - 10;
        int min_g = hue.g - 10;
        int min_b = hue.b - 10;

        for (int i = FADE_NUM - 1; i >= 0; i--) {
            bg[i] = sf::RectangleShape(sf::Vector2f(HUD_WIDTH - i * 2 * FADE_WIDTH, HUD_HEIGHT - i * 2 * FADE_WIDTH));
            bg[i].setFillColor(hue);
            bg[i].setPosition(0 + i * FADE_WIDTH, HUD_POS + i * FADE_WIDTH);
            hue.r -= min_r / FADE_NUM;
            hue.g -= min_g / FADE_NUM;
            hue.b -= min_b / FADE_NUM;
        }
    }

    HUD() {
        bg = new sf::RectangleShape[FADE_NUM];
        color_set(sf::Color(0xBF40BFFF));

        static sf::Font font;
        if (!font.loadFromFile("assets/Boxy-Bold.ttf")) {
            throw std::runtime_error("Error loading font");
        }
        placeholder = sf::Text();
        placeholder.setFont(font);
        placeholder.setString(PLACEHOLDER);
        placeholder.setCharacterSize(24);
        placeholder.setFillColor(sf::Color::Black);
        placeholder.setPosition(30, HUD_POS + 24);

        algorithm = sf::Text();
        algorithm.setFont(font);
        algorithm.setString("DLX");
        algorithm.setCharacterSize(24);
        algorithm.setFillColor(sf::Color::Black);
        algorithm.setPosition(HUD_WIDTH - 96, HUD_POS + 96);
    }

    void change_algorithm(int _selector) {
        selector = _selector;
        switch (selector) {
            case 1:
                algorithm.setString("DLX");
                algorithm.setPosition(HUD_WIDTH - 96, HUD_POS + 96);
                color_set(sf::Color(0xBF40BFFF));
                break;
            case 2:
                algorithm.setString("Backtracking");
                algorithm.setPosition(HUD_WIDTH - 96*2.75, HUD_POS + 96);
                color_set(sf::Color(0xB9FF66FF));
                break;
            default:
                selector = 1;
                algorithm.setString("DLX");
                algorithm.setPosition(HUD_WIDTH - 96, HUD_POS + 96);
                color_set(sf::Color(0xBF40BFFF));
                break;
        }
    }

    void draw(sf::RenderWindow& window) {
        for (int i = 0; i < FADE_NUM; i++) {
            window.draw(bg[i]);
        }
        window.draw(placeholder);
        window.draw(algorithm);
    }
};

