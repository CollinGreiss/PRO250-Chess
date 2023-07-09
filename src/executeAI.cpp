#include <iostream>
#include <vector>
#include <string>
#include "mainAI.h"

using namespace std;

int map_to_int(char c) {
    int val;
    switch (c) {
    case 'a': val = 1; break;
    case 'b': val = 2; break;
    case 'c': val = 3; break;
    case 'd': val = 4; break;
    case 'e': val = 5; break;
    case 'f': val = 6; break;
    case 'g': val = 7; break;
    case 'h': val = 8; break;
    default: val = 0;
    }
    return val;
}

void exec_player_move(Node& root, std::pair<std::string, MoveType>user_move)
{
    string mv = user_move.first;

    switch (user_move.second)
    {
    case MoveType::NORMAL:
        exec_normalMove(root, user_move.first);
        break;
    case MoveType::CASTLE:
        exec_CastleMove(root, user_move.first);
        break;
    case MoveType::ENPASSANT:
        exec_EnpassatMove(root, user_move.first);
        break;
    case MoveType::NEWPIECE:
        exec_NewPieceMove(root, user_move.first);
        break;
    default:
        break;
    }
    // Mapping mv to the correct array coordinates (s,t) --> (u,v)
}

void exec_normalMove(Node& root, string mv)
{
    int s = 8 - (mv.c_str()[1] - '0') + 2; //XStart
    int t = map_to_int(mv.c_str()[0]) + 1; //YStart
    int u = 8 - (mv.c_str()[3] - '0') + 2; //XEnd
    int v = map_to_int(mv.c_str()[2]) + 1; //YEnd

    // Replacing the target square with source square
    char source = root->board[s][t];
    char target = root->board[u][v];

    root->board[u][v] = source;
    root->board[s][t] = ' ';

    if (target != ' ')
        root->materials[target] -= 1;
}

void exec_CastleMove(Node& root, string mv)
{
    int XStart = map_to_int(mv.c_str()[0]) + 1; //XStart as a king position
    int YStart = 8 - (mv.c_str()[1] - '0') + 2; //YStart as a king position

    int XEnd = map_to_int(mv.c_str()[2]) + 1; //XEnd as a rook position
    int YEnd  = 8 - (mv.c_str()[3] - '0') + 2; //YEnd as a rook position

    int XKingPos = map_to_int(mv.c_str()[4]) + 1;
    int XRookPos = map_to_int(mv.c_str()[5]) + 1;

    root->board[YStart][XKingPos] = root->board[YStart][XStart];
    root->board[YStart][XRookPos] = root->board[YEnd][XEnd];

    root->board[YStart][XStart] = ' ';
    root->board[YEnd][XEnd] = ' ';
}

void exec_EnpassatMove(Node& root, string mv)
{
    int XStart = map_to_int(mv.c_str()[0]) + 1; //XStart as a king position
    int YStart = 8 - (mv.c_str()[1] - '0') + 2; //YStart as a king position

    int XEnd = map_to_int(mv.c_str()[2]) + 1; //XEnd as a rook position
    int YEnd = 8 - (mv.c_str()[3] - '0') + 2; //YEnd as a rook position

    int YPawnToDestroy = 8 - (mv.c_str()[4] - '0') + 2;

    root->board[YEnd][XEnd] = root->board[YStart][XStart];
    root->board[YStart][XStart] = ' ';

    root->board[YPawnToDestroy][XEnd] = ' ';
}

void exec_NewPieceMove(Node& root, string mv)
{
    int s = 8 - (mv.c_str()[1] - '0') + 2; //XStart
    int t = map_to_int(mv.c_str()[0]) + 1; //YStart
    int u = 8 - (mv.c_str()[3] - '0') + 2; //XEnd
    int v = map_to_int(mv.c_str()[2]) + 1; //YEnd

    // Replacing the target square with source square
    char source = root->board[s][t];
    char target = root->board[u][v];

    root->board[u][v] = mv[4];
    root->board[s][t] = ' ';

    if (target != ' ')
        root->materials[target] -= 1;
}
