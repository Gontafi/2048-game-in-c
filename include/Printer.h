#pragma once

#include "Game.h"

class Printer {
	void print_times(char c, int count);
	void draw_line(int length);
	void draw_cell_surronding_line(int columns);
	int get_spaces_before_number(int number_length);
	int get_number_length(int number);
	void draw_cell_line(int* row, int columns);
public:
	void print_game(Game& game);
};

