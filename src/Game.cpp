//
// Created by zjchr on 11/12/2023.
//
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cmath>
#include "Game.hpp"

using namespace std;

Game::Game(){

    for (int row = 0;row<4;row++)
        for (int col=0;col<4;col++)
            matrix[row][col] = 0;

    window = new sf::RenderWindow({1024, 1024}, "2048");
    (*window).setKeyRepeatEnabled(false);



    textureList.resize(13);
    textureList[0].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\blank.png)");
    textureList[1].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\1.png)");
    textureList[2].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\2.png)");
    textureList[3].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\4.png)");
    textureList[4].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\8.png)");
    textureList[5].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\16.png)");
    textureList[6].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\32.png)");
    textureList[7].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\64.png)");
    textureList[8].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\128.png)");
    textureList[9].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\256.png)");
    textureList[10].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\512.png)");
    textureList[11].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\1024.png)");
    textureList[12].loadFromFile(R"(C:\Users\zjchr\CLionProjects\gamingProj1\src\sprites\2048.png)");



    spriteList.resize(16);
    for (int i=0,c=0;c<4;c++){
        for (int r=0;r<4;r++,i++)
        {
            spriteList[i].setScale(8,8);
            spriteList[i].setPosition(c*144, r*144);
            spriteList[i].move(0, 0);
        }
    }


    addPiece();
}
void Game::run(){
    while ((*window).isOpen()){
        processEvents();
        update();
        render();
    }
}

void Game::processEvents() {
    while ((*window).pollEvent(event)){
        //Close Window
        if (event.type == sf::Event::Closed){
            (*window).close();
        }

        //Escape Key to Exit
        if (event.type == sf::Event::KeyPressed){
            if (event.key.code == sf::Keyboard::Key::Escape)
                (*window).close();
        }

        // WASD movement
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::W){
            Moves.push('U');
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::S){
            Moves.push('D');
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::A){
            Moves.push('L');
        }
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Key::D){
            Moves.push('R');
        }


    }
}
void Game::update() {
    if (!Moves.empty())
    {
        int tempMat[4][4];
        for (int r=0;r<4;r++)
            for (int c=0;c<4;c++)
                tempMat[r][c]=matrix[r][c];


        switch (Moves.front()) {
            case 'U':
                for (int c=0;c<4;c++){
                    for (int r=0;r<3;r++){
                        if (matrix[r][c]==0){
                            for (int i=r;i<3;i++){
                                matrix[i][c] = matrix[i+1][c];
                            }
                            matrix[3][c]=0;
                        }
                    }
                    for (int r=0;r<3;r++){
                        if (matrix[r][c]==matrix[r+1][c] && matrix[r][c]!=0){
                            matrix[r][c]++;
                            matrix[r+1][c] = 0;
                        }
                    }
                    for (int r=0;r<3;r++){
                        if (matrix[r][c]==0){
                            for (int i=r;i<3;i++){
                                matrix[i][c] = matrix[i+1][c];
                            }
                            matrix[3][c]=0;
                        }
                    }
                }
                break;
            case 'D':
                for (int c=0;c<4;c++){
                    for (int r=3;r>0;r--){
                        if (matrix[r][c]==0){
                            for (int i=r;i>0;i--){
                                matrix[i][c] = matrix[i-1][c];
                            }
                            matrix[0][c]=0;
                        }
                    }
                    for (int r=3;r>0;r--){
                        if (matrix[r][c]==matrix[r-1][c] && matrix[r][c]!=0){
                            matrix[r][c]++;
                            matrix[r-1][c] = 0;
                        }
                    }
                    for (int r=3;r>0;r--){
                        if (matrix[r][c]==0){
                            for (int i=r;i>0;i--){
                                matrix[i][c] = matrix[i-1][c];
                            }
                            matrix[0][c]=0;
                        }
                    }
                }
                break;
            case 'R':
                for (int r=0;r<4;r++){
                    for (int c=3;c>0;c--){
                        if (matrix[r][c]==0){
                            for (int i=c;i>0;i--){
                                matrix[r][i] = matrix[r][i-1];
                            }
                            matrix[r][0]=0;
                        }
                    }
                    for (int c=3;c>0;c--){
                        if (matrix[r][c]==matrix[r][c-1] && matrix[r][c]!=0){
                            matrix[r][c]++;
                            matrix[r][c-1] = 0;
                        }
                    }
                    for (int c=3;c>0;c--){
                        if (matrix[r][c]==0){
                            for (int i=c;i>0;i--){
                                matrix[r][i] = matrix[r][i-1];
                            }
                            matrix[r][0]=0;
                        }
                    }
                }
                break;
            case 'L':
                for (int r=0;r<4;r++){
                    for (int c=0;c<3;c++){
                        if (matrix[r][c]==0){
                            for (int i=c;i<3;i++){
                                matrix[r][i] = matrix[r][i+1];
                            }
                            matrix[r][3]=0;
                        }
                    }
                    for (int c=0;c<3;c++){
                        if (matrix[r][c]==matrix[r][c+1] && matrix[r][c]!=0){
                            matrix[r][c]++;
                            matrix[r][c+1] = 0;
                        }
                    }
                    for (int c=0;c<3;c++){
                        if (matrix[r][c]==0){
                            for (int i=c;i<3;i++){
                                matrix[r][i] = matrix[r][i+1];
                            }
                            matrix[r][3]=0;
                        }
                    }
                }
                break;
        }
        bool checkMove=false;
        for (int r=0;r<4;r++)
            for (int c=0;c<4;c++)
                if (tempMat[r][c]!=matrix[r][c])
                    checkMove=true;
        if (checkMove){
            addPiece();
        }
        Moves.pop();
    }
}

void ::Game::render() {
    (*window).clear(sf::Color::Black);

    for (int i=0,c=0;c<4;c++){
        for (int r=0;r<4;r++,i++)
        {
            spriteList[i].setTexture(textureList[matrix[r][c]]);
            (*window).draw(spriteList[i]);
        }
    }
    (*window).display();
}

void Game::addPiece() {
    bool need = true;
    while (need){
        int tempR=rand()%4, tempC=rand()%4;
        if (matrix[tempR][tempC]==0){
            matrix[tempR][tempC] = ((rand()%2)+2);
            need=false;
        }
    }
}