//
//  main.cpp
//  Othello
//
//  Created by 范静涛 on 2022/4/2.
//

#include "Othello.hpp"
#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    OthBoard Board;
    Board.Print();
    Board.Print_BitBoard();

    Board.DoFlips(RowNo::R3, ColNo::D, Color::W);
    Board.DoFlips_BitBoard(RowNo::R3, ColNo::D, Color::W);
    
    Board.DoFlips(RowNo::R3, ColNo::E, Color::B);
    Board.DoFlips_BitBoard(RowNo::R3, ColNo::E, Color::B);
    
    Board.DoFlips(RowNo::R6, ColNo::F, Color::W);
    Board.DoFlips_BitBoard(RowNo::R6, ColNo::F, Color::W);
    
    Board.Print();
    Board.Print_BitBoard();
    cout << Board.CountFlips(RowNo::R3, ColNo::F, Color::W) << endl;
    cout << Board.CountFlips_BitBoard(RowNo::R3, ColNo::F, Color::W) << endl;
    
    return 0;
}
