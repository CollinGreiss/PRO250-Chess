#include "Queen.h"
#include <iostream>

Queen::Queen(Team team, Point pos, SDL_Handler* handler)
	:Piece(team, pos, handler, QUEEN)
{
	std::string filename;
	if (team == BLACK)
	{
		filename = "../res/Chess_qdt60.png";
	}
	else
	{
		filename = "../res/Chess_qlt60.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);
	render();
}


void Queen::sayMyName()
{
	if (m_team == BLACK)
	{
		std::cout << "BLACK QUEEN" << std::endl;
	}
	else
	{
		std::cout << "WHTIE QUEEN" << std::endl;
	}
}

void Queen::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<PossibleMove> moves;
	int dx_copy;
	int dy_copy;
	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			dx_copy = dx;
			dy_copy = dy;
			while (field[m_pos.xCoord + dx_copy][m_pos.yCoord + dy_copy] == nullptr)
			{
				moves = pushMove(moves,
					PossibleMove{ m_pos.xCoord + dx_copy, m_pos.yCoord + dy_copy, MoveType::NORMAL },
					getOwnKing(field),
					field,
					checkCheck);
				if (dx_copy < 0)
				{
					dx_copy -= 1;
				}
				else if (dx_copy > 0)
				{
					dx_copy += 1;
				}
				if (dy_copy < 0)
				{
					dy_copy -= 1;
				}
				else if (dy_copy > 0)
				{
					dy_copy += 1;
				}
			}
			if (field[m_pos.xCoord + dx_copy][m_pos.yCoord + dy_copy] != nullptr
				&& (m_pos.xCoord + dx_copy >= 0 && m_pos.xCoord + dx_copy <= 7 && m_pos.yCoord + dy_copy >= 0 && m_pos.yCoord + dy_copy <= 7))
			{
				if (field[m_pos.xCoord + dx_copy][m_pos.yCoord + dy_copy]->getTeam() != m_team)
				{
					moves = pushMove(moves,
						PossibleMove{ m_pos.xCoord + dx_copy, m_pos.yCoord + dy_copy, MoveType::NORMAL },
						getOwnKing(field),
						field,
						checkCheck);
				}
			}
		}
	}

	m_possibleMoves = moves;
}