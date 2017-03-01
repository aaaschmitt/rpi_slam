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

using std::cout;

int main (int argc, char *argv[]) {
    if (argc > 1) {
        std::stringstream convert(argv[1]);
        if (!(convert >> LOG_LEVEL))
            cout << "ERROR: invalid log level specified, using default";
    }
    
    if (!setup()) {
        cout << "ERROR: could not complete setup";
        exit(1);
    }
    return run();
}

int setup() {
    return setupPins();
}

int setupPins() {
    wiringPiSetup();
    return 0;
}

int run() {
    
}
