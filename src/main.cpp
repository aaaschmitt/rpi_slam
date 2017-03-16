//
//  main.cpp
//  rpi_slam
//
//  Created by Andrew Schmitt on 9/25/16.
//  Copyright © 2016 Andrew Schmitt. All rights reserved.
//

#include "main.hpp"
#include "UltraSensor.hpp"
#include <iostream>
#include <string>
#include <stdio.h>
#include <sstream>
#include <cstdlib>
#include <wiringPi.h>
#include <wiringPiI2C.h>

using std::cout;

int main (int argc, char *argv[]) {
    int fd = wiringPiI2CSetup(0x04);
    for (int i = 0; i < 5; i++) {
        wiringPiI2CWrite(fd, i);
    }
}
