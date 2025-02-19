#include "MainLoop.h"
#include <iostream>


int main(int argc, char* args[]) {

	char playerSide;

	std::cout << "Choose your color (W - white, B - black)" << std::endl;
	std::cin >> playerSide;


	while (playerSide != 'W' && playerSide != 'B') {

		std::cout << "Invalid input, please try again" << std::endl;
		std::cout << "Choose your color (W - white, B - black)" << std::endl;
		std::cin >> playerSide;

	}

	char isPlayingVsBotChar;
	bool isPlayingVsBot;
	std::cout << "Do you want to play vs AI (Y - yes, N - no)" << std::endl;
	std::cin >> isPlayingVsBotChar;

	while (isPlayingVsBotChar != 'Y' && isPlayingVsBotChar != 'N') {

		std::cout << "Invalid input, please try again" << std::endl;
		std::cout << "Do you want to play vs AI (Y - yes, N - no)" << std::endl;
		std::cin >> isPlayingVsBotChar;

	}

	if (isPlayingVsBotChar == 'Y' || isPlayingVsBotChar == 'y')isPlayingVsBot = true;
	else isPlayingVsBot = false;

	Game::Variant variant;
	char variantChar;
	
	std::cout << "Choose the variant (1 - normal, 2 - chess960)" << std::endl;
	std::cin >> variantChar;

	while (variantChar != '1' && variantChar != '2') {

		std::cout << "Invalid input, please try again" << std::endl;
		std::cout << "Choose the variant (1 - normal, 2 - chess960)" << std::endl;
		std::cin >> variantChar;

	}

	if (variantChar == '1') variant = Game::Variant::NORMAL;
	else variant = Game::Variant::CHESS960;

	MainLoop::Run(playerSide, isPlayingVsBot, variant);
	return 0;

}
