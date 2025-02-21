#include <string>
#include <vector>
#include <map>
#include "mainAI.h"

#define KingWt 1300
#define QueenWt 900
#define RookWt 500
#define BishopWt 330
#define KnightWt 320
#define PawnWt 100

using namespace std;

// White's Piece-Square Tables
const int wKingTableMid[8][8] = {
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -10,-20,-20,-20,-20,-20,-20,-10,
     20, 20,  0,  0,  0,  0, 20, 20,
     20, 30, 10,  0,  0, 10, 30, 20
};
const int wQueenTable[8][8] = {
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
     -5,  0,  5,  5,  5,  5,  0, -5,
      0,  0,  5,  5,  5,  5,  0, -5,
    -10,  5,  5,  5,  5,  5,  0,-10,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
};
const int wRookTable[8][8] = {
      0,  0,  0,  0,  0,  0,  0,  0,
      5, 10, 10, 10, 10, 10, 10,  5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
      0,  0,  0,  5,  5,  0,  0,  0
};
const int wBishopTable[8][8] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
};
const int wKnightTable[8][8] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50
};
const int wPawnTable[8][8] = {
     0,  0,  0,  0,  0,  0,  0,  0,
    50, 50, 50, 50, 50, 50, 50, 50,
    10, 10, 20, 30, 30, 20, 10, 10,
     5,  5, 10, 25, 25, 10,  5,  5,
     0,  0,  0, 20, 20,  0,  0,  0,
     5, -5,-10,  0,  0,-10, -5,  5,
     5, 10, 10,-20,-20, 10, 10,  5,
     0,  0,  0,  0,  0,  0,  0,  0
};

// Black's Piece-Square Tables
const int bKingTableMid[8][8] = {
     20, 30, 10,  0,  0, 10, 30, 20,
     20, 20,  0,  0,  0,  0, 20, 20,
    -10,-20,-20,-20,-20,-20,-20,-10,
    -20,-30,-30,-40,-40,-30,-30,-20,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30,
    -30,-40,-40,-50,-50,-40,-40,-30
};
const int bQueenTable[8][8] = {
    -20,-10,-10, -5, -5,-10,-10,-20,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -10,  0,  5,  5,  5,  5,  0,-10,
      0,  0,  5,  5,  5,  5,  0, -5,
     -5,  0,  5,  5,  5,  5,  0, -5,
    -10,  5,  5,  5,  5,  5,  0,-10,
    -10,  0,  5,  0,  0,  0,  0,-10,
    -20,-10,-10, -5, -5,-10,-10,-20
};
const int bRookTable[8][8] = {
      0,  0,  0,  5,  5,  0,  0,  0,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
     -5,  0,  0,  0,  0,  0,  0, -5,
      5, 10, 10, 10, 10, 10, 10,  5,
      0,  0,  0,  0,  0,  0,  0,  0
};
const int bBishopTable[8][8] = {
    -20,-10,-10,-10,-10,-10,-10,-20,
    -10,  5,  0,  0,  0,  0,  5,-10,
    -10, 10, 10, 10, 10, 10, 10,-10,
    -10,  0, 10, 10, 10, 10,  0,-10,
    -10,  5,  5, 10, 10,  5,  5,-10,
    -10,  0,  5, 10, 10,  5,  0,-10,
    -10,  0,  0,  0,  0,  0,  0,-10,
    -20,-10,-10,-10,-10,-10,-10,-20
};
const int bKnightTable[8][8] = {
    -50,-40,-30,-30,-30,-30,-40,-50,
    -40,-20,  0,  5,  5,  0,-20,-40,
    -30,  5, 10, 15, 15, 10,  5,-30,
    -30,  0, 15, 20, 20, 15,  0,-30,
    -30,  5, 15, 20, 20, 15,  5,-30,
    -30,  0, 10, 15, 15, 10,  0,-30,
    -40,-20,  0,  0,  0,  0,-20,-40,
    -50,-40,-30,-30,-30,-30,-40,-50
};
const int bPawnTable[8][8] = {
      0,  0,  0,  0,  0,  0,  0,  0,
      5, 10, 10,-20,-20, 10, 10,  5,
      5, -5,-10,  0,  0,-10, -5,  5,
      0,  0,  0, 20, 20,  0,  0,  0,
      5,  5, 10, 25, 25, 10,  5,  5,
     10, 10, 20, 30, 30, 20, 10, 10,
     50, 50, 50, 50, 50, 50, 50, 50,
      0,  0,  0,  0,  0,  0,  0,  0
};


double material_score(map<char, int>& m, bool isAIPlayingWhite) {

    double black = PawnWt * m['p'] + KnightWt * m['n'] + BishopWt * m['b'] + RookWt * m['r'] + QueenWt * m['q'] + KingWt * m['k'];
    double white = PawnWt * m['P'] + KnightWt * m['N'] + BishopWt * m['B'] + RookWt * m['R'] + QueenWt * m['Q'] + KingWt * m['K'];
    // Here we should check a side 
    double finalScore = isAIPlayingWhite ? (black - white) : (white - black);
    return finalScore;
}


double static_eval(Node& root, bool isAIPlayingWhite) {
    double score = material_score(root->materials, isAIPlayingWhite);
    int i, j;
    for (i = 2; i < 10; i++) {
        for (j = 2; j < 10; j++) {
            char c = root->board[i][j];
            //if (isAIPlayingWhite)
            //{
            //    if ('K' == c)
            //        score -= wKingTableMid[i - 2][j - 2];
            //    if ('Q' == c)
            //        score -= wQueenTable[i - 2][j - 2];
            //    if ('R' == c)
            //        score -= wRookTable[i - 2][j - 2];
            //    if ('B' == c)
            //        score -= wBishopTable[i - 2][j - 2];
            //    if ('N' == c)
            //        score -= wKnightTable[i - 2][j - 2];
            //    if ('P' == c)
            //        score -= wPawnTable[i - 2][j - 2];

            //    // Black's pieces
            //    if ('k' == c)
            //        score += bKingTableMid[i - 2][j - 2];
            //    if ('q' == c)
            //        score += bQueenTable[i - 2][j - 2];
            //    if ('r' == c)
            //        score += bRookTable[i - 2][j - 2];
            //    if ('b' == c)
            //        score += bBishopTable[i - 2][j - 2];
            //    if ('n' == c)
            //        score += bKnightTable[i - 2][j - 2];
            //    if ('p' == c)
            //        score += bPawnTable[i - 2][j - 2];
            //}
            //else
            //{
                // White's pieces
                if ('K' == c)
                    score += wKingTableMid[i - 2][j - 2];
                if ('Q' == c)
                    score += wQueenTable[i - 2][j - 2];
                if ('R' == c)
                    score += wRookTable[i - 2][j - 2];
                if ('B' == c)
                    score += wBishopTable[i - 2][j - 2];
                if ('N' == c)
                    score += wKnightTable[i - 2][j - 2];
                if ('P' == c)
                    score += wPawnTable[i - 2][j - 2];

                // Black's pieces
                if ('k' == c)
                    score -= bKingTableMid[i - 2][j - 2];
                if ('q' == c)
                    score -= bQueenTable[i - 2][j - 2];
                if ('r' == c)
                    score -= bRookTable[i - 2][j - 2];
                if ('b' == c)
                    score -= bBishopTable[i - 2][j - 2];
                if ('n' == c)
                    score -= bKnightTable[i - 2][j - 2];
                if ('p' == c)
                    score -= bPawnTable[i - 2][j - 2];
           // }
        }
    }
    return score / 100;
}
