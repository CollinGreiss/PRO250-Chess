#include "Piece.h"
#include "King.h"
#include "Misc.h"

#include <string>
#include <iostream>

std::vector<PossibleMove>Piece::pushMove(std::vector<PossibleMove> moveList,
	PossibleMove move,
	King* king,
	Piece* field[8][8],
	bool checkCheck)
{
	if (!checkCheck)
	{
		moveList.push_back(move);
	}
	else
	{
		bool enemyPlace = true;
		king->setCheck(field, king->getPos().xCoord, king->getPos().yCoord);
		Piece* zwisch = &(*field[move.MovePos.xCoord][move.MovePos.yCoord]);
		enemyPlace = false;

		if (field[move.MovePos.xCoord][move.MovePos.yCoord] != nullptr)
		{
			enemyPlace = true;
			field[move.MovePos.xCoord][move.MovePos.yCoord] = nullptr;
		}

		std::swap(field[move.MovePos.xCoord][move.MovePos.yCoord], field[m_pos.xCoord][m_pos.yCoord]);
		if (m_type == KING)
		{
			king->setCheck(field, move.MovePos.xCoord, move.MovePos.yCoord);
		}
		else
		{
			king->setCheck(field, king->getPos().xCoord, king->getPos().yCoord);
		}
		std::swap(field[move.MovePos.xCoord][move.MovePos.yCoord], field[m_pos.xCoord][m_pos.yCoord]);

		if (enemyPlace)
		{
			field[move.MovePos.xCoord][move.MovePos.yCoord] = &(*zwisch);
		}
		if (!king->getCheck())
		{
			moveList.push_back(move);
		}
		king->setCheck(field, king->getPos().xCoord, king->getPos().yCoord);
	}
	return moveList;
}


King* Piece::getOwnKing(Piece* field[8][8])
{
	for  (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (field[i][j] != nullptr)
			{
				if (field[i][j]->getTeam() == m_team && field[i][j]->getType() == Piece::KING)
				{
					King* ret = static_cast<King*>(field[i][j]);
					return ret;
				}
			}
		}
	}
	return nullptr;
}

Piece::Piece(Team team, Point pos, SDL_Handler* handler, PieceType type)
	:m_team(team), m_pos(pos), m_handler(handler), m_texture(NULL), m_hasMoved(false), m_type(type)
{
}

Piece::Piece(const Piece& piece)
	:m_team(piece.m_team), m_pos(piece.m_pos), m_handler(piece.m_handler), m_texture(NULL), m_hasMoved(false), m_type(piece.m_type)
{
}

Piece::~Piece()
{
	SDL_DestroyTexture(m_texture);

	m_handler->undoPieceRender(m_pos.xCoord, m_pos.yCoord);
}


void Piece::render()
{
	SDL_Rect src = {0, 0, m_handler->CELL_WIDTH, m_handler->CELL_WIDTH };
	if (m_handler == nullptr)
	{
		sayMyName();
	}
	SDL_Rect dest = { m_handler->SCREEN_WIDTH / 8 * m_pos.xCoord - 2,
					  m_handler->SCREEN_HEIGHT / 8 * m_pos.yCoord,
					  m_handler->SCREEN_WIDTH / 8,
					  m_handler->SCREEN_HEIGHT / 8 };
	m_handler->DrawRectangle(src, dest, m_texture);
}

void Piece::sayMyName()
{
	std::cout << "No Piece here" << std::endl;
}
