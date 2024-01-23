#include <iostream>
#include <system_error>
#include "GameState.h"
#include "Human.h"
#include "Game_With_AI.h"
#include "Graph.h"
#include "Vertex.h"
#include "Queue.h"
using namespace std;
int size = 3;
int difficulty = 1;

/* Worked with Armando Sanchez, Matthew Kum, William Chen, and Erick Yang */

//Matthew
void techSupportPage(){
    system("clear");
    cout << "= \\     /      01 1 0 1 1 11 = 1-= - 1= - = - = - = - -  -1- 1 -t2- " << endl;
    cout << "   1=- 4-1-05 1=-50 15=  T3ch Support pAge broken 0 199  -0 0 -0  = - - = " << endl;
    cout << "- =- =- -= -= - 1151 pl-se conta-t tech support vi_a tec_h sup ort page        1" << endl;
   
    string s = "";
    while(getline(cin, s)){
        cin.ignore();
       
        if (s == ""){
            break;
        }
    }
}

//William
string displayDifficulty(int whichDifficulty){
   string mode;

   if(whichDifficulty == 1){
       mode = "EASY";
   }
   else if(whichDifficulty == 2){
       mode = "HARD";
   }

   return mode;
}

//Armando and Matthew
void displayMenu(){
    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << endl;
    cout << "1. Play Against A Human Player" << endl;
    cout << "2. Play Against A Computer Assisted Player" << endl;
    cout << "3. Settings" << endl;
    cout << "4. Exit" << endl << endl;
    cout << "5. Tech Support" << endl;
    cout << "=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=" << endl << endl << endl;
}

//Julian and Armando
int main(){
    bool whichDifficulty; // true = hard, false = easy
    int option;
    bool gameOver = false;
    displayMenu();

    while (gameOver != true){
        system("clear");
        cout << "Current Grid Size: " << size << endl;
        cout << "Current AI Difficulty: " << displayDifficulty(difficulty) << endl << endl;
        displayMenu();
        cout << "Select Option: ";

        while(cin >> option){
            if(option == 1){
                humanGame(size);
                break;
            }

            else if(option == 2){
                /*  To use the above function, you need to make a struct where it has a GameState variable that 
                    represents the game board. When it is the AI's turn, you call the above function to ge it's move
                */
                gameWithAI game(difficulty, size);
                game.startGame();
                break;
            }

            else if(option == 3){
                system("clear");
                cout << "Choose Computer Difficulty" << endl << endl;
                cout << "1. Easy" << endl;
                cout << "2. Hard" << endl << endl;
                cout << "Select a choice: ";
                cin >> difficulty;

                while (difficulty < 1 || difficulty > 2){
                    system("clear");
                    cout << "Choose Computer Difficulty" << endl << endl;
                    cout << "1. Easy" << endl;
                    cout << "2. Hard" << endl << endl;
                    cout << "Please pick a number available: ";
                    cin >> difficulty;
                }

                if(difficulty == 1){
                    whichDifficulty = false;
                    cout << "AI EASY" << endl;
                }
                else if (difficulty == 2){
                    whichDifficulty = true;
                    cout << "AI HARD" << endl;
                }

                system("clear");
                cout << "What size gameboard do you want? (3-4)" << endl << endl;
                cout << "Enter desired size: ";
                int newSize;
                cin >> newSize;

                while (newSize > 4 || newSize < 3){
                    if (newSize > 4){
                        system("clear");
                        cout << "Too big (Pick from 3-4)" << endl << endl;
                        cout << "Enter desired size: ";
                        cin >> newSize;
                    }
                    else if (newSize < 3) {
                        system("clear");
                        cout << "Too small (Pick from 3-4)" << endl << endl;
                        cout << "Enter desired size: ";
                        cin >> newSize;
                    }
                    else{
                        size = newSize;
                        cout << size << endl;
                        break;
                    }
                }
                size = newSize;
                break;
            }

            else if(option == 4){
                cout << "Thank you for playing, goodbye..." << endl;
                exit(0);
                gameOver = true;
            }

            else if(option == 5){
                techSupportPage();
                break;
            }
        }
    }

    return 0;
}