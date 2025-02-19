#include "Pawn.h"
#include <iostream>
#include <list>

Pawn::Pawn(Team team, Point pos, SDL_Handler* handler, Team playerTeam)
	:Piece(team, pos, handler, PAWN), m_enPassant(std::pair<bool, int>(false, 0))
{
	std::string filename;
	if (team == BLACK)
	{
		filename = "../res/Chess_pdt60.png";
	}
	else
	{
		filename = "../res/Chess_plt60.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);

	if (team == playerTeam)
	{
		moveDirection = -1;
	}
	else
	{
		moveDirection = 1;
	}

	render();
}

void Pawn::sayMyName()
{
	if (m_team == BLACK)
	{
		std::cout << "BLACK PAWN" << std::endl;
	}
	else
	{
		std::cout << "WHITE PAWN" << std::endl;
	}
}

void Pawn::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<PossibleMove> moves;

	if (m_pos.yCoord + moveDirection == 0 || m_pos.yCoord + moveDirection == 7)
	{
		if (field[m_pos.xCoord][m_pos.yCoord + moveDirection] == nullptr)
		{
			moves = pushMove(moves,
				PossibleMove{ m_pos.xCoord, m_pos.yCoord + moveDirection, MoveType::NEWPIECE },
				getOwnKing(field),
				field,
				checkCheck);
		}
	}
	else
	{
		if (field[m_pos.xCoord][m_pos.yCoord + moveDirection] == nullptr)
		{
			moves = pushMove(moves,
				PossibleMove{ m_pos.xCoord, m_pos.yCoord + moveDirection, MoveType::NORMAL },
				getOwnKing(field),
				field,
				checkCheck);
		}
	}

	if ((m_pos.yCoord + 2 * moveDirection >= 0) && (m_pos.yCoord + 2 * moveDirection <= 7))
	{
		if (field[m_pos.xCoord][m_pos.yCoord + 2 * moveDirection] == nullptr && !m_hasMoved)
		{
			moves = pushMove(moves,
				PossibleMove{ m_pos.xCoord, m_pos.yCoord + 2 * moveDirection, MoveType::NORMAL },
				getOwnKing(field),
				field,
				checkCheck);
		}
	}

	if (m_pos.xCoord + 1 <= 7)
	{
		if (field[m_pos.xCoord + 1][m_pos.yCoord + moveDirection] != nullptr)
		{
			if (field[m_pos.xCoord + 1][m_pos.yCoord + moveDirection]->getTeam() != m_team)
			{
				if (m_pos.yCoord + moveDirection == 0 || m_pos.yCoord + moveDirection == 7)
				{
					moves = pushMove(moves,
						PossibleMove{ m_pos.xCoord + 1, m_pos.yCoord + moveDirection, MoveType::NEWPIECE },
						getOwnKing(field),
						field,
						checkCheck);
				}
				else
				{
					moves = pushMove(moves,
						PossibleMove{ m_pos.xCoord + 1, m_pos.yCoord + moveDirection, MoveType::NORMAL },
						getOwnKing(field),
						field,
						checkCheck);
				}
			}
		}
	}
	if (m_pos.xCoord - 1 >= 0)
	{
		if (field[m_pos.xCoord - 1][m_pos.yCoord + moveDirection] != nullptr)
		{
			if (field[m_pos.xCoord - 1][m_pos.yCoord + moveDirection]->getTeam() != m_team)
			{
				if (m_pos.yCoord + moveDirection == 0 || m_pos.yCoord + moveDirection == 7)
				{
					moves = pushMove(moves,
						PossibleMove{ m_pos.xCoord - 1, m_pos.yCoord + moveDirection, MoveType::NEWPIECE },
						getOwnKing(field),
						field,
						checkCheck);
				}
				else
				{
					moves = pushMove(moves,
						PossibleMove{ m_pos.xCoord - 1, m_pos.yCoord + moveDirection, MoveType::NORMAL },
						getOwnKing(field),
						field,
						checkCheck);
				}
			}
		}
	}

	if (m_enPassant == std::pair<bool, int>(true, -1))
	{
		moves = pushMove(moves,
			PossibleMove{ m_pos.xCoord + 1, m_pos.yCoord + moveDirection, MoveType::ENPASSANT },
			getOwnKing(field),
			field,
			checkCheck);
	}
	if (m_enPassant == std::pair<bool, int>(true, 1))
	{
		moves = pushMove(moves,
			PossibleMove{ m_pos.xCoord - 1, m_pos.yCoord + moveDirection, MoveType::ENPASSANT },
			getOwnKing(field),
			field,
			checkCheck);
	}
	m_possibleMoves = moves;
}






