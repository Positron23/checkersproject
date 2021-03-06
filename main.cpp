#include <iostream>
#include <vector>
using namespace std;

const char EMP = '.';
const char BLACK = 'B';
const char RED = 'R';
const double INF = 1000000000000; // large number that will never be reached by static evalution

/*
struct piece {
    int row;
    int col;
    char c;
};
 */
struct Move {
    int iPosition;
    int fPosition;
    char c;
};

struct line {
    int iPosition;
    int fPosition;
    char c;
    double eval;
};

class CheckerBoard {

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
        void setBoard(int row, int col, char c){
            board[row][col] = c;
        }
        CheckerBoard copy(){
            CheckerBoard ret;
            for (int r = 0; r < 8; r++){
                for (int c = 0; c < 8; c++){
                    ret.setBoard(r, c, board[r][c]);
                }
            }
            return ret;
        }
        void printBoard(){
            for (int i = 0; i < 8; i++){
                for (int j = 0; j < 8; j++){
                    cout << board[i][j] ;
                }
                cout << endl;
            }
        }

        char findWinner(){
            int numRed = 0; int numBlack = 0;
            for (int r = 0; r < 8; r++){
                for (int c = 0; c < 8; c++){
                    if (toupper(board[r][c]) == RED)
                        numRed += 1;
                    if (toupper(board[r][c]) == BLACK)
                        numBlack += 1;
                }
            }
            if (numRed == 0)
                return BLACK;
            else if (numBlack == 0)
                return RED;
            else
                return EMP;
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

                        return 1;
                    }
                    // taking move
                    if (abs(fR-iR)==2 && abs(fC-iC)==2 && fPosition>iPosition){
                        // take to the left or right, respectively
                        if (fPosition-iPosition == 9 || fPosition-iPosition==7){

                            return 2;
                        }

                    }
                }
                // RED non-king
                if (piece == 'r'){
                    // not a taking move
                    if (abs(fR-iR) == 1 && abs(fC-iC) == 1 && isEmpty(fPosition) && fPosition < iPosition){

                        return 1;
                    }
                    // taking move
                    if (abs(fR-iR)==2 && abs(fC-iC)==2 && fPosition<iPosition){
                        // take to the left or right, respectively
                        if (fPosition-iPosition == -9 || fPosition-iPosition == -7){

                            return 2;
                        }

                    }
                }
                // BLACK king
                if (piece == 'B'){
                    // not a taking move
                    if (abs(fR-iR) == 1 && abs(fC-iC) == 1 && isEmpty(fPosition)){

                        return 1;
                    }
                    // taking move
                    if (abs(fR-iR)==2 && abs(fC-iC)==2){
                        // take to the left or right, respectively
                        if (fPosition-iPosition == 9 || fPosition-iPosition==7){

                            return 2;
                        }

                    }
                }
                // RED king
                if (piece == 'R'){
                    // not a taking move
                    if (abs(fR-iR) == 1 && abs(fC-iC) == 1 && isEmpty(fPosition)){

                        return 1;
                    }
                    // taking move
                    if (abs(fR-iR)==2 && abs(fC-iC)==2){
                        // take to the left or right, respectively
                        if (fPosition-iPosition == -9 || fPosition-iPosition == -7){

                            return 2;
                        }

                    }
                }

            }
            return 0;
        }
        int makeMove(int iPosition, int fPosition, char colour) { //Function to make a move and update checkers board
            int result = canMakeMove(iPosition, fPosition, colour);
            if (result==0) return 0;
            // Initial position row and column
            short iR = positionDict[iPosition][0];
            short iC = positionDict[iPosition][1];
            // Final position row and column
            short fR = positionDict[fPosition][0];
            short fC = positionDict[fPosition][1];
            char piece = board[iR][iC];

            board[fR][fC] = piece;
            board[iR][iC] = EMP;

            if (result==2){
                board[(fR+iR)/2][(fC+iC)/2] = EMP;
            }
            if (colour==BLACK && fPosition>=29) board[fR][fC] = 'B';
            if (colour==RED && fPosition<=4) board[fR][fC] = 'R';
            return result;
        }
        // Returns true if the square given by the position number is empty
        bool isEmpty(short positionNum){
            short row = positionDict[positionNum][0];
            short col = positionDict[positionNum][1];
            return board[row][col] == EMP;
        }

        vector<Move> possibleMoves() {
            vector<Move> pM;
            for(int i=1; i<33; i++)
            {
                for(int j=1; j<33; j++)
                {
                    char c = board[positionDict[i][0]][positionDict[j][1]];
                    if (canMakeMove(i, j, c))
                    {
                        Move t;
                        //t.c = c; t.row = positionDict[j][0]; t.col = positionDict[j][1];
                        t.iPosition = i; t.fPosition = j; t.c = c;
                        pM.push_back(t);
                    }
                }
            } /*
            for(int i = 0; i<8; i++)
            {
                for (int j = 0; j<8; j++)
                {
                    if(board[i][j] == 'r')
                    {
                        if((i+1) < 8 && (j+1) < 8 && board[i+1][j+1] == EMP)
                        {
                            pair <int, int> t;
                            t.first = i+1; t.second = j+1;
                            pM.push_back(t);
                        }
                        if((i+1) < 8 && (j-1) > 0 && board[i+1][j-1] == EMP)
                        {
                            pair <int, int> t;
                            t.first = i+1; t.second = j-1;
                            pM.push_back(t);
                        }
                    }
                    if(board[i][j] == 'b')
                    {
                        if((i-1) > 0 && (j+1) < 8 && board[i-1][j+1] == EMP)
                        {
                            pair <int, int> t;
                            t.first = i-1; t.second = j+1;
                            pM.push_back(t);
                        }
                        if((i-1) > 0 && (j-1) > 0 && board[i+1][j-1] == EMP)
                        {
                            pair <int, int> t;
                            t.first = i-1; t.second = j-1;
                            pM.push_back(t);
                        }
                    }
                }
            }
            */
            return pM;
        }

        double static_evaluation() { // Simple evaluation function
            int eval = 0;
            for (int r = 0; r < 8; r++){
                for (int c = 0; c < 8; c++){
                    if (board[r][c] == 'r'){
                        eval -= 1;
                    }
                    if (board[r][c] == 'R'){
                        eval -= 3;
                    }
                    if (board[r][c] == 'b'){
                        eval += 1;
                    }
                    if (board[r][c] == 'B'){
                        eval += 3;
                    }
                }
            }
            return eval;
        }

};

double minimax(CheckerBoard board, int depth, double alpha, double beta, char player){
    if (depth == 0 || board.findWinner() != EMP)
        return board.static_evaluation();

    if (player == BLACK){
        double maxEval = -1*INF;
        double eval = maxEval;
        Move bestMove;
        vector<Move> pM = board.possibleMoves();
        for (Move x: pM){
            CheckerBoard clone = board.copy();
            clone.makeMove(x.iPosition, x.fPosition, x.c);
            eval = minimax(clone, depth - 1, alpha, beta, RED);
            if (eval > maxEval){
                maxEval = eval;
                bestMove.iPosition = x.iPosition;
                bestMove.fPosition = x.fPosition;
                bestMove.c = x.c;
            }
            alpha = fmax(alpha, eval);
            if ( alpha >= beta)
                break;
        }
        cout << bestMove.iPosition << " to " << bestMove.fPosition << "\n";
        return maxEval;
    }
    if (player == RED){
        double minEval = INF;
        double eval = minEval;
        Move bestMove;
        vector<Move> pM = board.possibleMoves();
        for (Move x: pM){
            CheckerBoard clone = board.copy();
            clone.makeMove(x.iPosition, x.fPosition, x.c);
            eval = minimax(clone, depth - 1, alpha, beta, BLACK);
            if (eval < minEval){
                minEval = eval;
                bestMove.iPosition = x.iPosition;
                bestMove.fPosition = x.fPosition;
                bestMove.c = x.c;
            }
            beta = fmin(beta, eval);
            if ( alpha >= beta)
                break;
        }
        cout << bestMove.iPosition << " to " << bestMove.fPosition << "\n";
        return minEval;
    }


}

int main() {
    std::cout << "Hello, World!" << std::endl;
    int x = 0, x2=0;
    CheckerBoard CB;
    CB.printBoard();
    char colours[] = {'B', 'R'};
    int turnNumber = 0;
    int result;
    while(x!=-1||x2!=-1) {
        if (turnNumber%2) {
            printf("You are on the red side. Please enter the coordinates of the piece you want to move: \n");
        }
        else {
            printf("You are on the black side. Please enter the coordinates of the piece you want to move: \n");
        }
        scanf("%d", &x);
        printf("Please enter the position you want to move to \n");
        scanf("%d", &x2);
        result = CB.makeMove(x, x2, colours[turnNumber%2]);
        if (result>0){
            turnNumber++;
        }
        else{
            printf("Try again \n");
        }
        CB.printBoard();
        vector<Move> pM = CB.possibleMoves();
        printf("%d", pM.size());
        for(int i=0; i<pM.size(); i++) {printf("%d, %d \n", pM[i].iPosition, pM[i].fPosition, pM[i].c);}

    }
    return 0;
}
