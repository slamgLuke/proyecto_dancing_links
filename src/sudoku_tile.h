#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

struct Tile {
    string value;
    sf::Sprite sprite;
    sf::Text text;

    Tile() {
        value = " ";
    }

    void draw(sf::RenderWindow& window) {
        // todo!()
    }

};
