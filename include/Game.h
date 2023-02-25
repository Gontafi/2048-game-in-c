#ifndef GAME_H
#define GAME_H

#pragma once


#include "Primitives.h"
#include <vector>
#include <stdlib.h>

class Game {

private:

	int** cells;
	int rows;
	int columns;
	int score;

	Index2D get_random_empty_cell();

	void spawn_two_or_four();

	bool can_move();

	bool has_at_least_one_cell_of(int value);

	bool has_at_least_one_mergeable_cell();

	bool can_be_merged_to(Index2D cell, Direction direction);

	Index2D get_stopping_point(Index2D cell, Direction direction);

	void process_move(Direction direction);

	void left();
	void right();
	void up();
	void down();

	void transition(Index2D cell, Direction direction);

public:

	Game(int rows, int columns);
	Game(int rows, int columns, int score, int** cells);

	GameState get_current_state();

	void move(Direction direction);

	void reset();

	~Game();

	int* get_row(int row);

	int get_score();
	int get_rows();
	int get_columns();
	int value_at(int row, int column);
};
#endif // GAME_H
