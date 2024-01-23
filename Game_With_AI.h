#ifndef GAME_WITH_AI_H
#define GAME_WITH_AI_H
#include <cstdlib>
#include <iostream>
#include <cmath>  
#include "Graph.h"
#include "Vertex.h"
#include "Queue.h"
#include "GameState.h"

//Julian
struct gameWithAI{
    int difficulty;
    int size;
    std::string enter;
   
    gameWithAI(){

    }

    gameWithAI(int mode, int size){
        difficulty = mode; //1 is easy mode, 2 is hard mode
        this->size = size;
    }

    void startGame(){
        GameState gameBoard(size);
        bool isPlayerTurn = true; //X is always the player.

        while (!gameBoard.done){
            system("clear");

            if (isPlayerTurn){
                int x, y;
               
                std::cout << gameBoard << std::endl;
                std::cout << "\n";
                std::cout << "Enter move for (X): ";
                isPlayerTurn = !isPlayerTurn;

                std::string move;
                std::cin >> move;
                x = std::stoi(move);

                std::cin >> move;
                y = std::stoi(move);

                gameBoard.play(x, y);
            }
            else {
                isPlayerTurn = !isPlayerTurn;
                Vec move = gameBoard.AI_Player_makeMove(difficulty, gameBoard);
                gameBoard.play(move.x, move.y);
                std::cout << gameBoard << std::endl;
            }
        }

        system("clear");
        std::cout << gameBoard << std::endl;
        std::cout << std::endl;

        if (gameBoard.hasWon(0)){
            std::cout << "Player X has won" << std::endl << std::endl << std::endl;
            std::cout << "Press [enter] to continue";

            getline(std::cin, enter);
            std::cin.ignore();
            if (enter == "") {}
        }

        else if (gameBoard.hasWon(1)){
            std::cout << "Player O has won" << std::endl << std::endl << std::endl;
            std::cout << "Press [enter] to continue";

            getline(std::cin, enter);
            std::cin.ignore();
            if (enter == "") {}
        }

        else {
            std::cout << "It's a tie" << std::endl << std::endl << std::endl;
            std::cout << "Press [enter] to continue";

            getline(std::cin, enter);
            std::cin.ignore();
            if (enter == "") {}
        }
    }
};

#endif