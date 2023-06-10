#include "MainLoop.h"
#include <iostream>

int main(int argc, char* args[])
{
	char playerSide;
	std::cout << "Choose your color (W - white, B - black)" << std::endl;
	std::cin >> playerSide;

	MainLoop::Run(playerSide);
	return 0;
}
