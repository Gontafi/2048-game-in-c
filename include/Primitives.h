#pragma once



enum Direction {
	LEFT = 75,
	RIGHT = 77,
	UP = 72,
	DOWN = 80,
};

enum GameState {
	Run,
	Won,
	Lost
};

struct Index2D {
	int X;
	int Y;

	template<class T>
	T& get(T** matrix) {
		return matrix[Y][X];
	}

	template<class T>
	void set(T** matrix, const T& value) {
		matrix[Y][X] = value;
	}

	bool is_out_of_range(int rows, int columns) {
		if (X < 0 || X >= columns) {
			return true;
		}

		if (Y < 0 || Y >= rows) {
			return true;
		}

		return false;
	}

	Index2D neighbour_at(Direction direction) {
		switch (direction) {
		case LEFT:
			return Index2D{ X - 1, Y };
			break;

		case RIGHT:
			return Index2D{ X + 1, Y };
			break;

		case UP:
			return Index2D{ X, Y - 1 };
			break;

		case DOWN:
			return Index2D{ X, Y + 1 };
			break;
		}
	}
};
