//
// Created by TCY on 2023/2/23.
//

#include <ctime>
#include <iostream>

#define MAX_ROUND 10000000

unsigned int CountBitZero1(long long num) {
    /*
     * 思路：将num逐位位移，判断最低位是否为0
     * 需要用到判断、循环
     * */
    unsigned int count = 0;
    for (unsigned i = 0; i < sizeof(long long) * 8; i++) {
        count += ((num & 1) == 0);
        num >>= 1;
    }
    return count;
}

unsigned int CountBitZero2(long long num) {
    /*
     * 思路：观察发现 num|num+1 会为 num 增加一个0（考虑 num 末位 为0/为1 两种情况即可证明）
     * 需要用到循环（当然，循环跳出的条件需要每次判断）
     * 参考资料：https://blog.csdn.net/makunIT/article/details/104692949
     * */
    unsigned int count = 0;
    while (num + 1) {
        num |= (num + 1);
        count++;
    }
    return count;
}

unsigned int CountBitZero3(unsigned long long num) {
//    // 对于num中的每2位ab求"2a+b-a=a+b"
//    num = num - (num>>1 & (unsigned long long)0b0101010101010101010101010101010101010101010101010101010101010101);
//    num = sizeof(long long) * 8 - num % 3;
    /*
     * 思路：分治地将每3位=>每6位含1的个数表示出来，在使用取模的特性得到含1的个数
     * 参考资料：https://www.jianshu.com/p/a5114a581900
     * 注：不太清楚如果按上面注释掉的代码哪里会出问题。
     * */
    num = num-((num>>1)&0333333333333333333333)-((num>>2)&0111111111111111111111);
    num = (num+(num>>3))&0707070707070707070707;
    return sizeof(unsigned long long)*8-num%63;
}

int main() {

    std::cout << "char size: " << sizeof(char) << " "
              << "\nint size: " << sizeof(int) << " "
              << "\nunsigned int size: " << sizeof(unsigned int) << " "
              << "\nlong size: " << sizeof(long) << " "
              << "\nlong long size: " << sizeof(long long) << " "
              << std::endl;

    // 检验正确性
    char a = -127;  // 10000001 => 6
    int b = 0;  // 00...00 => 64
    unsigned int c = 4294967295;  // 00..0011..11 => 32
    long d = -8; // 1...1000 => 3
    long long e = -8; // 1...1000 => 3

    std::cout << CountBitZero1(a) <<  " "
              << CountBitZero1(b) <<  " "
              << CountBitZero1(c) <<  " "
              << CountBitZero1(d) <<  " "
              << CountBitZero1(e) <<  " "
              << std::endl;

    std::cout << CountBitZero2(a) <<  " "
              << CountBitZero2(b) <<  " "
              << CountBitZero2(c) <<  " "
              << CountBitZero2(d) <<  " "
              << CountBitZero2(e) <<  " "
              << std::endl;

    std::cout << CountBitZero3(a) <<  " "
              << CountBitZero3(b) <<  " "
              << CountBitZero3(c) <<  " "
              << CountBitZero3(d) <<  " "
              << CountBitZero3(e) <<  " "
              << std::endl;

    // 比较时间
    clock_t Start = clock();

    for (unsigned Round = 1; Round < MAX_ROUND; Round++) {
        CountBitZero1(a);
    }
    double elapsedTime = static_cast<double>(clock() - Start) / CLOCKS_PER_SEC;
    std::cout << "Method 1: " << elapsedTime << "s" << std::endl;

    Start = clock();
    for (unsigned Round = 1; Round < MAX_ROUND; Round++) {
        CountBitZero2(a);
    }
    elapsedTime = static_cast<double>(clock() - Start) / CLOCKS_PER_SEC;
    std::cout << "Method 2: " << elapsedTime << "s" << std::endl;

    Start = clock();
    for (unsigned Round = 1; Round < MAX_ROUND; Round++) {
        CountBitZero3(a);
    }
    elapsedTime = static_cast<double>(clock() - Start) / CLOCKS_PER_SEC;
    std::cout << "Method 3: " << elapsedTime << "s" << std::endl;

    /*
     * 输出样例：
     *  char size: 1
        int size: 4
        unsigned int size: 4
        long size: 8
        long long size: 8
        6 64 32 3 3
        6 64 32 3 3
        6 64 32 3 3
        Method 1: 0.688616s
        Method 2: 0.061896s
        Method 3: 0.020598s
     * */

    return 0;
}
