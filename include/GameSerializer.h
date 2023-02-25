#pragma once

#include <string>

#include "Game.h"

class GameSerializer {
public:
	void serialize(Game& game, const std::string& file_path);

	Game* deserialize(const std::string& file_path);
};
