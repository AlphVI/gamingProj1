//
// Created by zjchr on 11/12/2023.
//

#ifndef CMAKESFMLPROJECT_GAME_HPP
#define CMAKESFMLPROJECT_GAME_HPP

#include <queue>

class Game {
public:
    Game();

    void run();


private:
    void processEvents();
    void update();
    void render();
    void addPiece();


    sf::RenderWindow* window;
    std::vector<sf::Sprite> spriteList;
    std::vector<sf::Texture> textureList;
    std::queue<char> Moves;
    sf::Event event;

    int matrix[4][4];


};


#endif //CMAKESFMLPROJECT_GAME_HPP
