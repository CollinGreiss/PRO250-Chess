#include "King.h"
#include "Pawn.h"
#include <iostream>
#include <stdlib.h>

King::King(Team team, Point pos, SDL_Handler* handler, Team playerTeam)
	:Piece(team, pos, handler, KING), m_check(false)
{
	std::string filename;
	if (team == BLACK)
	{
		filename = "../res/Chess_kdt60.png";
	}
	else
	{
		filename = "../res/Chess_klt60.png";
	}
	m_handler = handler;
	m_texture = handler->loadImage(filename);

	this->playerTeam = playerTeam;
	render();
}

void King::sayMyName()
{
	if (m_team == BLACK)
	{
		std::cout << "BLACK KING" << std::endl;
	}
	else
	{
		std::cout << "WHTIE KING" << std::endl;
	}
}

void King::calcPossibleMoves(Piece* field[8][8], bool checkCheck)
{
	std::vector<PossibleMove> moves;
	bool castles = true;
	bool enemyPlace = false;

	for (int dx = -1; dx <= 1; dx++)
	{
		for (int dy = -1; dy <= 1; dy++)
		{
			if (m_pos.xCoord + dx >= 0 && m_pos.yCoord + dx <= 7 && m_pos.yCoord + dy >= 0 && m_pos.yCoord + dy <= 7)
			{
				if (field[m_pos.xCoord + dx][m_pos.yCoord + dy] != nullptr)
				{
					if (field[m_pos.xCoord + dx][m_pos.yCoord + dy]->getTeam() != m_team)
					{
						moves = pushMove(moves,
							PossibleMove{ m_pos.xCoord + dx, m_pos.yCoord + dy, MoveType::NORMAL },
							getOwnKing(field),
							field,
							checkCheck);
					}
				}
				else
				{
					moves = pushMove(moves,
						PossibleMove{ m_pos.xCoord + dx, m_pos.yCoord + dy, MoveType::NORMAL },
									 getOwnKing(field),
									 field,
									 checkCheck);
				}
			}
		}
	}

	if (!m_hasMoved) // Check for castle
	{
		for (int i = 0; i <= 7; i += 7)
		{
			for (int j = 0; j <= 7; j += 7)
			{
				castles = true;
				if (field[i][j] != nullptr)
				{
					if (field[i][j]->getTeam() == m_team && field[i][j]->getType() == ROOK && !field[i][j]->m_hasMoved)
					{
						int a, b, c;
						if (i == 0)
						{
							a = 1;
							b = 2;
							c = 3;
							if (playerTeam == Team::BLACK)
							{
								a = 1;
								b = 2;
								c = 2;
							}
						}
						else
						{
							a = 5;
							b = 6;
							c = 6;

							if (playerTeam == Team::BLACK)
							{
								a = 4;
								b = 5;
								c = 6;
							}
						}
						if (field[a][j] == nullptr && field[b][j] == nullptr && field[c][j] == nullptr)
						{
							for (int k = 0; k < 8; k++)
							{
								for (int l = 0; l < 8; l++)
								{
									if (field[k][l] != nullptr)
									{
										if (field[k][l]->getTeam() != m_team)
										{
											std::vector<PossibleMove> notPossible = field[k][l]->getPossibleMoves();
											for (const auto& value : notPossible)
											{
												if (i == 0)
												{
													if ((value.MovePos.xCoord == 4 && value.MovePos.yCoord == j)
														|| (value.MovePos.xCoord == 2 && value.MovePos.yCoord == j)
														|| (value.MovePos.xCoord == 3 && value.MovePos.yCoord == j))
													{
														castles = false;
													}
												}
												else
												{
													if ((value.MovePos.xCoord == 5 && value.MovePos.yCoord == j)
														|| (value.MovePos.xCoord == 6 && value.MovePos.yCoord == j)
														|| (value.MovePos.xCoord == 4 && value.MovePos.yCoord == j))
													{
														castles = false;
													}
												}
											}
										}
									}
								}
							}
							if (castles)
							{
								moves.push_back(PossibleMove{ i, j, MoveType::CASTLE });
							}
						}
					}
				}
			}
		}
	}
	m_possibleMoves = moves;
}

void King::setCheck(Piece* field[8][8], int x, int y)
{
	bool check = false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (field[i][j] != nullptr)
			{
				if (field[i][j]->getTeam() != m_team)
				{
					if (field[i][j]->getType() == KING)
					{
						if (abs(field[i][j]->getPos().xCoord - x) <= 1 && abs(field[i][j]->getPos().yCoord - y) <= 1)
						{
							check = true;
						}

					}
					else if (field[i][j]->getType() == PAWN)
					{
						int dy_pawn;
						if (field[i][j]->getTeam() == WHITE)
						{
							dy_pawn = 1;
						}
						else
						{
							dy_pawn = -1;
						}
						if ((x == field[i][j]->getPos().xCoord + 1 || x == field[i][j]->getPos().xCoord - 1) && y == field[i][j]->getPos().yCoord + dy_pawn)
						{
							check = true;
						}
					}
					else
					{
						field[i][j]->calcPossibleMoves(field, false);
						std::vector<PossibleMove> notPossible = field[i][j]->getPossibleMoves();
						for (const auto& value : notPossible)
						{
							if (value.MovePos.xCoord == x && value.MovePos.yCoord == y)
							{
								check = true;
							}
						}
					}
				}
			}
		}
	}
	
	m_check = check;
}
