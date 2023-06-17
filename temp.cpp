#include <iostream>
#include<climits>
#include <vector>

using namespace std;

// The board is represented by a 3x3 matrix
char board[3][3];

// Constants for player and AI
const char PLAYER = 'X';
const char AI = 'O';

// Function to initialize the board
void initializeBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

// Function to print the board
void printBoard() {
    for (int i = 0; i < 3; i++) {
        cout << " " << board[i][0] << " | " << board[i][1] << " | " << board[i][2] << " " << endl;
        if (i != 2)
            cout << "-----------" << endl;
    }
    cout << endl;
}

// Function to check if the board is full
bool isBoardFull() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                return false;
        }
    }
    return true;
}

// Function to check if there is a win
bool checkWin(char player) {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
            return true;
    }

    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
            return true;
    }

    // Check diagonals
    if (board[0][0] == player && board[1][1] == player && board[2][2] == player)
        return true;

    if (board[2][0] == player && board[1][1] == player && board[0][2] == player)
        return true;

    return false;
}

// Function to get all possible moves
vector<pair<int, int>> getValidMoves() {
    vector<pair<int, int>> validMoves;

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ')
                validMoves.push_back(make_pair(i, j));
        }
    }

    return validMoves;
}

// Alpha-Beta algorithm
int alphaBeta(bool maximizingPlayer) {
    if (checkWin(PLAYER))
        return -1;

    if (checkWin(AI))
        return 1;

    if (isBoardFull())
        return 0;

    if (maximizingPlayer) {
        int maxEval = INT_MIN;

        vector<pair<int, int>> moves = getValidMoves();
        for (const auto& move : moves) {
            int row = move.first;
            int col = move.second;

            board[row][col] = AI;
            int eval = alphaBeta(false);
            board[row][col] = ' ';

            maxEval = max(maxEval, eval);
        }

        return maxEval;
    } else {
        int minEval = INT_MAX;

        vector<pair<int, int>> moves = getValidMoves();
        for (const auto& move : moves) {
            int row = move.first;
            int col = move.second;

            board[row][col] = PLAYER;
            int eval = alphaBeta(true);
            board[row][col] = ' ';

            minEval = min(minEval, eval);
        }

        return minEval;
    }
}

// Function to make AI move
void makeAIMove() {
    int maxEval = INT_MIN;
    pair<int, int> bestMove;

    vector<pair<int, int>> moves = getValidMoves();
    for (const auto& move : moves) {
        int row = move.first;
        int col = move.second;

        board[row][col] = AI;
        int eval = alphaBeta(false);
        board[row][col] = ' ';

        if (eval > maxEval) {
            maxEval = eval;
            bestMove = move;
        }
    }

    int row = bestMove.first;
    int col = bestMove.second;
    board[row][col] = AI;
}

// Function to make player move
void makePlayerMove() {
    int row, col;
    cout << "Enter your move (row and column): ";
    cin >> row >> col;

    while (row < 1 || row > 3 || col < 1 || col > 3 || board[row - 1][col - 1] != ' ') {
        cout << "Invalid move. Enter your move (row and column): ";
        cin >> row >> col;
    }

    board[row - 1][col - 1] = PLAYER;
}

// Main function
int main() {
    initializeBoard();

    while (!isBoardFull() && !checkWin(PLAYER) && !checkWin(AI)) {
        printBoard();

        makePlayerMove();

        if (isBoardFull() || checkWin(PLAYER) || checkWin(AI))
            break;

        makeAIMove();
    }

    printBoard();

    if (checkWin(PLAYER))
        cout << "Congratulations! You won!" << endl;
    else if (checkWin(AI))
        cout << "Sorry, you lost. AI won!" << endl;
    else
        cout << "It's a draw!" << endl;

    return 0;
}

