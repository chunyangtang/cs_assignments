//
// Created by TCY on 2023/2/23.
//

#include <ctime>
#include <iostream>

#define MAX_ROUND 10000000

unsigned int CountBitZero(long long num) {
    unsigned int count = 0;
    while (num + 1) {
        num |= (num + 1);
        count++;
    }
    return count;
}

int main() {
    clock_t Start = clock();

    std::cout << "char size: " << sizeof(char) << " "
              << "\nint size: " << sizeof(int) << " "
              << "\nunsigned int size: " << sizeof(unsigned int) << " "
              << "\nlong size: " << sizeof(long) << " "
              << "\nlong long size: " << sizeof(long long) << " "
              << std::endl;

    char a = -127;  // 10000001 => 6
    int b = 0;  // 00...00 => 64
    unsigned int c = 4294967295;  // 00..0011..11 => 32
    long d = -8; // 1...1000 => 3
    long long e = -8; // 1...1000 => 3

    std::cout << CountBitZero(a) <<  " "
              << CountBitZero(b) <<  " "
              << CountBitZero(c) <<  " "
              << CountBitZero(d) <<  " "
              << CountBitZero(e) <<  " "
//              << CountBitZero(e) <<  " "
              << std::endl;

    for (unsigned Round = 1; Round < MAX_ROUND; Round++) {
        CountBitZero(a);
    }

    double elapsedTime = static_cast<double>(clock() - Start) / CLOCKS_PER_SEC;
    std::cout << elapsedTime << "s" << std::endl;

    return 0;
}
