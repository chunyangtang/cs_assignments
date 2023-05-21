//
//  Othello.hpp
//  Othello
//
//  Created by 范静涛 on 2022/4/2.
//

#ifndef Othello_hpp
#define Othello_hpp

#include <bitset>

//Color: black, white, space(no piece)
class ColorEnum {
public:
    enum Type{
        B = 0, //Black
        W = 1, //White
        S = 2  //Space
    };
private:
    //This class is not instantiatable
    virtual void NoInstance() = 0;
};
using Color = ColorEnum::Type;

//Directions for search
class DirEnum{
public:
    enum Type{
        LEFT       = 0,
        LEFT_UP    = 1,
        UP         = 2,
        RIGHT_UP   = 3,
        RIGHT      = 4,
        RIGHT_DOWN = 5,
        DOWN       = 6,
        LEFT_DOWN  = 7
    };
private:
    //This class is not instantiatable
    virtual void NoInstance() = 0;
};
using Direction = DirEnum::Type;

//Row Number for R1 to R8
class RowNoEnum{
public:
    enum Type{
        R1 = 0,
        R2 = 1,
        R3 = 2,
        R4 = 3,
        R5 = 4,
        R6 = 5,
        R7 = 6,
        R8 = 7
    };
private:
    //This class is not instantiatable
    virtual void NoInstance() = 0;
};
using RowNo = RowNoEnum::Type;

//Column number from A to H
class ColNoEnum{
public:
    enum Type{
        A = 0,
        B = 1,
        C = 2,
        D = 3,
        E = 4,
        F = 5,
        G = 6,
        H = 7
    };
private:
    //This class is not instantiatable
    virtual void NoInstance() = 0;
};
using ColNo = ColNoEnum::Type;

//Row and Col offsets for neighborhood in the board
using Neighborhood = struct {
    int RowOffset;
    int ColOffset;
};

// 由于外部声明需要，这里重新定义了SIZE，需要与类中的SIZE一同修改
constexpr const int  SIZE = 8;

using BitBoard = std::bitset<SIZE * SIZE>;

//Class for Othello games
class OthBoard{
public:
    // -------BITBOARD 与 2D 棋盘公共的成员-------
    //Default Constructor
    OthBoard();
    //Copy Constructor
    OthBoard(const OthBoard& Source);
    //Operator Assignment
    OthBoard& operator=(const OthBoard& Source);
    //Virtual destructor
    virtual ~OthBoard();
    
    //........
    //........
    //........
    //...BW...
    //...WB...
    //........
    //........
    //........
    void Init();
    
    // -------仅 2D 棋盘使用的成员-------
    //Print currnet board with pieces
    void Print() const;
    //Get whether or not you can flip in a certain direction, without counting the number of flips
    inline bool AnyDrctnlFlips(RowNo Row, ColNo Col, Direction Dir, Color Side) const {
        return CountDrctnlFlips(Row, Col, Dir, Side) != 0;
    }
    //Get the number of pieces that can be flipped in one direction, when you put own piece into the specified position
    unsigned int CountDrctnlFlips(RowNo Row, ColNo Col, Direction Dir, Color Side) const;
    //Get whether or not you can flip, without counting the number of flips
    inline bool AnyFlips(RowNo Row, ColNo Col, Color Side) const {
        return CountFlips(Row, Col, Side) != 0;
    }
    //Get the number of pieces that can be flipped, when you put own piece into the specified position
    unsigned int CountFlips(RowNo Row, ColNo Col, Color Side) const;
    //Flip and return counts
    unsigned int DoFlips(RowNo Row, ColNo Col, Color Side);
    
    
    
    // ---------仅BitBoard使用的成员---------
    // 打印BitBoard棋盘
    void Print_BitBoard() const;
    // BitBoard获取棋盘上的棋子个数
    inline unsigned long CountWhite() const{
        return Board_Bitwise[Color::W].count();
    }
    inline unsigned long CountBlack() const{
        return Board_Bitwise[Color::B].count();
    }
    
    // BitBoard模板类，用于得到可能翻子的棋盘位置
    template<bool ShiftToLeft, unsigned int ShiftCount>
    constexpr inline BitBoard MaskShift(BitBoard OwnBoard, BitBoard OppBoard, BitBoard Mask) const {
        BitBoard MaskedOpp = OppBoard & Mask;
        BitBoard PotentialFlips = MaskedOpp;
        if constexpr(ShiftToLeft) {
            PotentialFlips &= (OwnBoard << ShiftCount);
            PotentialFlips |= MaskedOpp & (PotentialFlips << ShiftCount);
            PotentialFlips |= MaskedOpp & (PotentialFlips << ShiftCount);
            PotentialFlips |= MaskedOpp & (PotentialFlips << ShiftCount);
            PotentialFlips |= MaskedOpp & (PotentialFlips << ShiftCount);
            PotentialFlips |= MaskedOpp & (PotentialFlips << ShiftCount);
        }
        else {
            PotentialFlips &= (OwnBoard >> ShiftCount);
            PotentialFlips |= MaskedOpp & (PotentialFlips >> ShiftCount);
            PotentialFlips |= MaskedOpp & (PotentialFlips >> ShiftCount);
            PotentialFlips |= MaskedOpp & (PotentialFlips >> ShiftCount);
            PotentialFlips |= MaskedOpp & (PotentialFlips >> ShiftCount);
            PotentialFlips |= MaskedOpp & (PotentialFlips >> ShiftCount);
        }
        return PotentialFlips;
    }
    
    // BitBoard棋盘各方向全部可翻子数统计，函数实际为模板类MaskShift的特化
    // 由于bitset对位移操作的方向不同，这里位移方向与课堂介绍相反。
    template<Direction Dir>
    inline BitBoard PotentialFlips(BitBoard OwnBoard, BitBoard OppBoard) const {
        if constexpr (Dir == Direction::LEFT) {
            return MaskShift<true, 1>(OwnBoard, OppBoard, 0x7E7E7E7E7E7E7E7EULL);
        }
        else if constexpr(Dir == Direction::LEFT_UP) {
            return MaskShift<true, 9>(OwnBoard, OppBoard, 0x007E7E7E7E7E7E00ULL);
        }
        else if constexpr(Dir == Direction::UP) {
            return MaskShift<true, 8>(OwnBoard, OppBoard, 0x00FFFFFFFFFFFF00ULL);
        }
        else if constexpr(Dir == Direction::RIGHT_UP) {
            return MaskShift<true, 7>(OwnBoard, OppBoard, 0x007E7E7E7E7E7E00ULL);
        }
        else if constexpr(Dir == Direction::RIGHT) {
            return MaskShift<false, 1>(OwnBoard, OppBoard, 0x7E7E7E7E7E7E7E7EULL);
        }
        else if constexpr(Dir == Direction::RIGHT_DOWN) {
            return MaskShift<false, 9>(OwnBoard, OppBoard, 0x007E7E7E7E7E7E00ULL);
        }
        else if constexpr(Dir == Direction::DOWN) {
            return MaskShift<false, 8>(OwnBoard, OppBoard, 0x00FFFFFFFFFFFF00ULL);
        }
        else {  // (Dir == Direction::LEFT_DOWN)
            return MaskShift<false, 7>(OwnBoard, OppBoard, 0x007E7E7E7E7E7E00ULL);
        }
    }
    
    // BitBoard棋盘的翻子辅助操作，用于取当前特定行列棋子的可翻子
    // 在DoFlips_BitBoard与CountFlips_BitBoard中调用，函数实际为模板类MaskShift的特化
    // 由于bitset对位移操作的方向不同，这里位移方向与课堂介绍相反。
    template<Direction Dir>
    inline BitBoard Flip(BitBoard OwnBoard, BitBoard OppBoard) const {
        // 这里的OwnBoard与OppBoard实际代指希望下子的位置OwnPosition与全部可翻子个数PotentialFlips
        if constexpr (Dir == Direction::LEFT) {
            return MaskShift<false, 1>(OwnBoard, OppBoard, 0xFEFEFEFEFEFEFEFEULL);
        }
        else if constexpr (Dir == Direction::LEFT_UP) {
            return MaskShift<false, 9>(OwnBoard, OppBoard, 0xFEFEFEFEFEFEFE00ULL);
        }
        else if constexpr (Dir == Direction::UP) {
            return MaskShift<false, 8>(OwnBoard, OppBoard, 0xFFFFFFFFFFFFFF00ULL);
        }
        else if constexpr (Dir == Direction::RIGHT_UP) {
            return MaskShift<false, 7>(OwnBoard, OppBoard, 0x7F7F7F7F7F7F7F00ULL);
        }
        else if constexpr (Dir == Direction::RIGHT) {
            return MaskShift<true, 1>(OwnBoard, OppBoard, 0x7F7F7F7F7F7F7F7FULL);
        }
        else if constexpr (Dir == Direction::RIGHT_DOWN) {
            return MaskShift<true, 9>(OwnBoard, OppBoard, 0x007F7F7F7F7F7F7FULL);
        }
        else if constexpr (Dir == Direction::DOWN) {
            return MaskShift<true, 8>(OwnBoard, OppBoard, 0x00FFFFFFFFFFFFFFULL);
        }
        else {  // (Dir == Direction::LEFT_DOWN)
            return MaskShift<true, 7>(OwnBoard, OppBoard, 0x00FEFEFEFEFEFEFEULL);
        }
    }
    
    // BitBoard棋盘查看特定方向可翻子数
    template<Direction Dir>
    inline unsigned long CountDrctnlFlips_BitBoard(RowNo Row, ColNo Col, Color Side) const {
        BitBoard OwnBoard = Board_Bitwise[Side];
        BitBoard OppBoard = Board_Bitwise[1-Side];
        BitBoard OwnPos;
        OwnPos[Row * SIZE + Col] = 1;
        BitBoard Temp = PotentialFlips<Dir>(OwnBoard, OppBoard);
        BitBoard FlipPattern = Flip<Dir>(OwnPos, Temp);
        
        return FlipPattern.count();
    }
    
    // BitBoard棋盘查看全部可翻子数
    inline unsigned long CountFlips_BitBoard(RowNo Row, ColNo Col, Color Side) const {
        BitBoard OwnBoard = Board_Bitwise[Side];
        BitBoard OppBoard = Board_Bitwise[1-Side];
        BitBoard OwnPos;
        OwnPos[Row * SIZE + Col] = 1;
        
        BitBoard Temp = PotentialFlips<Direction::LEFT>(OwnBoard, OppBoard);
        BitBoard FlipPattern = Flip<Direction::LEFT>(OwnPos, Temp);
        
        Temp = PotentialFlips<Direction::LEFT_UP>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::LEFT_UP>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::UP>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::UP>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::RIGHT_UP>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::RIGHT_UP>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::RIGHT>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::RIGHT>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::RIGHT_DOWN>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::RIGHT_DOWN>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::DOWN>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::DOWN>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::LEFT_DOWN>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::LEFT_DOWN>(OwnPos, Temp);
        
        return FlipPattern.count();
    }
    
    // BitBoard棋盘看某个点在一个方向上是否可翻子
    template<Direction Dir>
    inline bool AnyDrctnlFlips_BitBoard(RowNo Row, ColNo Col, Color Side) const {
        return CountDrctnlFlips_BitBoard<Dir>(Row, Col, Side) != 0;
    }
    
    // BitBoard棋盘看某个点上全部方向是否可翻子
    inline bool AnyFlips_BitBoard(RowNo Row, ColNo Col, Color Side) const {
        return CountFlips_BitBoard(Row, Col, Side) != 0;
    }
    
    // BitBoard棋盘翻子操作
    inline bool DoFlips_BitBoard(RowNo Row, ColNo Col, Color Side) {
        BitBoard OwnBoard = Board_Bitwise[Side];
        BitBoard OppBoard = Board_Bitwise[1-Side];
        BitBoard OwnPos;
        OwnPos[Row * SIZE + Col] = 1;

        BitBoard Temp = PotentialFlips<Direction::LEFT>(OwnBoard, OppBoard);
        BitBoard FlipPattern = Flip<Direction::LEFT>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::LEFT_UP>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::LEFT_UP>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::UP>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::UP>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::RIGHT_UP>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::RIGHT_UP>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::RIGHT>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::RIGHT>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::RIGHT_DOWN>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::RIGHT_DOWN>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::DOWN>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::DOWN>(OwnPos, Temp);

        Temp = PotentialFlips<Direction::LEFT_DOWN>(OwnBoard, OppBoard);
        FlipPattern |= Flip<Direction::LEFT_DOWN>(OwnPos, Temp);
        
        Board_Bitwise[Side] ^= (FlipPattern | OwnPos);
        Board_Bitwise[1 - Side] ^= FlipPattern;
        
        return (FlipPattern != 0);
        
    }

protected:
    // -------BITBOARD 与 2D 棋盘公共的成员-------
    //Board Size 8 by 8
    // 由于外部声明需要，类外也定义了SIZE，此处需要与类外的SIZE一同修改
    constexpr static const int  SIZE = 8;
    //char for print: black, white, space
    constexpr static const char STATUS[3]={'B','W',' '};
    //enum array for convert from int to row number
    constexpr static const RowNo ROWS[] = {RowNo::R1, RowNo::R2, RowNo::R3, RowNo::R4, RowNo::R5, RowNo::R6, RowNo::R7, RowNo::R8};
    //enum array for convert from int to column number
    constexpr static const ColNo COLS[] = {ColNo::A,  ColNo::B,  ColNo::C,  ColNo::D,  ColNo::E,  ColNo::F,  ColNo::G,  ColNo::H};
    //enum array for convert from int to search direction
    constexpr static const Direction DIRS[] = {Direction::LEFT, Direction::LEFT_UP, Direction::UP,Direction::RIGHT_UP, Direction::RIGHT, Direction::RIGHT_DOWN, Direction::DOWN, Direction::LEFT_DOWN};
    
    //array of row and column offsets for search by direction
    // -------仅 2D 棋盘使用的成员-------
    constexpr static const Neighborhood NBHS[8] = {
        {.RowOffset =  0, .ColOffset = -1},  //←
        {.RowOffset = -1, .ColOffset = -1},  //↖
        {.RowOffset = -1, .ColOffset =  0},  //↑
        {.RowOffset = -1, .ColOffset =  1},  //↗
        {.RowOffset =  0, .ColOffset =  1},  //→
        {.RowOffset =  1, .ColOffset =  1},  //↘
        {.RowOffset =  1, .ColOffset =  0},  //↓
        {.RowOffset =  1, .ColOffset = -1}   //↙
    };

private:
    // -------仅 2D 棋盘使用的成员-------
    //default board
    //........
    //........
    //........
    //...BW...
    //...WB...
    //........
    //........
    //........
    static const char DEFAULT_BOARD[SIZE][SIZE];
    char Board[SIZE][SIZE];
    
    // ---------仅BitBoard使用的成员---------
    static const BitBoard DEFAULT_BOARD_BITWISE[2];
    BitBoard Board_Bitwise[2];
};

#endif /* Othello_hpp */
