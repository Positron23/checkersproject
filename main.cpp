#include <iostream>
using namespace std;

class CheckerBoard {
    const char EMP = '.';
    const char BLACK = 'B';
    const char RED = 'R';
    // Board to be changed and used
    // Is from black's perspective
    char board[8][8];
    // Standard notation for board positions, using zero for unreachable squares
    const short numberedBoard[8][8] = {
            {0, 32, 0, 31, 0, 30, 0, 29},
            {28, 0, 27, 0, 26, 0, 25, 0},
            {0, 24, 0, 23, 0, 22, 0, 21},
            {20, 0, 19, 0, 18, 0, 17, 0},
            {0, 16, 0, 15, 0, 14, 0, 13},
            {12, 0, 11, 0, 10, 0, 9, 0},
            {0, 8, 0, 7, 0, 6, 0, 5},
            {4, 0, 3, 0, 2, 0, 1}
    };
    // Board at start of game; red represented by 'r', black represented by 'b'
    char initialBoard[8][8] = {
            {EMP, 'r', EMP, 'r', EMP, 'r', EMP, 'r'},
            {'r', EMP, 'r', EMP, 'r', EMP, 'r', EMP},
            {EMP, 'r', EMP, 'r', EMP, 'r', EMP, 'r'},
            {EMP, EMP, EMP, EMP, EMP, EMP, EMP, EMP},
            {EMP, EMP, EMP, EMP, EMP, EMP, EMP, EMP},
            {'b', EMP, 'b', EMP, 'b', EMP, 'b', EMP},
            {EMP, 'b', EMP, 'b', EMP, 'b', EMP, 'b'},
            {'b', EMP, 'b', EMP, 'b', EMP, 'b', EMP}
    };
    // Dictionary of positions, for easy access
    // Index refers to the position number, as seen in numberedBoard
    // First layer stores the row of the square
    // Second layer stores the column of the square
    short positionDict[33][2];

    public:
        // Default Constructor
        CheckerBoard(){
            // Set board state to be equal to the initialBoard state
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    board[i][j] = initialBoard[i][j];
                    short positionNumber = numberedBoard[i][j];
                    if (numberedBoard[i][j] > 0){
                        positionDict[positionNumber][0] = i;
                        positionDict[positionNumber][1] = j;
                    }
                }
            }
        }
        void printBoard(){
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    cout << board[i][j] << EMP;
                }
                cout << endl;
            }
        }
        // Finds if it is possible to make a move from the initial position, iPosition, to the final position, fPosition
        // Returns a short, which is 1 if the move can be made, 0 if not, 2 if another move can be made
        short canMakeMove(short iPosition, short fPosition, char colour) {
            if (iPosition * fPosition == 0){ // If either are zero
                return 0;
            }
            // Initial position row and column
            short iR = positionDict[iPosition][0];
            short iC = positionDict[iPosition][1];
            // Final position row and column
            short fR = positionDict[fPosition][0];
            short fC = positionDict[fPosition][1];
            char piece = board[iR][iC];
            if (toupper(piece) == colour){ // check if the correct colour is making the move
                // BLACK non-king
                if (piece == 'b'){
                    // not a taking move
                    if (abs(fR-iR) == 1 && abs(fC-iC) == 1 && isEmpty(fPosition) && fPosition > iPosition){
                        board[iR][iC] = EMP; // clear initial position
                        if (fPosition >= 29){ // check for promotion
                            board[fR][fC] = 'B';
                        }
                        else board[fR][fC] = piece;
                        return 1;
                    }
                    // taking move
                    if (abs(fR-iR)==2 && abs(fC-iC)==2 && fPosition>iPosition){
                        // take to the left or right, respectively
                        if (fPosition-iPosition == 9 || fPosition-iPosition==7){
                            board[iR][iC] = EMP;
                            board[(fR+iR)/2][(fC+iC)/2] = EMP;
                            board[fR][fC] = piece;
                            if (fPosition >= 29) { // check for promotion
                                board[fR][fC] = 'B';
                            }
                            return 2;
                        }

                    }
                }
                // WHITE non-king
                if (piece == 'w'){
                    // not a taking move
                    if (abs(fR-iR) == 1 && abs(fC-iC) == 1 && isEmpty(fPosition) && fPosition < iPosition){
                        board[iR][iC] = EMP; // clear initial position
                        if (fPosition <= 4){ // check for promotion
                            board[fR][fC] = 'W';
                        }
                        else board[fR][fC] = piece;
                        return 1;
                    }
                    // taking move
                    if (abs(fR-iR)==2 && abs(fC-iC)==2 && fPosition>iPosition){
                        // take to the left or right, respectively
                        if (fPosition-iPosition == -9 || fPosition-iPosition == -7){
                            board[iR][iC] = EMP;
                            board[(fR+iR)/2][(fC+iC)/2] = EMP;
                            board[fR][fC] = piece;
                            if (fPosition <= 4) { // check for promotion
                                board[fR][fC] = 'B';
                            }
                        }

                    }
                }
                // BLACK king
                if (piece == 'B'){
                    // not a taking move
                    if (abs(fR-iR) == 1 && abs(fC-iC) == 1 && isEmpty(fPosition)){
                        board[iR][iC] = EMP; // clear initial position
                        board[fR][fC] = piece;
                        return 1;
                    }
                    // taking move
                    if (abs(fR-iR)==2 && abs(fC-iC)==2){
                        // take to the left or right, respectively
                        if (fPosition-iPosition == 9 || fPosition-iPosition==7){
                            board[iR][iC] = EMP;
                            board[(fR+iR)/2][(fC+iC)/2] = EMP;
                            board[fR][fC] = piece;
                            return 2;
                        }

                    }
                }
                // WHITE king
                if (piece == 'W'){
                    // not a taking move
                    if (abs(fR-iR) == 1 && abs(fC-iC) == 1 && isEmpty(fPosition)){
                        board[iR][iC] = EMP; // clear initial position
                        board[fR][fC] = piece;
                        return 1;
                    }
                    // taking move
                    if (abs(fR-iR)==2 && abs(fC-iC)==2){
                        // take to the left or right, respectively
                        if (fPosition-iPosition == -9 || fPosition-iPosition == -7){
                            board[iR][iC] = EMP;
                            board[(fR+iR)/2][(fC+iC)/2] = EMP;
                            board[fR][fC] = piece;
                            return 2;
                        }

                    }
                }

            }
            return 0;
        }
        // Returns true if the square given by the position number is empty
        bool isEmpty(short positionNum){
            short row = positionDict[positionNum][0];
            short col = positionDict[positionNum][1];
            return board[row][col] == EMP;
        }

};

int main() {
    std::cout << "Hello, World!" << std::endl;
    CheckerBoard CB;
    CB.printBoard();
    return 0;
}
