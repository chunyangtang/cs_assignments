//
//  Othello.cpp
//  Othello
//
//  Created by 范静涛 on 2022/4/2.
//

#include "Othello.hpp"
#include <iostream>
using namespace std;

const char OthBoard::DEFAULT_BOARD[SIZE][SIZE] = {
    //A         B         C         D         E         F         G         H
     {Color::S, Color::S, Color::S, Color::S, Color::S, Color::S, Color::S, Color::S},  //1
     {Color::S, Color::S, Color::S, Color::S, Color::S, Color::S, Color::S, Color::S},  //2
     {Color::S, Color::S, Color::S, Color::S, Color::S, Color::S, Color::S, Color::S},  //3
     {Color::S, Color::S, Color::S, Color::B, Color::W, Color::S, Color::S, Color::S},  //4
     {Color::S, Color::S, Color::S, Color::W, Color::B, Color::S, Color::S, Color::S},  //5
     {Color::S, Color::S, Color::S, Color::S, Color::S, Color::S, Color::S, Color::S},  //6
     {Color::S, Color::S, Color::S, Color::S, Color::S, Color::S, Color::S, Color::S},  //7
     {Color::S, Color::S, Color::S, Color::S, Color::S, Color::S, Color::S, Color::S}   //8
};

// BitBoard默认值初始化，替代原DEFAULT_BOARD
const BitBoard OthBoard::DEFAULT_BOARD_BITWISE[2] = {0b1000000001000000000000000000000000000, // Black
                                                     0b100000010000000000000000000000000000}; // White

OthBoard::OthBoard(){
    Init();
}

OthBoard::OthBoard(const OthBoard& Source){
    //copy
    for (unsigned int Row = 0; Row < SIZE; Row++) {
        for (unsigned int Col = 0; Col < SIZE; Col++) {
            Board[Row][Col] = Source.Board[Row][Col];
        }
    }
    // 对黑、白BitBoard赋值，替代循环
    Board_Bitwise[Color::B] = Source.Board_Bitwise[Color::B];
    Board_Bitwise[Color::W] = Source.Board_Bitwise[Color::W];
}

OthBoard& OthBoard::operator=(const OthBoard& Source){
    if (this != &Source) {
        //copy
        for (unsigned int Row = 0; Row < SIZE; Row++) {
            for (unsigned int Col = 0; Col < SIZE; Col++) {
                Board[Row][Col] = Source.Board[Row][Col];
            }
        }
        // 对黑、白BitBoard赋值，替代循环
        Board_Bitwise[Color::B] = Source.Board_Bitwise[Color::B];
        Board_Bitwise[Color::W] = Source.Board_Bitwise[Color::W];
    }
    return *this;
}

OthBoard::~OthBoard(){
}

void OthBoard::Init(){
    //copy from default board
    for (unsigned int Row = 0; Row < SIZE; Row++) {
        for (unsigned int Col = 0; Col < SIZE; Col++) {
            Board[Row][Col] = DEFAULT_BOARD[Row][Col];
        }
    }
    
    // 对黑、白BitBoard赋值，替代循环
    Board_Bitwise[Color::B] = DEFAULT_BOARD_BITWISE[Color::B];
    Board_Bitwise[Color::W] = DEFAULT_BOARD_BITWISE[Color::W];
}

void OthBoard::Print() const{
    cout << "  A B C D E F G H\n";
    for (unsigned int Row = 0; Row < SIZE; Row++) {
        cout << " +-+-+-+-+-+-+-+-+\n" << Row + 1 << '|' ;
        for (unsigned int Col = 0; Col < SIZE; Col++) {
            cout << STATUS[Board[Row][Col]] << '|';
            // 替代上一步
            // cout << STATUS[2-2*Board_Bitwise[Color::B][Row*SIZE+Col]-Board_Bitwise[Color::W][Row*SIZE+Col]] << '|';
        }
        cout << '\n';
    }
    cout << " +-+-+-+-+-+-+-+-+\n" << endl;
}

void OthBoard::Print_BitBoard() const{
    cout << "  A B C D E F G H\n";
    for (unsigned int Row = 0; Row < SIZE; Row++) {
        cout << " +-+-+-+-+-+-+-+-+\n" << Row + 1 << '|' ;
        for (unsigned int Col = 0; Col < SIZE; Col++) {
            cout << STATUS[2-2*Board_Bitwise[Color::B][Row*SIZE+Col]-Board_Bitwise[Color::W][Row*SIZE+Col]] << '|';
        }
        cout << '\n';
    }
    cout << " +-+-+-+-+-+-+-+-+\n" << endl;
}


//Get the number of pieces that can be flipped in a certain direction, when you put own piece into the specified position
unsigned int OthBoard::CountDrctnlFlips(RowNo Row, ColNo Col, Direction Dir, Color Side) const{
    char OwnSide = Side;
    char OppSide = 1 - OwnSide;
    unsigned int FlipCount  = 0;
    
    //only can put a piece into a space
    if (Board[Row][Col] != Color::S) {
        return FlipCount;
    }
    
    //search for a continued oppside serial
    int RowOffset = NBHS[Dir].RowOffset;
    int ColOffset = NBHS[Dir].ColOffset;
    int CurrentRow = Row + RowOffset;
    int CurrentCol = Col + ColOffset;
    while (CurrentRow < SIZE //先判断位置后颜色，绝对不能反，否则可能越界
        && CurrentCol < SIZE
        && Board[CurrentRow][CurrentCol] == OppSide){
        //add one oppside count
        FlipCount++;
        //add step to search next position
        // 变乘法为加法，提升计算效率
        CurrentRow += RowOffset;
        CurrentCol += ColOffset;
    }//end while
    
    //afer an oppside serial, is an own side piece
    if (   CurrentRow < SIZE //先判断位置后颜色，绝对不能反，否则可能越界
        && CurrentCol < SIZE
        && Board[CurrentRow][CurrentCol] == OwnSide){
        return FlipCount;
    }
    else {
        return 0;
    }
}

//Get the number of pieces that can be flipped, when you put own piece into the specified position
unsigned int OthBoard::CountFlips(RowNo Row, ColNo Col, Color Side) const{
    unsigned int TotalFlipCount = 0;
    for (auto e : DIRS) {
        TotalFlipCount += CountDrctnlFlips(Row, Col, e, Side);
    }
    // TotalFlipCount一定大于0，这里return时不需要条件判断
    return TotalFlipCount;

}

//Flip and return counts
unsigned int OthBoard::DoFlips(RowNo Row, ColNo Col, Color Side){
    unsigned int TotalFlipCount = 0;
    //Flip to each direction
    for (auto e : DIRS) {
        //flip count of this direction
        unsigned int FlipCount = CountDrctnlFlips(Row, Col, e, Side);
        TotalFlipCount += FlipCount;
        int RowOffset = NBHS[e].RowOffset;
        int ColOffset = NBHS[e].ColOffset;
        int CurrentRow = Row + RowOffset;
        int CurrentCol = Col + ColOffset;
        for (int Step = 1; Step <= FlipCount; Step++) {
            Board[CurrentRow][CurrentCol] = Side;
            // 变乘法为加法，提升计算效率
            CurrentRow += RowOffset;
            CurrentCol += ColOffset;
        }
    }
    if (TotalFlipCount > 0) {
        Board[Row][Col] = Side;
        return TotalFlipCount;
    }
    else {
        return 0;
    }
}

