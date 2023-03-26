//
//  main.cpp
//  md5_asm
//
//  Created by TCY on 2023/3/24.
//

#include <iostream>
#include "MD5.hpp"

int main(int argc, const char * argv[]) {
    
    std::cout << MD5::Encrypt("test") << std::endl;
    // Correct answer: "098F6BCD4621D373CADE4E832627B4F6"
    
    std::cout << MD5::Encrypt("Principles of Computer System") << std::endl;
    // Correct answer: "6C2768FA15680DDF22783C58A727D2D5"
    
    MD5 m1("Hello, World!");
    std::cout << m1 << endl;
    // Correct answer: "65A8E27D8879283831B664BD8B7F0AD4"
    
    return 0;
}

