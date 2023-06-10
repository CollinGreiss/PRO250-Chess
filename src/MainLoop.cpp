#include "MainLoop.h"
#include "SDL_Handler.h"
#include "Misc.h"
#include "Game.h"

#include <SDL.h>
#include <stdio.h>
#include <memory>

void MainLoop::Run(char playerSide)
{
	SDL_Handler handler;

	handler.renderBackground();

	std::unique_ptr<Game> game = std::make_unique<Game>(&handler, playerSide);
	bool quit = false;

	int xStart = -1;
	int yStart = -1;
	int xEnd = -1;
	int yEnd = -1;
	Piece* clickedOn = nullptr;

	while (!quit)
	{
		while (SDL_WaitEvent(&handler.m_event))
		{
			if (handler.m_event.type == SDL_QUIT)
			{
				quit = true;
				break;
			}

			if (handler.m_event.type == SDL_MOUSEBUTTONDOWN)
			{
				xStart = handler.m_event.button.x / handler.CELL_WIDTH;
				yStart = handler.m_event.button.y / handler.CELL_WIDTH;
				clickedOn = game->GetFieldPos(xStart, yStart);
				if (clickedOn != nullptr)
				{
					if (clickedOn->getTeam() == game->getTurn())
					{
						game->renderPossibleMoves(clickedOn);
					}
				}
			}
			else if (handler.m_event.type == SDL_MOUSEBUTTONUP)
			{
				if (clickedOn != nullptr)
				{
					if (clickedOn->getTeam() == game->getTurn())
					{
						game->UndoRenderPossibleMove(clickedOn);
					}
				}
				xEnd = handler.m_event.button.x / 80;
				yEnd = handler.m_event.button.y / 80;
				if (clickedOn != nullptr)
				{
					if ((xStart != -1 && yStart != -1 && xEnd != -1 && yEnd != -1)
						&& (clickedOn->getTeam() == game->getTurn())
						&& (game->isValidMove(xEnd, yEnd, clickedOn)))
					{
						std::vector<PossibleMove> list = game->GetFieldPos(xStart, yStart)->getPossibleMoves();
						for (const auto& value : list)
						{
							if (value.MovePos.xCoord == xEnd && value.MovePos.yCoord == yEnd)
							{
								game->move(clickedOn, PossibleMove{ {xEnd, yEnd}, value.Move_Type });
							}
						}
						xStart = -1;
						yStart = -1;
						yEnd = -1;
						game->calcAllMoves();
						clickedOn = nullptr;
					}
				}
			}
		}
	}
}