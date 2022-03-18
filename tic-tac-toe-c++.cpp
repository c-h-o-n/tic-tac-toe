/**
 * Author: Ducsai Bálint
 * Date: 2018.11.07.
 * Task: Tic-Tac-Toe, prog1
 * IDE: Atom /w gpp-compiler
**/

//TODO: avoid goto 
//TODO: function prototyping!!!
//BUG: Visual Studio 2019 compiles differently: inputCheck works odd

#include <iostream>
#include <string>
#include <iomanip>    //setw(), setfill()
#include <conio.h>    //_getch()
#include <windows.h>  //hConsole, system()

using namespace std;

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

char map[10][10]; // map[row][col]
char winPos[10][10]; //to save winning marks' position(coloring)

char  winType,
option;
int turnCounter = 0;

//DRAWs startscreen
void startscreen() {
	cout << endl << "\t  _______ _____ _______     _______ _______ _______     _______  _____  _______\n\t     |      |   |       ___    |    |_____| |       ___    |    |     | |______\n\t     |    __|__ |_____         |    |     | |_____         |    |_____| |______\n";
	cout << endl << endl << setw(23);

	char about[] = { "This is a 2 player tic-tac-toe game on a 10x10 board.  \n" };
	for (int x = 0; x < sizeof(about); x++) {
		cout << about[x];
		Sleep(20);
	}
	cout << endl << setw(58) << "Press <Enter> to start." << endl;
	while (option != 13) {
		option = _getch();
	}
}

//LOADs map matrix with '.'
void loadMap() {
	turnCounter = 0;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			map[i][j] = '.';
			winPos[i][j] = 0;
		}
	}
}

//CHECKs if input is valid
bool inputCheck(int x, int y) {
	if (map[x - 1][y - 1] == '.' && (x > 0 && x < 11) && (y > 0 && y < 11)) {
		return true;
	}
}
//SAVEs input to map[x][y]
void applyInput(int x, int y, int player) {
	if (player == 0) {
		map[x][y] = 'x';
	} else {
		map[x][y] = 'o';
	}
}

//CHECKs if there is a winner
bool checkWinner() {
	char  checkMark;
	if (turnCounter % 2 == 0) {
		checkMark = 'o';
	} else {
		checkMark = 'x';
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			//check horizontal
			if (j + 4 < 10 && map[i][j] == checkMark && map[i][j + 1] == checkMark && map[i][j + 2] == checkMark && map[i][j + 3] == checkMark && map[i][j + 4] == checkMark) {
				winPos[i][j] = map[i][j];
				winPos[i][j + 1] = map[i][j + 1];
				winPos[i][j + 2] = map[i][j + 2];
				winPos[i][j + 3] = map[i][j + 3];
				winPos[i][j + 4] = map[i][j + 4];
				return true;
			//check vertical
			} else if (i + 4 < 10 && map[i][j] == checkMark && map[i + 1][j] == checkMark && map[i + 2][j] == checkMark && map[i + 3][j] == checkMark && map[i + 4][j] == checkMark) {
				winPos[i][j] = map[i][j];
				winPos[i + 1][j] = map[i + 1][j];
				winPos[i + 2][j] = map[i + 2][j];
				winPos[i + 3][j] = map[i + 3][j];
				winPos[i + 4][j] = map[i + 4][j];
				return true;
			//check right-diagonal
			} else if (i + 4 < 10 && j + 4 < 10 && map[i][j] == checkMark && map[i + 1][j + 1] == checkMark && map[i + 2][j + 2] == checkMark && map[i + 3][j + 3] == checkMark && map[i + 4][j + 4] == checkMark) {
				winPos[i][j] = map[i][j];
				winPos[i + 1][j + 1] = map[i + 1][j + 1];
				winPos[i + 2][j + 2] = map[i + 2][j + 2];
				winPos[i + 3][j + 3] = map[i + 3][j + 3];
				winPos[i + 4][j + 4] = map[i + 4][j + 4];
				return true;
			//check left-diagonal
			} else if (i + 4 < 10 && j - 4 > 0 && map[i][j] == checkMark && map[i + 1][j - 1] == checkMark && map[i + 2][j - 2] == checkMark && map[i + 3][j - 3] == checkMark && map[i + 4][j - 4] == checkMark) {
				winPos[i][j] = map[i][j];
				winPos[i + 1][j - 1] = map[i + 1][j - 1];
				winPos[i + 2][j - 2] = map[i + 2][j - 2];
				winPos[i + 3][j - 3] = map[i + 3][j - 3];
				winPos[i + 4][j - 4] = map[i + 4][j - 4];
				return true;
			}
		}
	}
	return false;
}
//CHECKs if the game end with a draw
bool checkTie() {
	bool isTie = true;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (map[i][j] == '.') {
				isTie = false;
			}
		}
	}

	if (isTie == true) {
		return true;
	} else {
		return false;
	}
}

//DRAWs the game + input
void drawGame() {
error_handle:
	system("cls");
	int xPos,
		yPos;

	cout << turnCounter + 1 << ". turn\n";
	cout << "Player 1: x" << "  Player 2: o" << endl << endl;

	cout << "#######################";
	for (int i = 0; i < 10; i++) {
		cout << endl;
		cout << "#";
		for (int j = 0; j < 10; j++) {
			cout << "|";
			if ((winPos[i][j] == 'x' || winPos[i][j] == 'o') && checkWinner()) {
				SetConsoleTextAttribute(hConsole, 10);
				cout << winPos[i][j];
				SetConsoleTextAttribute(hConsole, 7);
			} else {
				cout << map[i][j];
			}
		}
		cout << "|#";
	}
	cout << endl << "#######################" << endl << endl;

	if (!checkWinner()) {
		if (turnCounter % 2 == 0) {
			cout << "Player 1's turn\n";
		} else {
			cout << "Player 2's turn\n";
		}
		do {
			cout << "Enter row number: ";
			cin >> xPos;
			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "Not a valid position.";
				Sleep(1100);
				goto error_handle;
			}
			cout << "Enter column number: ";
			cin >> yPos;
			if (cin.fail()) {
				cin.clear();
				cin.ignore();
				cout << "Not a valid position.";
				Sleep(1100);
				goto error_handle;
			}
			if (!inputCheck(xPos, yPos)) {
				cout << "Not a valid position.";
				Sleep(1100);
				goto error_handle;
			}
		} while (!inputCheck(xPos, yPos));


		applyInput(xPos - 1, yPos - 1, turnCounter % 2);
		turnCounter++;
	}
}


int main() {
	startscreen();
restart:
	loadMap();
	do {
		drawGame();
	} while (!checkWinner() && !checkTie());
	drawGame(); //to draw the last turn;

	//Game Over
	if (checkWinner()) {
		if (turnCounter % 2) {
			cout << "The winner is Player 1(x)" << endl;
		} else {
			cout << "The winner is Player 2(o)" << endl;
		}
	} else {
		cout << "The game is a draw" << endl;
	}

	cout << "\nPress <Enter> to restart\nPress <Esc> to exit\n";
	option = 0;
	while (option != 13 && option != 27) {
		option = _getch();
	}
	if (option == 13) {
		goto restart;
	}
	else {
		return 0;
	}
	//system("pause");
}
