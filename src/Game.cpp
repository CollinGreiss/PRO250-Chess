#include "Game.h"
#include "Pieces/Piece.h"
#include <iostream>
#include <vector>

Game::Game(SDL_Handler* handler, Piece::Team playerTeam, Variant variant) {

	playerSide = playerTeam;

	int blackPieceYPos = 0;
	int blackPawnYPos = 1;

	int whitePieceYPos = 7;
	int whitePawnYPos = 6;

	if (playerSide == Piece::Team::BLACK) // Check, what pieces color should be first depending on player choice
	{
		whitePieceYPos = 0;
		whitePawnYPos = 1;

		blackPieceYPos = 7;
		blackPawnYPos = 6;
	}

	m_turn = Piece::WHITE;
	m_handler = handler;
	m_checkEnPassant = true;

	switch (variant) {

	case NORMAL:
		SetupPiecesNormal();
		break;

	case CHESS960:
		SetupPieces960();
		break;

	default:
		SetupPiecesNormal();
		break;

	}

	m_pieces = {
	pl1, pl2, pl3, pl4, pl5, pl6, pl7, pl8,
	pb1, pb2, pb3, pb4, pb5, pb6, pb7, pb8,
	rb1, rb2, rl1, rl2,
	nb1, nb2, nl1, nl2,
	bb1, bb2, bl1, bl2,
	kb1, kl1,
	qb1, ql1
	};


	m_field[rb1->getPos().xCoord][rb1->getPos().yCoord] = rb1;
	m_field[rb2->getPos().xCoord][rb2->getPos().yCoord] = rb2;
	m_field[rl1->getPos().xCoord][rl1->getPos().yCoord] = rl1;
	m_field[rl2->getPos().xCoord][rl2->getPos().yCoord] = rl2;

	m_field[nb1->getPos().xCoord][nb1->getPos().yCoord] = nb1;
	m_field[nb2->getPos().xCoord][nb2->getPos().yCoord] = nb2;
	m_field[nl1->getPos().xCoord][nl1->getPos().yCoord] = nl1;
	m_field[nl2->getPos().xCoord][nl2->getPos().yCoord] = nl2;

	m_field[bb1->getPos().xCoord][bb1->getPos().yCoord] = bb1;
	m_field[bb2->getPos().xCoord][bb2->getPos().yCoord] = bb2;
	m_field[bl1->getPos().xCoord][bl1->getPos().yCoord] = bl1;
	m_field[bl2->getPos().xCoord][bl2->getPos().yCoord] = bl2;

	m_field[kb1->getPos().xCoord][kb1->getPos().yCoord] = kb1;
	m_field[kl1->getPos().xCoord][kl1->getPos().yCoord] = kl1;

	m_field[qb1->getPos().xCoord][qb1->getPos().yCoord] = qb1;
	m_field[ql1->getPos().xCoord][ql1->getPos().yCoord] = ql1;
	//In for cycle
	m_field[pl1->getPos().xCoord][pl1->getPos().yCoord] = pl1;
	m_field[pl2->getPos().xCoord][pl2->getPos().yCoord] = pl2;
	m_field[pl3->getPos().xCoord][pl3->getPos().yCoord] = pl3;
	m_field[pl4->getPos().xCoord][pl4->getPos().yCoord] = pl4;
	m_field[pl5->getPos().xCoord][pl5->getPos().yCoord] = pl5;
	m_field[pl6->getPos().xCoord][pl6->getPos().yCoord] = pl6;
	m_field[pl7->getPos().xCoord][pl7->getPos().yCoord] = pl7;
	m_field[pl8->getPos().xCoord][pl8->getPos().yCoord] = pl8;

	m_field[pb1->getPos().xCoord][pb1->getPos().yCoord] = pb1;
	m_field[pb2->getPos().xCoord][pb2->getPos().yCoord] = pb2;
	m_field[pb3->getPos().xCoord][pb3->getPos().yCoord] = pb3;
	m_field[pb4->getPos().xCoord][pb4->getPos().yCoord] = pb4;
	m_field[pb5->getPos().xCoord][pb5->getPos().yCoord] = pb5;
	m_field[pb6->getPos().xCoord][pb6->getPos().yCoord] = pb6;
	m_field[pb7->getPos().xCoord][pb7->getPos().yCoord] = pb7;
	m_field[pb8->getPos().xCoord][pb8->getPos().yCoord] = pb8;

	for (int i = 2; i < 6; i++) {
		for (int j = 0; j < 8; j++) {
			m_field[j][i] = nullptr;
		}
	}

	calcAllMoves();
}

Game::~Game() {}

void Game::SetupPiecesNormal() {

	int blackPieceYPos = 0;
	int blackPawnYPos = 1;

	int whitePieceYPos = 7;
	int whitePawnYPos = 6;

	if (playerSide == Piece::Team::BLACK) {

		whitePieceYPos = 0;
		whitePawnYPos = 1;

		blackPieceYPos = 7;
		blackPawnYPos = 6;

	}

	pl1 = new Pawn(Piece::WHITE, Point{ 0, whitePawnYPos }, m_handler, playerSide);
	pl2 = new Pawn(Piece::WHITE, Point{ 1, whitePawnYPos }, m_handler, playerSide);
	pl3 = new Pawn(Piece::WHITE, Point{ 2, whitePawnYPos }, m_handler, playerSide);
	pl4 = new Pawn(Piece::WHITE, Point{ 3, whitePawnYPos }, m_handler, playerSide);
	pl5 = new Pawn(Piece::WHITE, Point{ 4, whitePawnYPos }, m_handler, playerSide);
	pl6 = new Pawn(Piece::WHITE, Point{ 5, whitePawnYPos }, m_handler, playerSide);
	pl7 = new Pawn(Piece::WHITE, Point{ 6, whitePawnYPos }, m_handler, playerSide);
	pl8 = new Pawn(Piece::WHITE, Point{ 7, whitePawnYPos }, m_handler, playerSide);
	pb1 = new Pawn(Piece::BLACK, Point{ 0, blackPawnYPos }, m_handler, playerSide);
	pb2 = new Pawn(Piece::BLACK, Point{ 1, blackPawnYPos }, m_handler, playerSide);
	pb3 = new Pawn(Piece::BLACK, Point{ 2, blackPawnYPos }, m_handler, playerSide);
	pb4 = new Pawn(Piece::BLACK, Point{ 3, blackPawnYPos }, m_handler, playerSide);
	pb5 = new Pawn(Piece::BLACK, Point{ 4, blackPawnYPos }, m_handler, playerSide);
	pb6 = new Pawn(Piece::BLACK, Point{ 5, blackPawnYPos }, m_handler, playerSide);
	pb7 = new Pawn(Piece::BLACK, Point{ 6, blackPawnYPos }, m_handler, playerSide);
	pb8 = new Pawn(Piece::BLACK, Point{ 7, blackPawnYPos }, m_handler, playerSide);
	rb1 = new Rook(Piece::BLACK, Point{ 0, blackPieceYPos }, m_handler);
	rb2 = new Rook(Piece::BLACK, Point{ 7, blackPieceYPos }, m_handler);
	rl1 = new Rook(Piece::WHITE, Point{ 0, whitePieceYPos }, m_handler);
	rl2 = new Rook(Piece::WHITE, Point{ 7, whitePieceYPos }, m_handler);
	nb1 = new Knight(Piece::BLACK, Point{ 1, blackPieceYPos }, m_handler);
	nb2 = new Knight(Piece::BLACK, Point{ 6, blackPieceYPos }, m_handler);
	nl1 = new Knight(Piece::WHITE, Point{ 1, whitePieceYPos }, m_handler);
	nl2 = new Knight(Piece::WHITE, Point{ 6, whitePieceYPos }, m_handler);
	bb1 = new Bishop(Piece::BLACK, Point{ 2, blackPieceYPos }, m_handler);
	bb2 = new Bishop(Piece::BLACK, Point{ 5, blackPieceYPos }, m_handler);
	bl1 = new Bishop(Piece::WHITE, Point{ 2, whitePieceYPos }, m_handler);
	bl2 = new Bishop(Piece::WHITE, Point{ 5, whitePieceYPos }, m_handler);

	if (playerSide == Piece::Team::BLACK) {
		kb1 = new King(Piece::BLACK, Point{ 3, blackPieceYPos }, m_handler, playerSide);
		kl1 = new King(Piece::WHITE, Point{ 3, whitePieceYPos }, m_handler, playerSide);
		qb1 = new Queen(Piece::BLACK, Point{ 4, blackPieceYPos }, m_handler);
		ql1 = new Queen(Piece::WHITE, Point{ 4, whitePieceYPos }, m_handler);
	} else {
		kb1 = new King(Piece::BLACK, Point{ 4, blackPieceYPos }, m_handler, playerSide);
		kl1 = new King(Piece::WHITE, Point{ 4, whitePieceYPos }, m_handler, playerSide);
		qb1 = new Queen(Piece::BLACK, Point{ 3, blackPieceYPos }, m_handler);
		ql1 = new Queen(Piece::WHITE, Point{ 3, whitePieceYPos }, m_handler);
	}

}

void Game::SetupPieces960() {

	int blackPieceYPos = 0;
	int blackPawnYPos = 1;

	int whitePieceYPos = 7;
	int whitePawnYPos = 6;

	if (playerSide == Piece::Team::BLACK) {

		whitePieceYPos = 0;
		whitePawnYPos = 1;

		blackPieceYPos = 7;
		blackPawnYPos = 6;

	}

	pl1 = new Pawn(Piece::WHITE, Point{ 0, whitePawnYPos }, m_handler, playerSide);
	pl2 = new Pawn(Piece::WHITE, Point{ 1, whitePawnYPos }, m_handler, playerSide);
	pl3 = new Pawn(Piece::WHITE, Point{ 2, whitePawnYPos }, m_handler, playerSide);
	pl4 = new Pawn(Piece::WHITE, Point{ 3, whitePawnYPos }, m_handler, playerSide);
	pl5 = new Pawn(Piece::WHITE, Point{ 4, whitePawnYPos }, m_handler, playerSide);
	pl6 = new Pawn(Piece::WHITE, Point{ 5, whitePawnYPos }, m_handler, playerSide);
	pl7 = new Pawn(Piece::WHITE, Point{ 6, whitePawnYPos }, m_handler, playerSide);
	pl8 = new Pawn(Piece::WHITE, Point{ 7, whitePawnYPos }, m_handler, playerSide);
	pb1 = new Pawn(Piece::BLACK, Point{ 0, blackPawnYPos }, m_handler, playerSide);
	pb2 = new Pawn(Piece::BLACK, Point{ 1, blackPawnYPos }, m_handler, playerSide);
	pb3 = new Pawn(Piece::BLACK, Point{ 2, blackPawnYPos }, m_handler, playerSide);
	pb4 = new Pawn(Piece::BLACK, Point{ 3, blackPawnYPos }, m_handler, playerSide);
	pb5 = new Pawn(Piece::BLACK, Point{ 4, blackPawnYPos }, m_handler, playerSide);
	pb6 = new Pawn(Piece::BLACK, Point{ 5, blackPawnYPos }, m_handler, playerSide);
	pb7 = new Pawn(Piece::BLACK, Point{ 6, blackPawnYPos }, m_handler, playerSide);
	pb8 = new Pawn(Piece::BLACK, Point{ 7, blackPawnYPos }, m_handler, playerSide);

	std::srand(std::time(0));

	std::vector<int> spots{ 0, 1, 2, 3, 4, 5, 6, 7 };

	int kSpot = spots[1 + rand() % 6];

	int r1Spot = (kSpot == 1) ? 0 : spots[1 + rand() % (kSpot - 1)];
	int r2Spot = (kSpot == 6) ? 7 : spots[kSpot + 1 + rand() % (7 - kSpot)];

	spots.erase(std::find(spots.begin(), spots.end(), kSpot));
	spots.erase(std::find(spots.begin(), spots.end(), r1Spot));
	spots.erase(std::find(spots.begin(), spots.end(), r2Spot));

	int b1Spot = spots[rand() % 5];
	spots.erase(std::find(spots.begin(), spots.end(), b1Spot));

	int b2Spot = spots[rand() % 4];
	while (b2Spot % 2 == b1Spot % 2) b2Spot = spots[rand() % 4];
	spots.erase(std::find(spots.begin(), spots.end(), b2Spot));

	int qSpot = spots[rand() % 3];
	spots.erase(std::find(spots.begin(), spots.end(), qSpot));

	int n1Spot = spots[rand() % 2];
	spots.erase(std::find(spots.begin(), spots.end(), n1Spot));

	int n2Spot = spots[0];

	kb1 = new King(Piece::BLACK, Point{ kSpot, blackPieceYPos }, m_handler, playerSide);
	qb1 = new Queen(Piece::BLACK, Point{ qSpot, blackPieceYPos }, m_handler);

	rb1 = new Rook(Piece::BLACK, Point{ r1Spot, blackPieceYPos }, m_handler);
	rb2 = new Rook(Piece::BLACK, Point{ r2Spot, blackPieceYPos }, m_handler);
	nb1 = new Knight(Piece::BLACK, Point{ n1Spot, blackPieceYPos }, m_handler);
	nb2 = new Knight(Piece::BLACK, Point{ n2Spot, blackPieceYPos }, m_handler);
	bb1 = new Bishop(Piece::BLACK, Point{ b1Spot, blackPieceYPos }, m_handler);
	bb2 = new Bishop(Piece::BLACK, Point{ b2Spot, blackPieceYPos }, m_handler);


	kl1 = new King(Piece::WHITE, Point{ kSpot, whitePieceYPos }, m_handler, playerSide);
	ql1 = new Queen(Piece::WHITE, Point{ qSpot, whitePieceYPos }, m_handler);

	rl1 = new Rook(Piece::WHITE, Point{ r1Spot, whitePieceYPos }, m_handler);
	rl2 = new Rook(Piece::WHITE, Point{ r2Spot, whitePieceYPos }, m_handler);
	nl1 = new Knight(Piece::WHITE, Point{ n1Spot, whitePieceYPos }, m_handler);
	nl2 = new Knight(Piece::WHITE, Point{ n2Spot, whitePieceYPos }, m_handler);
	bl1 = new Bishop(Piece::WHITE, Point{ b1Spot, whitePieceYPos }, m_handler);
	bl2 = new Bishop(Piece::WHITE, Point{ b2Spot, whitePieceYPos }, m_handler);


}

Piece* Game::GetFieldPos(int row, int col) {
	return m_field[row][col];
}


std::pair<std::string, MoveType> Game::move(Piece* start, PossibleMove move) {
	if (m_checkEnPassant) {
		DisableEnPassant();
	} else {
		m_checkEnPassant = true;
	}

	std::pair<std::string, MoveType>MoveForAI;
	//std::string MoveString;

	//std::cout << "In game move function: Start.x = " << start->getPos().xCoord << " Start.y = " << start->getPos().yCoord <<
	//	" move.x = " << move.MovePos.xCoord << "Move.y = " << move.MovePos.yCoord << std::endl;

	MoveForAI.first = MoveToAIMove(start, move);
	MoveForAI.second = move.Move_Type;

	//For AI Castle we return move Start, End, KingPos.X, RookPos.x;
	//For ENPASSANT we return move start, end, Piece position to eat
	//For exchange we retrun move start, end, new piece of an Pawn
	switch (move.Move_Type) {
	case MoveType::NORMAL:
		normal(start->getPos().xCoord, start->getPos().yCoord, move.MovePos.xCoord, move.MovePos.yCoord);
		break;
	case MoveType::CASTLE:
		MoveForAI.first += Castles(start->getPos().xCoord, start->getPos().yCoord, move.MovePos.xCoord, move.MovePos.yCoord);
		break;
	case MoveType::ENPASSANT:
		MoveForAI.first += EnPassant(start->getPos().xCoord, start->getPos().yCoord, move.MovePos.xCoord, move.MovePos.yCoord);
		break;
	case MoveType::NEWPIECE:
		MoveForAI.first += Exchange(start->getPos().xCoord, start->getPos().yCoord, move.MovePos.xCoord, move.MovePos.yCoord);
		break;
	default:
		break;
	}

	GameState();
	//std::cout << "Move = " << MoveForAI.first << std::endl;
	return MoveForAI;
}

void Game::InsertAIMove(std::string AIMove) {
	std::vector<int> NormalMove = AIMoveToMove(AIMove);
	clickedOn = GetFieldPos(NormalMove[0], NormalMove[1]);

	if (clickedOn == NULL || clickedOn->getTeam() == playerSide) {
		clickedOn = GetFieldPos(NormalMove[2], NormalMove[3]);
		move(clickedOn, PossibleMove{ {NormalMove[0], NormalMove[1]}, MoveType::NORMAL });
	} else
		move(clickedOn, PossibleMove{ {NormalMove[2], NormalMove[3]}, MoveType::NORMAL });
}


std::string Game::MoveToAIMove(Piece* start, PossibleMove move) {
	//std::cout << "Start.x = " << start->getPos().xCoord << "Start.y = " << start->getPos().yCoord <<
	//	"  move.x = " << move.MovePos.xCoord << " move.y = " << move.MovePos.yCoord << std::endl;
	std::string MoveString;

	char StartXLetter = ConvertAIXCord(start->getPos().xCoord);
	int StartYPos = ConvertAIYCord(start->getPos().yCoord);

	char EndXLetter = ConvertAIXCord(move.MovePos.xCoord);
	int EndYPos = ConvertAIYCord(move.MovePos.yCoord);

	MoveString = StartXLetter + std::to_string(StartYPos) + EndXLetter + std::to_string(EndYPos);

	return MoveString;
}

char Game::ConvertAIXCord(int xCoord) {
	char AI_XPos = playerSide == Piece::Team::WHITE ? boardXLetters[xCoord] : boardXLetters[7 - xCoord];
	return AI_XPos;
}

int Game::ConvertAIYCord(int yCoord) {
	int AIYPos = playerSide == Piece::Team::WHITE ? (8 - yCoord) : (yCoord + 1);
	return AIYPos;
}


std::vector<int> Game::AIMoveToMove(std::string AIMove) {
	//Check this function
	std::vector<int>NormalMove;
	int xStart = (AIMove[0] - '0');
	int yStart = (AIMove[1] - '0');
	int xEnd = (AIMove[2] - '0');
	int yEnd = (AIMove[3] - '0');
	NormalMove.resize(4);

	NormalMove[0] = playerSide == Piece::Team::WHITE ? xStart : (7 - xStart);
	NormalMove[1] = playerSide == Piece::Team::WHITE ? (8 - yStart) : (yStart - 1);
	NormalMove[2] = playerSide == Piece::Team::WHITE ? xEnd : (7 - xEnd);
	NormalMove[3] = playerSide == Piece::Team::WHITE ? (8 - yEnd) : (yEnd - 1);

	/*NormalMove[0] = xStart;
	NormalMove[1] = (8 - yStart);
	NormalMove[2] = xEnd ;
	NormalMove[3] = (8 - yEnd);*/

	return NormalMove;
}

void Game::normal(int xStart, int yStart, int xEnd, int yEnd) {
	m_field[xEnd][yEnd] = GetFieldPos(xStart, yStart);
	m_field[xEnd][yEnd]->m_hasMoved = true;
	m_field[xStart][yStart] = nullptr;
	m_handler->undoPieceRender(xStart, yStart);
	//  m_field[xEnd][yEnd]->setPosition(std::pair<int, int>(xEnd, yEnd));
	m_field[xEnd][yEnd]->setPosition(Point{ xEnd,yEnd });
	if (m_field[xEnd][yEnd] != nullptr) {
		m_handler->undoPieceRender(xEnd, yEnd);
	}
	m_field[xEnd][yEnd]->render();

	if (m_field[xEnd][yEnd]->getType() == Piece::PAWN) {
		if (abs(yEnd - yStart) == 2) {
			if (xEnd - 1 >= 0) {
				if (m_field[xEnd - 1][yEnd] != nullptr) {
					if (m_field[xEnd - 1][yEnd]->getType() == Piece::PAWN) {
						Pawn* pwn = static_cast<Pawn*>(m_field[xEnd - 1][yEnd]);
						pwn->setEnPassant(std::pair<bool, int>(true, -1));
						m_checkEnPassant = false;
					}
				}
			}

			if (xEnd + 1 <= 7) {
				if (m_field[xEnd + 1][yEnd] != nullptr) {
					if (m_field[xEnd + 1][yEnd]->getType() == Piece::PAWN) {
						Pawn* pwn = static_cast<Pawn*>(m_field[xEnd + 1][yEnd]);
						pwn->setEnPassant(std::pair<bool, int>(true, 1));
						m_checkEnPassant = false;
					}
				}
			}
		}
	}
}


std::string Game::EnPassant(int xStart, int yStart, int xEnd, int yEnd) {
	std::string AIMoveToAdd;

	Pawn* pawn_start = static_cast<Pawn*>(m_field[xStart][yStart]);

	AIMoveToAdd += std::to_string(ConvertAIYCord(yEnd - pawn_start->moveDirection));

	m_field[xEnd][yEnd - pawn_start->moveDirection] = nullptr;
	m_field[xEnd][yEnd] = GetFieldPos(xStart, yStart);
	m_field[xEnd][yEnd]->m_hasMoved = true;
	m_field[xStart][yStart] = nullptr;

	m_handler->undoPieceRender(xStart, yStart);
	m_handler->undoPieceRender(xEnd, yEnd - pawn_start->moveDirection);
	m_field[xEnd][yEnd]->setPosition(Point{ xEnd, yEnd });
	m_field[xEnd][yEnd]->render();

	return AIMoveToAdd;
}


std::string Game::Exchange(int xStart, int yStart, int xEnd, int yEnd) {
	std::string NewFigure;

	SDL_Texture* text_rook = m_handler->loadImage("../res/Chess_rlt60.png");
	SDL_Texture* text_knight = m_handler->loadImage("../res/Chess_nlt60.png");
	SDL_Texture* text_bishop = m_handler->loadImage("../res/Chess_blt60.png");
	SDL_Texture* text_queen = m_handler->loadImage("../res/Chess_qlt60.png");
	int y_draw = 0;
	Piece::Team team = Piece::WHITE;

	if (m_field[xStart][yStart]->getTeam() == Piece::BLACK) {
		text_rook = m_handler->loadImage("../res/Chess_rdt60.png");
		text_knight = m_handler->loadImage("../res/Chess_ndt60.png");
		text_bishop = m_handler->loadImage("../res/Chess_bdt60.png");
		text_queen = m_handler->loadImage("../res/Chess_qdt60.png");
		y_draw = 3 * m_handler->SCREEN_HEIGHT / 4;
		team = Piece::BLACK;
	}

	SDL_SetRenderDrawColor(m_handler->m_renderer, 155, 103, 60, 255);
	SDL_Rect rectangle = { 0,
						  y_draw,
						  m_handler->SCREEN_WIDTH / 4,
						  m_handler->SCREEN_HEIGHT / 4 };
	SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
	SDL_Rect src = { 0, 0, 60, 60 };
	m_handler->DrawRectangle(src, rectangle, text_rook);

	SDL_SetRenderDrawColor(m_handler->m_renderer, 255, 255, 255, 255);
	rectangle.x = m_handler->SCREEN_WIDTH / 4;
	SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
	m_handler->DrawRectangle(src, rectangle, text_knight);

	SDL_SetRenderDrawColor(m_handler->m_renderer, 155, 103, 60, 255);
	rectangle.x = 2 * m_handler->SCREEN_WIDTH / 4;
	SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
	m_handler->DrawRectangle(src, rectangle, text_bishop);

	SDL_SetRenderDrawColor(m_handler->m_renderer, 255, 255, 255, 255);
	rectangle.x = 3 * m_handler->SCREEN_WIDTH / 4;
	SDL_RenderFillRect(m_handler->m_renderer, &rectangle);
	m_handler->DrawRectangle(src, rectangle, text_queen);

	bool quit = false;
	int x = -1;
	int y = -1;

	Piece* clickedOn = nullptr;

	std::cout << m_handler;

	while (quit == false) {
		while (SDL_PollEvent(&m_handler->m_event)) {
			if (m_handler->m_event.type == SDL_QUIT) {
				quit = true;
			}

			if (m_handler->m_event.type == SDL_MOUSEBUTTONDOWN) {
				x = m_handler->m_event.button.x / 160;
				y = m_handler->m_event.button.y / 160;

				if (y >= y_draw / 160 && y < y_draw / 160 + 1) {
					if (x < m_handler->SCREEN_WIDTH / 640) {
						clickedOn = new Rook(team, Point{ xEnd, yEnd }, m_handler);
						NewFigure = m_turn == Piece::Team::WHITE ? "R" : "r";
					} else if (x < 2 * m_handler->SCREEN_WIDTH / 640) {
						clickedOn = new Knight(team, Point{ xEnd, yEnd }, m_handler);
						NewFigure = m_turn == Piece::Team::WHITE ? "N" : "n";
					} else if (x < 3 * m_handler->SCREEN_WIDTH / 640) {
						clickedOn = new Bishop(team, Point{ xEnd, yEnd }, m_handler);
						NewFigure = m_turn == Piece::Team::WHITE ? "B" : "b";
					} else if (x <= 4 * m_handler->SCREEN_WIDTH / 640) {
						clickedOn = new Queen(team, Point{ xEnd, yEnd }, m_handler);
						NewFigure = m_turn == Piece::Team::WHITE ? "Q" : "q";
					}
					std::cout << x << " " << m_handler->SCREEN_WIDTH / 640 << std::endl;
				}
			}

			if (m_handler->m_event.type == SDL_MOUSEBUTTONUP && clickedOn != nullptr) {
				quit = true;
			}
		}
	}

	m_field[xEnd][yEnd] = clickedOn;
	m_field[xStart][yStart] = nullptr;
	m_handler->undoPieceRender(xStart, yStart);
	m_handler->renderBackground();

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (m_field[i][j] != nullptr) {
				m_field[i][j]->render();
			}
		}
	}

	SDL_DestroyTexture(text_rook);
	SDL_DestroyTexture(text_bishop);
	SDL_DestroyTexture(text_knight);
	SDL_DestroyTexture(text_queen);

	return NewFigure;
}


std::string Game::Castles(int xStart, int yStart, int xEnd, int yEnd) //Start - king position, end - rook position
{
	std::string castleStringForAI;
	int newRookPosX;
	int newKingPosX;
	if (xEnd == 0) //Long castling for white, and short for black side
	{
		if (playerSide == Piece::Team::WHITE) {
			newKingPosX = 2;
			newRookPosX = 3;
		} else {
			newKingPosX = 1;
			newRookPosX = 2;
		}
	} else {
		if (playerSide == Piece::Team::WHITE) {
			newKingPosX = 6;
			newRookPosX = 5;
		} else {
			newKingPosX = 5;
			newRookPosX = 4;
		}
	}

	castleStringForAI += ConvertAIXCord(newKingPosX);
	castleStringForAI += ConvertAIXCord(newRookPosX);

	m_field[newKingPosX][yEnd] = m_field[xStart][yEnd];
	m_field[newRookPosX][yEnd] = m_field[xEnd][yEnd];

	m_field[newKingPosX][yEnd]->m_hasMoved = true;
	m_field[newRookPosX][yEnd]->m_hasMoved = true;

	m_field[newKingPosX][yEnd]->setPosition(Point{ newKingPosX, yEnd });
	m_field[newRookPosX][yEnd]->setPosition(Point{ newRookPosX, yEnd });

	m_field[xStart][yEnd] = nullptr;
	m_field[xEnd][yEnd] = nullptr;

	m_handler->undoPieceRender(xStart, yEnd);
	m_handler->undoPieceRender(xEnd, yEnd);

	m_field[newKingPosX][yEnd]->render();
	m_field[newRookPosX][yEnd]->render();

	return castleStringForAI;
}

void Game::GameState() {
	bool lost = true;
	King* pivot = kb1;

	if (m_turn == Piece::BLACK) {
		pivot = kl1;
	}

	pivot->setCheck(m_field, kl1->getPos().xCoord, kl1->getPos().yCoord);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (m_field[i][j] != nullptr) {
				if (m_field[i][j]->getTeam() != m_turn) {
					m_field[i][j]->calcPossibleMoves(m_field, true);
					if (!m_field[i][j]->getPossibleMoves().empty()) {
						lost = false;
					}
				}
			}
		}
	}

	if (pivot->getCheck() && lost) {
		if (m_turn == Piece::BLACK) {
			std::cout << "Black wins!";
		} else {
			std::cout << "White wins!";
		}
	} else if (lost) {
		if (m_turn == Piece::BLACK) {
			std::cout << "Remis!";
		} else {
			std::cout << "Remis!";
		}
	}
	if (m_turn == Piece::BLACK) {
		m_turn = Piece::WHITE;
	} else {
		m_turn = Piece::BLACK;
	}

}


void Game::DisableEnPassant() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (m_field[i][j] != nullptr) {
				if (m_field[i][j]->getType() == Piece::PAWN) {
					Pawn* pwn = static_cast<Pawn*>(m_field[i][j]);
					pwn->setEnPassant(std::pair<bool, int>(false, 0));
				}
			}
		}
	}
}


void Game::renderPossibleMoves(Piece* piece) {
	piece->calcPossibleMoves(m_field, true);
	std::vector<PossibleMove> possible = piece->getPossibleMoves();
	SDL_Rect rectangle;
	for (const auto& value : possible) {
		if ((value.MovePos.xCoord % 2 == 0 && value.MovePos.yCoord % 2 == 1) || (value.MovePos.xCoord % 2 == 1 && value.MovePos.yCoord % 2 == 0)) {
			SDL_SetRenderDrawColor(m_handler->m_renderer, 0, 134, 139, 255);
		} else {
			SDL_SetRenderDrawColor(m_handler->m_renderer, 164, 211, 238, 255);
		}
		rectangle = { value.MovePos.xCoord * m_handler->SCREEN_WIDTH / 8,
					 value.MovePos.yCoord * m_handler->SCREEN_HEIGHT / 8,
					  m_handler->SCREEN_WIDTH / 8,
					  m_handler->SCREEN_HEIGHT / 8 };
		SDL_RenderFillRect(m_handler->m_renderer, &rectangle);

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (m_field[i][j] != nullptr) {
					m_field[i][j]->render();
				}
			}
		}
	}
}

void Game::UndoRenderPossibleMove(Piece* piece) {
	std::vector<PossibleMove> possible = piece->getPossibleMoves();
	for (const auto& value : possible) {
		if ((value.MovePos.xCoord % 2 == 0 && value.MovePos.yCoord % 2 == 1) || (value.MovePos.xCoord % 2 == 1 && value.MovePos.yCoord % 2 == 0)) {
			SDL_SetRenderDrawColor(m_handler->m_renderer, 155, 103, 60, 255);
		} else {
			SDL_SetRenderDrawColor(m_handler->m_renderer, 255, 255, 255, 255);
		}
		SDL_Rect rectangle = { value.MovePos.xCoord * m_handler->SCREEN_WIDTH / 8,
								  value.MovePos.yCoord * m_handler->SCREEN_HEIGHT / 8,
								  m_handler->SCREEN_WIDTH / 8,
								  m_handler->SCREEN_HEIGHT / 8 };
		SDL_RenderFillRect(m_handler->m_renderer, &rectangle);

		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (m_field[i][j] != nullptr) {
					m_field[i][j]->render();
				}
			}
		}
	}
}

void Game::calcAllMoves() {
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (m_field[i][j] != nullptr) {
				m_field[i][j]->calcPossibleMoves(m_field, true);
			}
		}
	}
}


bool Game::isValidMove(int x, int y, Piece* piece) {
	std::vector<PossibleMove> list = piece->getPossibleMoves();
	for (const auto& value : list) {
		if (value.MovePos.xCoord == x && value.MovePos.yCoord == y) {
			return true;
		}
	}
	return false;
}
