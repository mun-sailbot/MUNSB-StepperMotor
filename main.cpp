//
//  main.cpp
//  Motor
//
//  Created by Bryan Melanson on 2018-03-11.
//  Copyright © 2018 Bryan Melanson. All rights reserved.
//

#include <iostream>
#include "Motor.hpp"

int main(int argc, const char * argv[]) {
    Motor m1 = Motor(5, 5, 1, 5);
    m1.rotate(5);
    m1.setStartPosition();
    std::cout << "Hello, World!\n";
    return 0;
}
