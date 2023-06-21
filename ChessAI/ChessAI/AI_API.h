#pragma once
#include <string>
#include <vector>

class AI_API
{
public:
	AI_API();
	~AI_API();

	void GetUserInput(std::string userMove);
	std::string CalcAIMove();

};

