#include <chrono>
#include <thread>

#include "../include/tictactoe.hpp"

TTT::TTT(){
    fillBoard();
}

void TTT::fillBoard(){
    int counter = 0;
    for (int i = 0; i < BSIZE; i++){
        for (int j = 0; j < BSIZE; j++){
            counter--;
            board[i][j].setMark(' ');
            board[i][j].setSellStatus(counter);
        }
    }
}

void TTT::printBoard()const{
    std::cout << "\n -------------\n";
    for (int i = 0; i < BSIZE; i++){
        std::cout << " | ";
        for (int j = 0; j < BSIZE; j++){
            std::cout << board[i][j].getMark() << " | ";
        }
        std::cout << "\n -------------\n";
    }
}

void TTT::makeMove(){
    int row, col;

    if (turn == 'X')
        std::cout << "\nPlayer - 1(X) turn: ";
    else if (turn == 'O')
        std::cout << "\nPlayer - 2(O) turn: ";

    std::cin >> choice;
    while (!correctNumber(choice)){
        std::cout << "Invalid Move!\nYour move: ";
        std::cin >> choice;
    }

    switch (choice){
    case 1: row = 0; col = 0; break;
    case 2: row = 0; col = 1; break;
    case 3: row = 0; col = 2; break;
    case 4: row = 1; col = 0; break;
    case 5: row = 1; col = 1; break;
    case 6: row = 1; col = 2; break;
    case 7: row = 2; col = 0; break;
    case 8: row = 2; col = 1; break;
    case 9: row = 2; col = 2; break;
    }

    if (turn == 'X' && board[row][col].getMark() != 'X' && board[row][col].getMark() != 'O'){
        board[row][col].setMark('X');
        board[row][col].setSellStatus(1);
        turn = 'O';
        totalMoves++;
        printBoard();
    } else if (turn == 'O' && board[row][col].getMark() != 'X' && board[row][col].getMark() != 'O'){
        board[row][col].setMark('O');
        board[row][col].setSellStatus(2);
        turn = 'X';
        totalMoves++;
        printBoard();
    } else {
        std::cout << "Cell already filled! Choose another one!\n";
        makeMove();
    }

}

bool TTT::gameOver(){  
    for (int i = 0; i < 3; i++){
        if (board[i][0].getSellStatus() == board[i][1].getSellStatus() && board[i][0].getSellStatus() == board[i][2].getSellStatus()
        || board[0][i].getSellStatus() == board[1][i].getSellStatus() && board[0][i].getSellStatus() == board[2][i].getSellStatus()){
            printWinner();
            return true;
        }
        
        if (board[0][0].getSellStatus() == board[1][1].getSellStatus() && board[0][0].getSellStatus() == board[2][2].getSellStatus()
        || board[0][2].getSellStatus() == board[1][1].getSellStatus() && board[0][2].getSellStatus() == board[2][0].getSellStatus()){
            printWinner();
            return true;
        }
    }
    
    if (totalMoves == maxMoves){
        std::cout << "Draw!\n";
        return true;
    }

    return false;
}

void TTT::printWinner()const{
    if (turn == 'O')
        std::cout << "Congratulations! Player with 'X' has won the game\n";
    else
        std::cout << "Congratulations! Player with 'O' has won the game\n";
}

bool TTT::correctNumber(int value){
    if (value > 0 && value < 10)
        return true;
    else
        return false;
}

bool TTT::isMovesLeft(){
    if (totalMoves == maxMoves)
        return true;
    else    
        return false;
}

char TTT::getTurn(){
    return turn;
}

bool TTT::makeMoveAI(Move bestMove){
    if (turn == 'O'){
        std::cout << "Computer - 2(O) turn...\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(800));
        board[bestMove.row][bestMove.col].setMark('O');
        board[bestMove.row][bestMove.col].setSellStatus(2);
        turn = 'X';
        totalMoves++;
        printBoard();
        return false;
    } else {
        return true;
    }
}

void TTT::initialize(){
    AI ai;

    printBoard();
    while (!gameOver()){
        Move bestMove = ai.findBestMove(board);
        // int valBestMove = board[bestMove.row][bestMove.col].getSellStatus();
        // std::cout << "The optimal move is: " << -valBestMove << std::endl;

        if (makeMoveAI(bestMove))
            makeMove();
    }
}