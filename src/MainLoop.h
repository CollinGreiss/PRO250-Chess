#pragma once

#include "Game.h"

class MainLoop {
public:

	static void Run(char playerSide = 'W', bool isPlayingVsBot = false, Game::Variant variant = Game::Variant::NORMAL);

};

