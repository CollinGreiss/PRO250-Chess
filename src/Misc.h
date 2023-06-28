#pragma once

const char boardXLetters[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h' };

enum class MoveType
{
	NORMAL, 
	CASTLE, 
	ENPASSANT,
	NEWPIECE,
	INIT
};

struct Point
{
	int xCoord, yCoord;
};

struct PossibleMove 
{
	Point MovePos;
    MoveType Move_Type;
};

class Misc
{
};

