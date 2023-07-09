#include "MainLoop.h"
#include <iostream>


int main(int argc, char* args[])
{
	char playerSide;
	std::cout << "Choose your color (W - white, B - black)" << std::endl;
	std::cin >> playerSide;

	char isPlayingVsBotChar;
	bool isPlayingVsBot;
	std::cout << "Do you want to play vs AI (Y - yes, N - no)" << std::endl;
	std::cin >> isPlayingVsBotChar;

	if (isPlayingVsBotChar == 'Y' || isPlayingVsBotChar == 'y')isPlayingVsBot = true;
	else isPlayingVsBot = false;

	MainLoop::Run(playerSide, isPlayingVsBot);
	return 0;
}
