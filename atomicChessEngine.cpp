#include <iostream>
#include <vector>

using namespace std;

wchar_t pieces[] = { L'♔', L'♕', L'♖', L'♗', L'♘', L'♙', L'♚', L'♛', L'♜', L'♝', L'♞', L'p' };
wchar_t tiles[] = { L'■', L'□' };
wchar_t validTiles[] = { L'◙', L'○'};


class Console {
public:
	void logError(string err) {
		cout << "ERROR: " << err << endl;
	}

	void log(string log) {
		cout << "LOG: " << log << endl;
	}
};


struct Position {
	int x;
	int y;
};

struct Move {
	Position from;
	Position to;
};

class Board {
	int board[8][8];
	bool isWhite = true;
	Console boardConsole;
	bool result = 0;

public:
	void initialize() {
		int setupBoard[8][8] = {
			{2,4,3,1,0,3,4,2},
			{5,5,5,5,5,5,5,5},
			{-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1},
			{-1,-1,-1,-1,-1,-1,-1,-1},
			{11,11,11,11,11,11,11,11},
			{8,10,9,7,6,9,10,8}
		};

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				board[i][j] = setupBoard[i][j];
			}
		}
		boardConsole = Console();
	}

	void display() {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (board[i][j] == -1) {
					std::wcout << tiles[(i + j) % 2];
				}
				else {
					std::wcout << pieces[board[i][j]];
				}
			}
			std::wcout << " " << char(i + 65);
			std::wcout << endl;
		}

		for (int i = 1; i <= 8; i++) {
			std::wcout << i;
		}
		std::wcout << endl;
	}

	bool movesContainPos(vector<Position> moves, Position pos) {
		for (int i = 0; i < moves.size(); i++) {
			if (moves[i].x == pos.x && moves[i].y == pos.y) {
				return true;
			}
		}
		return false;
	}

	void displayWithMoves(vector<Position> moves) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (movesContainPos(moves, { j, i })) {
					std::wcout << validTiles[(i + j) % 2];
				}
				else if (board[i][j] == -1) {
					std::wcout << tiles[(i + j) % 2];
				}
				else {
					std::wcout << pieces[board[i][j]];
				}
				
			}
			std::wcout << " " << char(i + 65);
			std::wcout << endl;
		}

		for (int i = 1; i <= 8; i++) {
			std::wcout << i;
		}
		std::wcout << endl;
	}

	int pieceType(Position pos) {
		return board[pos.y][pos.x];
	}

	bool thisWhite(Position pos) {
		return pieceType(pos) < 6;
	}

	int indexOnPos(Position pos) {
		return pos.y * 8 + pos.x;
	}

	Position posOnIndex(int index) {
		return { index - index / 8, index / 8 };
	}

	vector<Position> validMoves(Position pos) {
		vector<Position> ret;
		if (pieceType(pos) == 8 || pieceType(pos) == 2 || pieceType(pos) == 1 || pieceType(pos) == 7) { // rook queen
			for (int x = pos.x + 1; x < 8; x++) {
				if (pieceType({ x, pos.y }) == -1) {
					ret.push_back({ x, pos.y });
				}
				else if (thisWhite({ x, pos.y }) != thisWhite(pos)) {
					ret.push_back({ x, pos.y });
					break;
				}
				else {
					break;
				}
			}
			for (int x = pos.x - 1; x >= 0; x--) {
				if (pieceType({ x, pos.y }) == -1) {
					ret.push_back({ x, pos.y });
				}
				else if (thisWhite({ x, pos.y }) != thisWhite(pos)) {
					ret.push_back({ x, pos.y });
					break;
				}
				else {
					break;
				}
			}
			for (int y = pos.y + 1; y < 8; y++) {
				if (pieceType({ pos.x, y }) == -1) {
					ret.push_back({ pos.x, y });
				}
				else if (thisWhite({ pos.x, y }) != thisWhite(pos)) {
					ret.push_back({ pos.x, y });
					break;
				}
				else {
					break;
				}
			}
			for (int y = pos.y - 1; y >= 0; y--) {
				if (pieceType({ pos.x, y }) == -1) {
					ret.push_back({ pos.x, y });
				}
				else if (thisWhite({ pos.x, y }) != thisWhite(pos)) {
					ret.push_back({ pos.x, y });
					break;
				}
				else {
					break;
				}
			}
		}
		else if (pieceType(pos) == 3 || pieceType(pos) == 9 || pieceType(pos) == 1 || pieceType(pos) == 7) { //bishop queen
			for (int index = indexOnPos(pos) - 7; index >= 0; index -= 7) {
				if (pieceType(posOnIndex(index)) == -1) {
					ret.push_back(posOnIndex(index));
				}
				else if (thisWhite(posOnIndex(index)) != thisWhite(pos)) {
					ret.push_back(posOnIndex(index));
					break;
				}
				else {
					break;
				}
			}
			for (int index = indexOnPos(pos) + 7; index >= 0; index += 7) {
				if (pieceType(posOnIndex(index)) == -1) {
					ret.push_back(posOnIndex(index));
				}
				else if (thisWhite(posOnIndex(index)) != thisWhite(pos)) {
					ret.push_back(posOnIndex(index));
					break;
				}
				else {
					break;
				}
			}
			for (int index = indexOnPos(pos) - 9; index >= 0; index -= 9) {
				if (pieceType(posOnIndex(index)) == -1) {
					ret.push_back(posOnIndex(index));
				}
				else if (thisWhite(posOnIndex(index)) != thisWhite(pos)) {
					ret.push_back(posOnIndex(index));
					break;
				}
				else {
					break;
				}
			}
			for (int index = indexOnPos(pos) + 9; index >= 0; index += 9) {
				if (pieceType(posOnIndex(index)) == -1) {
					ret.push_back(posOnIndex(index));
				}
				else if (thisWhite(posOnIndex(index)) != thisWhite(pos)) {
					ret.push_back(posOnIndex(index));
					break;
				}
				else {
					break;
				}
			}
		}
		else if (pieceType(pos) == 4 || pieceType(pos) == 10) { //knight
			for (int i = -1; i <= 1; i += 2) {
				for (int j = -1; j <= 1; j += 2) {
					if (pos.x - 2 * i >= 0 && pos.x - 2 * i < 8) {
						if (pos.y - 1 * j >= 0 && pos.y - 1 * j < 8) {
							if (thisWhite(pos) != thisWhite({ pos.x - 2 * i, pos.y - 1 * j }) || pieceType({ pos.x - 2 * i, pos.y - 1 * j }) == -1) {
								ret.push_back({ pos.x - 2 * i, pos.y - 1 * j });
							}
						}
					}
				}
			}
			for (int i = -1; i <= 1; i += 2) {
				for (int j = -1; j <= 1; j += 2) {
					if (pos.y - 2 * i >= 0 && pos.y - 2 * i < 8) {
						if (pos.x - 1 * j >= 0 && pos.x - 1 * j < 8) {
							if (thisWhite(pos) != thisWhite({pos.x - 1 * j, pos.y - 2 * i }) || pieceType({ pos.x - 1 * j, pos.y - 2 * i }) == -1) {
								ret.push_back({ pos.x - 1 * j, pos.y - 2 * i });
							}
						}
					}
				}
			}
		}
		else if (pieceType(pos) == 5) { // white pown
			if (pieceType({ pos.x, pos.y + 1 }) == -1) { 
				ret.push_back({ pos.x, pos.y + 1 });
			}
			if (thisWhite({ pos.x - 1, pos.y + 1 }) != thisWhite(pos)) {
				ret.push_back({ pos.x - 1, pos.y + 1 });
			}
			if (thisWhite({ pos.x + 1, pos.y + 1 }) != thisWhite(pos)) {
				ret.push_back({ pos.x + 1, pos.y + 1 });
			}
		}
		else if(pieceType(pos) == 11) { // black pown
			if (pieceType({ pos.x, pos.y - 1 }) == -1) {
				ret.push_back({ pos.x, pos.y - 1 });
			}
			if (pieceType({ pos.x, pos.y - 2 }) == -1 && pos.y == 6) {
				ret.push_back({ pos.x, pos.y - 2 });
			}
			if (thisWhite({ pos.x - 1, pos.y - 1 }) != thisWhite(pos) && pieceType({ pos.x - 1, pos.y - 1 }) != -1) {
				ret.push_back({ pos.x - 1, pos.y - 1 });
			}
			if (thisWhite({ pos.x + 1, pos.y - 1 }) != thisWhite(pos) && pieceType({ pos.x - 1, pos.y - 1 }) != -1) {
				ret.push_back({ pos.x + 1, pos.y - 1 });
			}
		}
		else if (pieceType(pos) == 0 || pieceType(pos) == 6) { // king
			for (int i = -1; i <= 1; i ++) {
				for (int j = -1; j <= 1; j++) {
					if (i != 0 && j != 0) {
						if (pos.x - i >= 0 && pos.x - i < 8) {
							if (pos.y - j >= 0 && pos.y - j < 8) {
								if (pieceType({ pos.x - i, pos.y - j }) == -1) {
									ret.push_back({ pos.x - i, pos.y - j });
								}
							}
						}
					}
				}
			}
		}
		return ret;
	}



	vector<Position> selectPiece(Position pos) {
		if (thisWhite(pos) == isWhite) {
			vector<Position> poss = validMoves(pos);
			displayWithMoves(poss);
			return poss;
		}
		else {
			boardConsole.logError("Not your piece");
			return {};
		}
	}

	bool canMove(Position pos, vector<Position> validPositions) {
		for (int i = 0; i < validPositions.size(); i++) {
			if (validPositions[i].x == pos.x && validPositions[i].y == pos.y) {
				return true;
			}
		}
		return false;
	}

	void assignToBoard(Position pos, int val) {
		board[pos.y][pos.x] = val;
	}

	void blow(Position pos, bool isPieceWhite) {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				if (pos.x - i >= 0 && pos.x - i < 8) {
					if (pos.y - j >= 0 && pos.y - j < 8) {
						if (pieceType({ pos.x - i, pos.y - j }) == 0 || pieceType({ pos.x - i, pos.y - j }) == 6) {
							result = -1 + 2 * isPieceWhite;
							assignToBoard({ pos.x - i, pos.y - j }, -1);
							return;
						}
						else if (pieceType({ pos.x - i, pos.y - j }) == 5 || pieceType({ pos.x - i, pos.y - j }) == 11) { //pawns
							continue;
						}
						else {
							assignToBoard({ pos.x - i, pos.y - j }, -1);
						}
					}
				}
			}
		}
	}

	void movePiece(Position from, vector<Position> validPositions, Position to) {
		if (canMove(to, validPositions)){
			if (pieceType(to) == -1){
				assignToBoard(to, pieceType(from));
			}
			else {
				blow(to, thisWhite(to));
				assignToBoard(to, -1);
			}
			assignToBoard(from, -1);
			isWhite = !isWhite;
			display();
			if (result == 0) {
				
				if (isWhite) {
					boardConsole.log("White to move: ");
				}
				else {
					boardConsole.log("Black to move: ");
				}
				char move[2];
				cin >> move;
				int x = move[0] - 65;
				int y = move[1] - 49;
				Position pos = { y, x };
				vector<Position> poss = selectPiece(pos);
				char too[2];
				cin >> too;
				x = too[0] - 65;
				y = too[1] - 49;
				Position posTo = { y, x };
				movePiece(pos, poss, posTo);
			}
		}
		else {
			boardConsole.logError("Not valid move");
			if (isWhite) {
				boardConsole.log("White to move: ");
			}
			else {
				boardConsole.log("Black to move: ");
			}
			char move[2];
			cin >> move;
			int x = move[0] - 65;
			int y = move[1] - 49;
			Position pos = { y, x };
			vector<Position> poss = selectPiece(pos);
			char too[2];
			cin >> too;
			x = too[0] - 65;
			y = too[1] - 49;
			Position posTo = { y, x };
			movePiece(pos, poss, posTo);
		}
	}


};


int main() {
	
	std::locale::global(std::locale("en_US.UTF-8"));
	std::wcout.imbue(std::locale());
	system("chcp 65001");
	system("color f0");

	Board board = Board();
	board.initialize();
	board.display();
	char move[2];
	cin >> move;
	int x = move[0] - 65;
	int y = move[1] - 49;
	Position pos = { y, x };
	cout << pos.x << ' ' << pos.y << endl;
	vector<Position> poss = board.selectPiece(pos);
	char too[2];
	cin >> too;
	x = too[0] - 65;
	y = too[1] - 49;
	Position posTo = { y, x };
	board.movePiece(pos, poss, posTo);
}