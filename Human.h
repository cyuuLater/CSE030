#ifndef HUMAN_H
#define HUMAN_H
#include <system_error>
#include "GameState.h"

#include <iostream>
std::string enter;

//Armando
void humanGame(int size){
    GameState game(size);

    while(!game.done){
        system("clear");
        std::cout << game <<  std::endl;
        int x, y;

        std::cout << std::endl;
        std::cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
        std::cin >> x >> y;

        game.play(x, y);
    }

    system("clear");
    std::cout << game << std::endl;
    std::cout << std::endl;

    if (game.hasWon(0)){
        std::cout << "Player X has won" << std::endl << std::endl << std::endl;
        std::cout << "Press [enter] to continue";

        getline(std::cin, enter);
        std::cin.ignore();
        if (enter == "") {}
    }

    else if (game.hasWon(1)){
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

#endif