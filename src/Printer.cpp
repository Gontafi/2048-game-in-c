#include <iostream>
#include "Printer.h"

using namespace std;

const int CELL_WIDTH = 6;

void Printer::print_times(char c, int count) {
	for (int i = 0; i < count; i++) cout << c;
}

void Printer::draw_line(int length) {
	print_times('-', length);
	cout << endl;
}

void Printer::draw_cell_surronding_line(int columns) {
	for (int i = 0; i < columns; i++) {
		cout << "|      ";
	}

	cout << '|' << endl;
}

int Printer::get_spaces_before_number(int number_length) {
	return CELL_WIDTH - number_length - 1;
}

// works only on positive integers
int Printer::get_number_length(int number) {
	if (number == 0) {
		return 1;
	}

	int length = 0;
	while (number > 0) {
		length++;
		number /= 10;
	}

	return length;
}

void Printer::draw_cell_line(int* row, int columns) {
	for (int i = 0; i < columns; i++) {
		cout << '|';

		int length = get_number_length(row[i]);
		int spaces_before_number = get_spaces_before_number(length);
		int spaces_after_number = CELL_WIDTH - length - spaces_before_number;

		print_times(' ', spaces_before_number);
		cout << row[i];
		print_times(' ', spaces_after_number);
	}

	cout << '|' << endl;
}

void Printer::print_game(Game& game) {
	system("cls");

	cout << "    2048 Puzzle Game" << endl;

	GameState state = game.get_current_state();

	if (state == Lost) {
		cout << "\tYou lost..." << endl;
	}
	else if (state == Won) {
		cout << "\tCongrats, you have reached 2048! You won!" << endl;
	}
	else {
		cout << endl;
	}

	cout << "\tScore:  " << game.get_score() << endl;

	const int LINE_LENGTH = (game.get_columns() + 1) * CELL_WIDTH - 1;

	for (int i = 0; i < game.get_rows(); i++) {
		draw_line(LINE_LENGTH);
		draw_cell_surronding_line(game.get_columns());
		draw_cell_line(game.get_row(i), game.get_columns());
		draw_cell_surronding_line(game.get_columns());
	}

	draw_line(LINE_LENGTH);

	cout << "Control Keys:" << endl
		<< "(Up-Arrow)\t\tUp" << endl
		<< "(Down-Arrow)\t\tDown" << endl
		<< "(Right-Arrow)\t\tRight" << endl
		<< "(Left-Arrow)\t\tLeft" << endl << endl
		<< "(R)\t\t\ Restart" << endl
		<< "(S)\t\t\t Save" << endl
		<< "(Q)\t\t\t Quit" << endl;
}
