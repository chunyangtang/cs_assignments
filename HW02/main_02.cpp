//
// Created by TCY on 2023/2/27.
//

#include <iostream>
#include <random>
#include <bitset>
#include "WindowStyle.h"

using namespace std;


int main() {
    // get a random style
    const unsigned char styles[] = {0b11111011, 0b01000010, 0b11111010, 0b00000000, 0b00001000, 0b00001011  };
    std::mt19937 rng;
    rng.seed(1);
    std::uniform_int_distribution<> distrib(0, 5);

    int rand_num = distrib(rng);

    WindowStyle style(styles[rand_num]);

    // print the size of the union to display memory usage
    cout << "sizeof(Status): " << sizeof(Status) << endl;

    // print the style chosen using random number
    cout << bitset<8>(styles[rand_num]) << endl;

    // print the style retrieved from the class (should be identical to the above)
    cout << bitset<8>((int)style.GetStatus().Char_Status) << endl;

    // print the status of each element
    cout << "Icon: " << style.GetStatus().Bi_Status.Icon << endl;
    cout << "Caption: " << style.GetStatus().Bi_Status.Caption << endl;
    cout << "Maximize: " << style.GetStatus().Bi_Status.Maximize << endl;
    cout << "Minimize: " << style.GetStatus().Bi_Status.Minimize << endl;
    cout << "Close: " << style.GetStatus().Bi_Status.Close << endl;
    cout << "Edge: " << style.GetStatus().Bi_Status.Edge << endl;
    cout << "Resizer: " << style.GetStatus().Bi_Status.Resizer << endl;

    return 0;
}