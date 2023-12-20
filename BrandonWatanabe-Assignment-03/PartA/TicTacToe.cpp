#include <iostream>
#include <string>
#include <stringstream>

using namespace std;

bool isWon(char, char[][3]);
bool isDraw(char[][3]);
void displayBoard(char[][3]);
void makeAMove(char[][3], char);

int main() {
	//
	//	PLEASE DO NOT CHANGE function main
	//
	char board[3][3] = { { ' ', ' ', ' ' },{ ' ', ' ', ' ' },{ ' ', ' ', ' ' } };
	displayBoard(board);

	while (true) {

		// The first player makes a move
		makeAMove(board, 'X');
		displayBoard(board);

		if (isWon('X', board)) {
			cout << "X player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}

		// The second player makes a move
		makeAMove(board, 'O');
		displayBoard(board);

		if (isWon('O', board)) {
			cout << "O player won" << endl;
			exit(0);
		}
		else if (isDraw(board)) {
			cout << "No winner" << endl;
			exit(0);
		}
	}

	return 0;
}

bool isWon(char player, char board[][3])
{
	for (int i = 0; i < sizeof(board) - 1; i++)
	{
		if (board[i][0] == player && board[i][1] == player && board[i][2] == player) return true; // horizontal

		for (int j = 0; j < sizeof(board[i]); j++)
		{
			if (board[0][j] == player && board[1][j] == player && board[2][j] == player) return true; // vertical
		}
	}

	if (board[0][0] == player && board[1][1] == player && board[2][2] == player) return true; // diagonal left to right

	else if (board[0][2] == player && board[1][1] == player && board[2][0] == player) return true; // diagonal right to left

	return false;
}

bool isDraw(char board[][3])
{

	for (int i = 0; i < sizeof(board) - 1; i++)
	{
		for (int j = 0; j < sizeof(board[i]); j++)
		{
			if (board[i][j] == ' ') return false; // if board is not full ret false
		}
	}

	return !isWon('X', board) && !isWon('O', board);
}

void displayBoard(char board[][3])
{
	cout << "-------------" << endl;
	for (int i = 0; i < sizeof(board) - 1; i++)
	{
		for (int j = 0; j < sizeof(board[i]); j++)
		{
			cout << "| " << board[i][j] << " |";
		}
		cout << endl;
	}
	cout << "-------------" << endl;
}

void makeAMove(char board[][3], char player) 
{
	int row;
	int col;
	stringstream ss;
	
	ss << "Enter a row (0, 1, 2) for player " << player << ": ";
	string rowPrompt = ss.str();

	ss << "Enter a column (0, 1, 2) for player " << player << ": ";
	string colPrompt = ss.str();

	while (true)
	{
		cout << rowPrompt;
		while (!(cin >> row)) //if input is not a number
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error! Entry is not a number, please enter numbers only." << endl;
			cout << rowPrompt;
		}

		if (row < 0 || row > 2) // if input is not in bounds
		{
			cout << "Error! Entry out of bounds." << endl;
			continue;
		}

		cout << colPrompt;
		while (!(cin >> col)) //if input is not a number
		{
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Error! Entry is not a number, please enter numbers only." << endl;
			cout << colPrompt;
		}

		if (col < 0 || col > 2) // if input is not in bounds
		{
			cout << "Error! Entry out of bounds. Please only enter 0, 1, or 2" << endl;
			continue;
		}

		if (board[row][col] != ' ') // non empty
		{
			cout << "This cell is already occupied. Try a different cell" << endl;
		}

		else // empty cell
		{
			board[row][col] = player;
			break;
		}
	}
}