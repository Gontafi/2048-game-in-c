#include "GameSerializer.h"

#include <iostream>
#include <fstream>

using namespace std;

void GameSerializer::serialize(Game& game, const string& file_path) {
	ofstream file(file_path, ios_base::binary);

	int rows = game.get_rows();
	int columns = game.get_columns();
	int score = game.get_score();

	file.write((char*)&rows, sizeof(int));
	file.write((char*)&columns, sizeof(int));
	file.write((char*)&score, sizeof(int));

	for (int i = 0; i < game.get_rows(); i++) {
		int* row = game.get_row(i);

		for (int j = 0; j < game.get_columns(); j++) {
			file.write((char*)(row + j), sizeof(int));
		}
	}
}

Game* GameSerializer::deserialize(const string& file_path) {
	ifstream file(file_path, ios_base::binary);

	int rows, columns, score;
	file.read((char*)&rows, sizeof(int));
	file.read((char*)&columns, sizeof(int));
	file.read((char*)&score, sizeof(int));

	int** cells = new int* [rows];
	for (int i = 0; i < rows; i++) {
		cells[i] = new int[columns];

		for (int j = 0; j < columns; j++) {
			file.read((char*)(cells[i] + j), sizeof(int));
		}
	}

	return new Game(rows, columns, score, cells);
}
