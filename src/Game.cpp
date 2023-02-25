#include "Game.h"

Game::Game(int rows, int columns) {
	this->rows = rows;
	this->columns = columns;
	score = 0;

	cells = new int* [rows];

	for (int i = 0; i < rows; i++) {
		cells[i] = new int[columns];
	}

	reset();
}

Game::Game(int rows, int columns, int score, int** cells) {
	this->rows = rows;
	this->columns = columns;
	this->score = score;
	this->cells = cells;
}

void Game::move(Direction direction)
{
	GameState state = get_current_state();

	if (state == Run) {
		process_move(direction);

		if (has_at_least_one_cell_of(0)) {
			spawn_two_or_four();
		}
	}
}

void Game::reset() {
	score = 0;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			cells[i][j] = 0;
		}
	}

	spawn_two_or_four();
	spawn_two_or_four();
}

void Game::spawn_two_or_four() {
	auto index = get_random_empty_cell();

    if(rand() % 100 < 50){
        index.set(cells, 2);
    }
    else{
        index.set(cells, 4);
    }
}

GameState Game::get_current_state() {
	if (has_at_least_one_cell_of(2048)) {
		return Won;
	}

	if (!can_move()) {
		return Lost;
	}

	return Run;
}

bool Game::has_at_least_one_cell_of(int value)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (cells[i][j] == value) {
				return true;
			}
		}
	}

	return false;
}

bool Game::can_move() {
	if (has_at_least_one_cell_of(0)) {
		return true;
	}

	return has_at_least_one_mergeable_cell();
}

bool Game::has_at_least_one_mergeable_cell() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Index2D cell = Index2D{ j, i };

			if (can_be_merged_to(cell, LEFT) ||
				can_be_merged_to(cell, RIGHT) ||
				can_be_merged_to(cell, UP) ||
				can_be_merged_to(cell, DOWN)) {
				return true;
			}
		}
	}

	return false;
}

bool Game::can_be_merged_to(Index2D cell, Direction direction) {
	Index2D neighbour = cell.neighbour_at(direction);

	if (neighbour.is_out_of_range(rows, columns)) {
		return false;
	}

	return neighbour.get(cells) == cell.get(cells);
}

Index2D Game::get_stopping_point(Index2D cell, Direction direction) {
	while (!cell.neighbour_at(direction).is_out_of_range(rows, columns) &&
			cell.neighbour_at(direction).get(cells) == 0)
	{
		cell = cell.neighbour_at(direction);
	}

	return cell;
}

void Game::process_move(Direction direction) {
	switch (direction) {
	case UP:
		up();
		break;
	case DOWN:
		down();
		break;
	case LEFT:
		left();
		break;
	case RIGHT:
		right();
		break;
	}
}

void Game::left() {
	for (int i = 0; i < rows; i++) {
		for (int j = 1; j < columns; j++) {
			Index2D index = { j, i };

			transition(index, LEFT);
		}
	}
}

void Game::right() {
	for (int i = 0; i < rows; i++) {
		for (int j = columns - 2; j >= 0; j--) {
			Index2D index = { j, i };

			transition(index, RIGHT);
		}
	}
}

void Game::up() {
	for (int i = 1; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			Index2D index = { j, i };

			transition(index, UP);
		}
	}
}

void Game::down() {
	for (int i = rows - 2; i >= 0; i--) {
		for (int j = 0; j < columns; j++) {
			Index2D index = { j, i };

			transition(index, DOWN);
		}
	}
}

void Game::transition(Index2D cell, Direction direction) {
	int value = cell.get(cells);

	if (value != 0) {
		Index2D stop = get_stopping_point(cell, direction);

		cell.set(cells, 0);
		stop.set(cells, value);

		Index2D neighbour = stop.neighbour_at(direction);

		if (!neighbour.is_out_of_range(rows, columns) &&
			neighbour.get(cells) == value) {
			stop.set(cells, 0);
			neighbour.set(cells, value * 2);

			score += value * 2;
		}
	}
}

Game::~Game() {
	for (int i = 0; i < rows; i++) {
		delete[] cells[i];
	}

	delete[] cells;
}

int* Game::get_row(int row) {
	return cells[row];
}

int Game::get_score() {
	return score;
}

int Game::get_rows(){
	return rows;
}

int Game::get_columns() {
	return columns;
}

int Game::value_at(int row, int column) {
	return cells[row][column];
}

Index2D Game::get_random_empty_cell()
{
	std::vector<Index2D> empty_cells;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (cells[i][j] == 0) {
				empty_cells.push_back(Index2D{ j, i });
			}
		}
	}

	return empty_cells.at(rand() % empty_cells.size());
}
