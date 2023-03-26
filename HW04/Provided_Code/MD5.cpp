//
//  MD5_BIN.cpp
//  DEMO_DAY_04_USER_XCODE
//
//  Created by Jingtao Fan on 2021/8/2.
//

#include "MD5.hpp"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

const DWORD MD5::T[4][16] = {
    {
        0xD76AA478, 0xE8C7B756, 0x242070DB, 0xC1BDCEEE,
        0xF57C0FAF, 0x4787C62A, 0xA8304613, 0xFD469501,
        0x698098D8, 0x8B44F7AF, 0xFFFF5BB1, 0x895CD7BE,
        0x6B901122, 0xFD987193, 0xA679438E, 0x49B40821
    },
    {
        0xF61E2562, 0xC040B340, 0x265E5A51, 0xE9B6C7AA,
        0xD62F105D, 0x02441453, 0xD8A1E681, 0xE7D3FBC8,
        0x21E1CDE6, 0xC33707D6, 0xF4D50D87, 0x455A14ED,
        0xA9E3E905, 0xFCEFA3F8, 0x676F02D9, 0x8D2A4C8A
    },
    {
        0xFFFA3942, 0x8771F681, 0x6D9D6122, 0xFDE5380C,
        0xA4BEEA44, 0x4BDECFA9, 0xF6BB4B60, 0xBEBFBC70,
        0x289B7EC6, 0xEAA127FA, 0xD4EF3085, 0x04881D05,
        0xD9D4D039, 0xE6DB99E5, 0x1FA27CF8, 0xC4AC5665
    },
    {
        0xF4292244, 0x432AFF97, 0xAB9423A7, 0xFC93A039,
        0x655B59C3, 0x8F0CCC92, 0xFFEFF47D, 0x85845DD1,
        0x6FA87E4F, 0xFE2CE6E0, 0xA3014314, 0x4E0811A1,
        0xF7537E82, 0xBD3AF235, 0x2AD7D2BB, 0xEB86D391
    }
};

const DWORD MD5::S[4][16]={
    {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22},
    {5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20},
    {4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23},
    {6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21}
};

const DWORD MD5::M[4][16]={
    {0, 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15},
    {1, 6, 11,  0,  5, 10, 15,  4,  9, 14,  3,  8, 13,  2,  7, 12},
    {5, 8, 11, 14,  1,  4,  7, 10, 13,  0,  3,  6,  9, 12, 15,  2},
    {0, 7, 14,  5, 12,  3, 10,  1,  8, 15,  6, 13,  4, 11,  2,  9}
};

//default constructor, with no plaintext
MD5::MD5() : m_CipherText{}{
}

//constructor, with plaintext
MD5::MD5(const string& PlainText){
    m_CipherText = Encrypt(PlainText);
}

//copy constructor
MD5::MD5(const MD5& aMD5){
    m_CipherText = aMD5.m_CipherText;
}

//as the base class, considering the possibility of subsequent expansion and modification, the destructor should be a virtual function
MD5::~MD5(){
}

//Encypte plaintext to m_ciphertext via MD5 algorithm
void MD5::Update(const string& PlainText){
    m_CipherText = Encrypt(PlainText);
}

//the overloading of operator assigment function
MD5& MD5::operator=(const MD5& aMD5){
    if (this != &aMD5) {
        m_CipherText = aMD5.m_CipherText;
    }
    return *this;
}

//the overloading of operator equal function
bool MD5::operator==(const MD5& aMD5) const{
    return m_CipherText == aMD5.m_CipherText;
}

//the overloading of operator not equal function
bool MD5::operator!=(const MD5& aMD5) const{
    return m_CipherText != aMD5.m_CipherText;
}

//the overloading of stream insertion operator
ostream& operator<<(ostream& Stream, const MD5& aMD5){
    Stream << aMD5.m_CipherText;
    return Stream;
}

//the overloading of stream extraction operator
istream& operator>>(istream& Stream, MD5& aMD5){
    Stream >> aMD5.m_CipherText;
    return Stream;
}

//Encypte plaintext to return value as string via MD5 algorithm
string MD5::Encrypt(const string& Plaintext){
    BIT512 Plain{StrToBit512(Plaintext)};
    
    DWORD A = 0x67452301;
    DWORD B = 0xEFCDAB89;
    DWORD C = 0x98BADCFE;
    DWORD D = 0x10325476;
    
    for(int i = 0; i < 16; i++){
        FRound(A, B, C, D, Plain.Dword[M[0][i]], S[0][i], T[0][i]);
    }
    for(int i = 0; i < 16; i++){
        GRound(A, B, C, D, Plain.Dword[M[1][i]], S[1][i], T[1][i]);
    }
    for(int i = 0; i < 16; i++){
        HRound(A, B, C, D, Plain.Dword[M[2][i]], S[2][i], T[2][i]);
    }
    for(int i = 0; i < 16; i++){
        RRound(A, B, C, D, Plain.Dword[M[3][i]], S[3][i], T[3][i]);
    }
    
    BIT128 Cipher{{0}};
    Cipher.Dword[0] = A + 0x67452301;
    Cipher.Dword[1] = B + 0xEFCDAB89;
    Cipher.Dword[2] = C + 0x98BADCFE;
    Cipher.Dword[3] = D + 0x10325476;

    stringstream Res;
    for (int i = 0; i < 16; i++) {
        Res <<setiosflags(ios::uppercase) <<setw(2) << setfill('0')<< hex << static_cast<unsigned int>(Cipher.Byte[i]);
    }
    return Res.str();

}

//return a MD5 object from a ciphertext string
MD5 MD5::FromCipherText(const string& aCipherText){
    MD5 aMD5{};
    aMD5.m_CipherText = aCipherText;
    return aMD5;
}

//a tool function of making BIT512 from string, for input convertion of MD5 algorithm
BIT512 MD5::StrToBit512(const string& PlainText){
    unsigned long StrLen = PlainText.length();
    if (StrLen > 56) {
        throw string{"too long"};
    }
    BIT512 Res{{0}};
    for (unsigned long i = 0; i < StrLen; i++) {
        Res.Byte[i] = PlainText[i];
    }
    Res.Byte[StrLen] = 0x80;

    Res.QWord[7] = QWORD{StrLen << 3};
    return Res;
}

//---------------------------------------------------------
void MD5::FRound(DWORD& a, DWORD& b, DWORD& c, DWORD& d, DWORD mj, DWORD s, DWORD ti){
    auto F = [](DWORD X, DWORD Y, DWORD Z)->DWORD {return (X & Y) | ((~X) & Z);};
    DWORD temp = F(b, c, d) + a + mj + ti;
    temp = (temp << s) | (temp >> (32 - s));
    a = b + temp;
    //ABCD loop swap
    temp = a;
    a = d;
    d = c;
    c = b;
    b = temp;
}

void MD5::GRound(DWORD& a, DWORD& b, DWORD& c, DWORD& d, DWORD mj, DWORD s, DWORD ti){
    auto G = [](DWORD X, DWORD Y, DWORD Z)->DWORD {return (X & Z) | (Y & (~Z));};
    DWORD temp = G(b, c, d) + a + mj + ti;
    temp = (temp << s) | (temp >> (32 - s));
    a = b + temp;
    //ABCD loop swap
    temp = a;
    a = d;
    d = c;
    c = b;
    b = temp;
}

void MD5::HRound(DWORD& a, DWORD& b, DWORD& c, DWORD& d, DWORD mj, DWORD s, DWORD ti){
    auto H = [](DWORD X, DWORD Y, DWORD Z)->DWORD {return X ^ Y ^ Z;};
    DWORD temp = H(b,c,d) + a + mj + ti;
    temp = (temp << s) | (temp >> (32 - s));
    a = b + temp;
    //ABCD loop swap
    temp = a;
    a = d;
    d = c;
    c = b;
    b = temp;
}

void MD5::RRound(DWORD& a, DWORD& b, DWORD& c, DWORD& d, DWORD mj, DWORD s, DWORD ti){
    auto I = [](DWORD X, DWORD Y, DWORD Z)->DWORD {return Y ^ (X | (~Z));};
    DWORD temp = I(b, c, d) + a + mj + ti;
    temp = (temp << s)|(temp >> (32 - s));
    a = b + temp;
    //ABCD loop swap
    temp = a;
    a = d;
    d = c;
    c = b;
    b = temp;
}
