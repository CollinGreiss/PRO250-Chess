#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include "Misc.h"
#include "mainAI.h"
#include "Piece.h"

using namespace std;
vector<string> prev_moves;


void print_materials(map<char, int>& m) {
    map<char, int>::iterator it;
    for (it = m.begin(); it != m.end(); it++)
        cout << it->first << "  " << it->second << endl;
}

// ========== Initializes the materials for the game ==========
void init_materials(map<char, int>& m) {
    // Black's Pieces
    m.insert(pair<char, int>('p', 8));
    m.insert(pair<char, int>('r', 2));
    m.insert(pair<char, int>('n', 2));
    m.insert(pair<char, int>('b', 2));
    m.insert(pair<char, int>('q', 1));
    m.insert(pair<char, int>('k', 1));

    // White's Pieces
    m.insert(pair<char, int>('P', 8));
    m.insert(pair<char, int>('R', 2));
    m.insert(pair<char, int>('N', 2));
    m.insert(pair<char, int>('B', 2));
    m.insert(pair<char, int>('Q', 1));
    m.insert(pair<char, int>('K', 1));
}


//int main() {
//    // INITIALIZES NODE VARIABLES
//    Node root = new tNode;
//    init_materials(root->materials);
//    root->cur_side = 0; // 0 denotes human/player side
//    print_board(root);
//
//    string user_input;
//    Node best;
//    while (true) {
//
//        // HUMAN SIDE FUNCTIONALITY
//        cin >> user_input;
//        if (user_input == "q" || user_input == "quit") {
//            break;
//        }
//
//        exec_player_move(root, user_input);
//        print_board(root);
//
//        if (root->materials['k'] == 0) {
//            cout << "*******************************************************" << endl;
//            cout << "******************* HUMAN SIDE WINS *******************" << endl;
//            cout << "*******************************************************" << endl;
//            break;
//        }
//
//        // COMPUTER SIDE FUNCTIONALITY
//        next_move(root, 0);
//
//        minimax_alpha_beta(root, best, 0, 0, LOWEST_SCORE, HIGHEST_SCORE);
//        print_board(best);
//
//        static_evals = 0;
//
//        int a, b;
//        for (a = 0; a < 12; a++) {
//            for (b = 0; b < 12; b++) {
//                root->board[a][b] = best->board[a][b];
//            }
//        }
//        root->materials = best->materials;
//        root->w_king_pos = best->w_king_pos;
//        root->b_king_pos = best->b_king_pos;
//
//        tree_delete(root);
//        prev_moves.clear();
//
//        if (root->materials['K'] == 0) {
//            cout << "*******************************************************" << endl;
//            cout << "****************** COMPUTER SIDE WINS *****************" << endl;
//            cout << "*******************************************************" << endl;
//            break;
//        }
//    }
//    return 0;
//}

mainAI::mainAI(Piece::Team playerTeam )
{
    root = new tNode;
    init_materials(root->materials);

    root->cur_side = playerTeam == Piece::Team::WHITE? 0 : 1; // 0 denotes human/player side
    isAIPlayingWhite = playerTeam == Piece::Team::WHITE ? false : true;

  //  print_board(root); //Doesnt work
}

mainAI::~mainAI()
{
}


void mainAI::GetUserInput(std::pair<std::string, MoveType>user_input)
{
    exec_player_move(root, user_input);
    //print_board(root);

}

string mainAI::CalculateAIMove()
{
    string AIMove;
    botIsThinking = true;
    next_move(root, 0);
    minimax_alpha_beta(root, best, 0, 0, LOWEST_SCORE, HIGHEST_SCORE, isAIPlayingWhite);
    AIMove = ExtractMove();

    ChangeRootPos();
    //print_board(root);
    botIsThinking = false;
    return AIMove;
}

//void print_row(char row[]) {
//    int i;
//
//    for (i = 2; i < 10; i++)
//        cout << '|' << "  " << row[i] << "  ";
//    cout << '|' << endl;
//    cout << "      +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
//}
//
//
//void print_board(Node& root) {
//    cout << "      +-----+-----+-----+-----+-----+-----+-----+-----+" << endl;
//    int i;
//    int col = 8;
//    for (i = 2; i < 10; i++) {
//        cout << "   " << col << "  ";
//        col--;
//        print_row(root->board[i]);
//    }
//    cout << "         A     B     C     D     E     F     G     H   " << endl << endl;
//}

string mainAI::ExtractMove()
{
    int col = 8;
    string AIMove;
    for (int i = 2; i < 10; i++) 
    {
        for (int row = 2; row < 10; row++)
        {
            if (root->board[i][row] != best->board[i][row])
            {
                AIMove += to_string(row - 2);
                AIMove += to_string(col);
               // cout << "Row = " << boardXLetters[(row - 2)] << "Column = " << (col) << endl;
            }
        }

        col--;
    }

   // cout << "AI move = " << AIMove << endl;
    return AIMove;
}


void mainAI::ChangeRootPos()
{
    static_evals = 0;

    int a, b;
    for (a = 0; a < 12; a++) {
        for (b = 0; b < 12; b++) {
            root->board[a][b] = best->board[a][b];
        }
    }
    root->materials = best->materials;
    root->w_king_pos = best->w_king_pos;
    root->b_king_pos = best->b_king_pos;

    tree_delete(root);
    prev_moves.clear();
}

