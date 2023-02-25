#include <iostream>
#include <fstream>
#include <conio.h>
#include <string>

#include "Printer.h"
#include "Game.h"
#include "GameSerializer.h"

using namespace std;

enum Keys {
	QuitKey = 113,
	RestartKey = 114,
	SaveKey = 115,
};

bool is_arrow_key(int key) {
	if (key == LEFT || key == RIGHT || key == UP || key == DOWN) {
		return true;
	}

	return false;
}

bool file_exists(string file_path) {
	ifstream file;
	file.open(file_path);

	if (file) {
		return true;
	}

	return false;
}

int main() {
	string file_path;
	cout << "Please, enter your last saved game file (print 'new' if you want to start new): ";
	cin >> file_path;

	Game* game;
	GameSerializer serializer;

	if (file_path == "new") {
		game = new Game(4, 4);
	}
	else {
		game = serializer.deserialize(file_path);
	}

	Printer printer;
	printer.print_game(*game);

	while (true) {
		int key = _getch();

		if (is_arrow_key(key)) {
			game->move((Direction)key);
			printer.print_game(*game);
		}
		if (key == RestartKey) {
			game->reset();
			printer.print_game(*game);
		}
		if (key == QuitKey) {
			break;
		}
		if (key == SaveKey) {
			cout << "Please, enter save file path: ";
			cin >> file_path;

			serializer.serialize(*game, file_path);

			printer.print_game(*game);
		}
	}

	delete game;
}
