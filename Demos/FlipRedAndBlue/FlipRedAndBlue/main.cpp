//
//  main.cpp
//  FlipRedAndBlue
//
//  Created by 范静涛 on 2023/2/19.
//

#include <iostream>

// Flips The Red And Blue Bytes (256x256)
void flipIt_C(unsigned char* buffer) {
    unsigned char* b = buffer;
    unsigned char temp;
    for (int i = 0; i < 256 * 256; i++) {
        temp = b[i * 3 + 0];
        b[i * 3 + 0] = b[i * 3 + 2];
        b[i * 3 + 2] = temp;
    }
}

// Flips The Red And Blue Bytes (256x256)
void flipIt_ASM(void* buffer) {
    void* b = buffer;       // Pointer To The Buffer
    __asm {                 // Assembler Code To Follow
        mov ecx, 256*256    // Set Up A Counter (Dimensions Of Memory Block)
        mov ebx, b          // Points ebx To Our Data (b)
        label:              // Label Used For Looping
            mov al,[ebx+0]  // Loads Value At ebx Into al
            mov ah,[ebx+2]  // Loads Value At ebx+2 Into ah
            mov [ebx+2],al  // Stores Value In al At ebx+2
            mov [ebx+0],ah  // Stores Value In ah At ebx
            add ebx,3       // Moves Through The Data By 3 Bytes
            dec ecx         // Decreases Our Loop Counter
            jnz label       // If Not Zero Jump Back To Label
    }
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}

