#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <iostream>
#include <cmath>  
#include "Graph.h"
#include "Vertex.h"
#include "Queue.h"

struct Vec{
    int x;
    int y;

    Vec(){
        x = 0;
        y = 0;
    }

    Vec(int x, int y){
        this->x = x;
        this->y = y;
    }

    void set(int x, int y){
        this->x = x;
        this->y = y;
    }
};

std::ostream& operator<<(std::ostream& os, const Vec& v){
    os << "(" << v.x << ", " << v.y << ")";

    return os;
}

struct GameState;
std::ostream& operator<<(std::ostream& os, const GameState& state);

struct GameState{
    int** grid;
    bool currentTurn;
    int size;
    int turnCount;

    bool done;
    Vec lastMove;

    GameState(){
        size = 3;
        currentTurn = 0;
        turnCount = 0;
        done = false;

        lastMove.set(-1, -1);

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = -1;
            }
        }
    }

    GameState(int size){
        this->size = size;
        currentTurn = 0;
        turnCount = 0;
        done = false;

        lastMove.set(-1, -1);

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = -1;
            }
        }
    }

    GameState(const GameState& other){
        size = other.size;
        currentTurn = other.currentTurn;
        turnCount = other.turnCount;
        done = other.done;
        lastMove = other.lastMove;

        grid = new int*[size];

        for (int i = 0; i < size; i++){
            grid[i] = new int[size];
            for (int j = 0; j < size; j++){
                grid[i][j] = other.grid[i][j];
            }
        }
    }

    bool operator==(const GameState& other){
        bool sizeMatch = size == other.size;
        bool currentTurnMatch = currentTurn == other.currentTurn;
        bool turnCountMatch = turnCount == other.turnCount;
        bool doneMatch = done == other.done;
        bool lastMoveMatch = lastMove.x == other.lastMove.x && lastMove.y == other.lastMove.y;
        if (sizeMatch && currentTurnMatch && turnCountMatch && doneMatch && lastMoveMatch){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    if (grid[i][j] != other.grid[i][j]){
                        return false;
                    }
                }
            }
            
            return true;
        }
        else{
            return false;
        }
    }

    GameState& operator=(const GameState& other){
        currentTurn = other.currentTurn;
        turnCount = other.turnCount;
        done = other.done;
        lastMove = other.lastMove;

        if (size == other.size){
            for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                    grid[i][j] = other.grid[i][j];
                }
            }
        }
        else{
            
            for (int i = 0; i < size; i++){
                delete[] grid[i];
            }
            delete[] grid;

            size = other.size;

            grid = new int*[size];

            for (int i = 0; i < size; i++){
                grid[i] = new int[size];
                for (int j = 0; j < size; j++){
                    grid[i][j] = other.grid[i][j];
                }
            }
        }

        return *this;
    }

    bool hasWon(int player){
        for (int i = 0; i < size; i++){
            int count = 0;
            for (int j = 0; j < size; j++){
                if (grid[i][j] == player){
                    count++;
                }
            }
            if (count == size){
                return true;
            }
        }

        for (int i = 0; i < size; i++){
            int count = 0;
            for (int j = 0; j < size; j++){
                if (grid[j][i] == player){
                    count++;
                }
            }
            if (count == size){
                return true;
            }
        }

        int mainDiagCount = 0;
        for (int i = 0; i < size; i++){
            if (grid[i][i] == player){
                mainDiagCount++;
            }
        }
        
        if (mainDiagCount == size){
            return true;
        }

        int secondaryDiagCount = 0;
        for (int i = 0; i < size; i++){
            if (grid[i][size-1-i] == player){
                secondaryDiagCount++;
            }
        }
        if (secondaryDiagCount == size){
            return true;
        }

        return false;
    }

    //Erick
    bool play(int x, int y){
        int row = x;
        int column = y;

        while((row > size-1 || row<0 || column>size-1 || column<0) || grid[row][column] != -1){
            std::cout<< "\033[1A";
            std::cout<< "\033[2K";
            std::cout<< "\033[0G";
            std::cout<< "Invalid Input, please re-enter your move: ";
            std::cin >> row >> column;
            //std::cin.clear();
            //std::cout<<row<<" "<<column<<std::endl;
        }

        // if (grid[row][column] != -1){
        //     return false;
        //     std::cout<<row<<" 1"<<column<<std::endl;
        // }

        grid[row][column] = currentTurn;
        currentTurn = !currentTurn;
        turnCount++;
        lastMove.set(row, column);

        if (turnCount == size * size){
            done = true;
        }
        else if (hasWon(0) || hasWon(1)){
            done = true;
        }

        return true;
    }



/*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
                                            AI_Player stuff start
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
*/

    //Matthew
    Vec AI_Player_makeMove(int difficulty, GameState gameBoard){
        if (difficulty == 1){
            //easy mode function
            return findValidMove(gameBoard);
        }
        else if (difficulty == 2){
            //hard mode function
            return findBestMove(gameBoard);
        }

        return Vec(0, 0);//will never trigger
    }

    //Julian and William
    Vec findValidMove(GameState gameBoard){
        for(int i = 0; i < size; i++){
            for(int j = 0; j < size; j++){
                if(gameBoard.grid[i][j] == -1){
                    return Vec(i, j);
                }
            }
        }

        return Vec(0,0);
    }

    //Matthew and Erick
    Vec findBestMove(GameState gameBoard){
        if(size == 3){
            Graph<GameState> stateSpace;
            Vertex<GameState>* start = new Vertex<GameState>(gameBoard);

            int bestVal = -1000;
            int bestI = 0;
            int bestJ = 0;

            ArrayList<Vertex<GameState>*> a;
            ArrayList<int> b;

            stateSpace.addVertex(start);
            Queue<Vertex<GameState>*> frontier;
            frontier.enqueue(start);

            while(!frontier.isEmpty()){
                Vertex<GameState>* curr = frontier.dequeue();
                if(!curr->data.done){
                    for(int i = 0; i < gameBoard.size; i++){
                        for(int j = 0; j < gameBoard.size; j++){
                            if(curr->data.grid[i][j] == -1){
                                GameState next = curr->data;
                                next.play(i,j);
                                Vertex<GameState>* successor = new Vertex<GameState>(next);
                                //int currVal = getRewardForHardMove(successor, 1);
                                stateSpace.addVertex(successor);
                                stateSpace.addDirectedEdge(curr,successor);
                                //int currVal = getRewardForHardMove(successor, 1);
                                if(!successor->data.done){
                                    frontier.enqueue(successor);
                                }
                                //int currVal = getRewardForHardMove(successor, 1);


                                // if(currVal > bestVal){
                                //     bestI = i;
                                //     bestJ = j;
                                //     bestVal = currVal;
                                // }
                            }
                        }
                    }
                }
            }

            //for every successor of start, call getReward(successor, player of choice)
            for(int k = 0; k < stateSpace.vertices.size(); k++){
                if (gameBoard.turnCount+1 == stateSpace.vertices[k]->data.turnCount){
                    a.append(stateSpace.vertices[k]);
                    b.append(getRewardForHardMove(stateSpace.vertices[k], 1));
                }
            }

            int bestScore = -1000;
            int currScore;
            int r;
            currScore = bestScore;

            for (int i = 0; i < b.size(); i++){
                if (b[i]>currScore){
                    currScore = b[i];
                    r = i;
                }
            }

            //for()

            return a[r]->data.lastMove;

            //return Vec(bestI,bestJ);
        } 
        else if(size == 4){
            return findBestMove_4x4(gameBoard);
        }

        return Vec(0, 0);
    }

    //Erick
    int getRewardForHardMove(Vertex<GameState>* start, int player){
        if (start->neighbors.size() == 0){
            int currPlayer = start->data.currentTurn;
            if (start->data.hasWon(player)){
                return 100;
            }
            else if (start->data.hasWon(!player)){
                return -100;
            }
            else{
                return 50;
            }
        }
        else{
            int reward = getRewardForHardMove(start->neighbors[0]->location, player);
            for (int i = 1; i < start->neighbors.size(); i++){
                int curr = getRewardForHardMove(start->neighbors[i]->location, player);
                if (start->data.currentTurn == player){
                    if (curr > reward){
                        reward = curr;
                    }
                }
                else{
                    if (curr < reward){
                        reward = curr;
                    }
                }
            }
            return reward;
        }
    }

    Vec findBestMove_4x4(GameState game){
        Graph<GameState> stateSpace;
        Vertex<GameState>* start = new Vertex<GameState>(game);

        stateSpace.addVertex(start);

        Queue<Vertex<GameState>*> frontier;
        frontier.enqueue(start);

        ArrayList<Vertex<GameState>*> a;
        ArrayList<int> b;
        int depth = 0;
        while (depth < 6 && !frontier.isEmpty()){
            depth++;
            //std::cout<< depth << std::endl;
            Vertex<GameState>* curr = frontier.dequeue();
            if (!curr->data.done){
                for(int i = 0; i < game.size; i++){
                    for (int j = 0; j < game.size; j++){
                        if(curr->data.grid[i][j] == -1){
                            GameState next = curr->data;
                            next.play(i, j);
                            Vertex<GameState>* successor = new Vertex<GameState>(next);
                            stateSpace.addVertex(successor);
                            stateSpace.addDirectedEdge(curr, successor);
                        
                            if (!successor->data.done){
                                frontier.enqueue(successor);
                            }
                        }
                    }
                }
            }
        }
        //return BestMove;
        for (int i = 0; i < stateSpace.vertices.size(); i++){
            if (game.turnCount + 1 == stateSpace.vertices[i]->data.turnCount){
                //std::cout<< stateSpace.vertices[i]->data << " " << evaluateGameState(stateSpace.vertices[i], 1) << std::endl;
                a.append(stateSpace.vertices[i]);
                b.append(rewardForHard4x4(stateSpace.vertices[i], 1));
            }
        }
        //std::cout<< m << std::endl;
        int bestScore = -1000;
        int currScore;
        int r;
        currScore = bestScore;
        //std::cout<< m << std::endl;
        for (int k = 0; k < b.size(); k++){
            //std::cout<< s[i] << std::endl;
            if (b[k] > currScore){
                currScore = b[k];
                r = k;
            }
        }

        //std::cout<< s << std::endl;
        return a[r]->data.lastMove;
    }   

    int gridValue(int i, int j) {
        // Assign higher weights to the center and corners of the board
        if ((i == 1 || i == 2) && (j == 1 || j == 2)) {
            return 10;
        }
        else if ((i == 0 || i == 3) && (j == 0 || j == 3)) {
            return 5; // Decrease the weight of the corners
        }
        // Assign higher weights to the cells on the diagonals
        else if (i == j || i + j == 3) {
            return 7;
        }
        else {
            return 1;
        }
    }
 
    bool isTwoInARow(GameState gameBoard, int player) {
        int count;

        // Check rows and columns
        for (int i = 0; i < 4; i++) {
            count = 0;
            for (int j = 0; j < 4; j++) {
                if (gameBoard.grid[i][j] == player) {
                    count++;
                }
            }
            if (count == 2) {
                return true;
            }


            count = 0;
            for (int j = 0; j < 4; j++) {
                if (gameBoard.grid[j][i] == player) {
                    count++;
                }
            }
            if (count == 2) {
                return true;
            }
        }


        // Check diagonals
        count = 0;
        for (int i = 0; i < 4; i++) {
            if (gameBoard.grid[i][i] == player) {
                count++;
            }
        }
        if (count == 2) {
            return true;
        }


        count = 0;
        for (int i = 0; i < 4; i++) {
            if (gameBoard.grid[i][3-i] == player) {
                count++;
            }
        }
        if (count == 2) {
            return true;
        }


        return false;
    }

    bool isThreeInARow(GameState gameBoard, int player) {
        for (int i = 0; i < 4; i++) {   //rows
            int count = 0;
            for (int j = 0; j < 4; j++) {
                if (gameBoard.grid[i][j] == player) {
                    count++;
                }
            }
            if (count >= 3) {
                return true;
            }
        }


        for (int j = 0; j < 4; j++) {   //cols
            int count = 0;
            for (int i = 0; i < 4; i++) {
                if (gameBoard.grid[i][j] == player) {
                    count++;
                }
            }
            if (count >= 3) {
                return true;
            }
        }


        int count1 = 0, count2 = 0;
        for (int i = 0; i < 4; i++) {       //diags
            if (gameBoard.grid[i][i] == player) {
                count1++;
            }
            if (gameBoard.grid[i][3-i] == player) {
                count2++;
            }
        }
        if (count1 >= 3 || count2 >= 3) {
            return true;
        }


        return false;
    }

    int rewardForHard4x4(Vertex<GameState>* start, int player) {
        GameState gameBoard = start->data;
        int currScore = 0;

        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                if (gameBoard.grid[i][j] == player) {    //ai
                    currScore += gridValue(i, j);
                }
                else if (gameBoard.grid[i][j] != 0) {
                    currScore -= gridValue(i, j);
                }
            }
        }
        if (gameBoard.hasWon(player)) {
            currScore += 1000;
        }
        else if (gameBoard.hasWon(!player)) {
            currScore -= 1000;
        }
    
    
        GameState temp;
        if (isTwoInARow(gameBoard, !player)) {       //check 2 in a row
            temp = gameBoard;
            Vec last = gameBoard.lastMove;
            temp.grid[last.x][last.y] = !player;
            if (isThreeInARow(temp, !player)) {     //check 3 in a row
                currScore += 800;
            }
        
        
        }
        if (isThreeInARow(gameBoard, !player)) {     //check 3 in a row
            temp = gameBoard;
            Vec last = gameBoard.lastMove;
        
            temp.grid[last.x][last.y] = !player;  // move for player X
            if (temp.hasWon(!player)) {  // Check if this move results in a win for player X
                currScore += 5000;
            }
        }

        return currScore;
    }


/*
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
                                            AI_Player stuff end
=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=~=
*/



    ~GameState(){
        for (int i = 0; i < size; i++){
            delete[] grid[i];
        }
        delete[] grid;
    }
};

std::ostream& operator<<(std::ostream& os, const GameState& state){
    os << "   ";
    for (int j = 0; j < state.size; j++){
        os << " " << j << "  ";
    }
    os << std::endl;
    os << "   ";
    for (int j = 0; j < state.size; j++){
        os << "--- ";
    }
    os << std::endl;
    for (int i = 0; i < state.size; i++){
        os << i << " ";
        for (int j = 0; j < state.size; j++){
            char c = ' ';
            if (state.grid[i][j] == 0){
                c = 'X';
            }
            else if (state.grid[i][j] == 1){
                c = 'O';
            }
            os << "| " << c << " ";
            if (j == state.size - 1) os << "|";
        }
        os << std::endl << "   ";
        for (int j = 0; j < state.size; j++){
            os << "--- ";
        }
        os << std::endl;
    }

    return os;
}

#endif