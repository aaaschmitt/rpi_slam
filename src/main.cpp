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

using std::cout;

// The trig pin
const int TRIG_PIN = 100;
const int ECHO_PIN = 100;

// Log everything
const int LOG_LEVEL_DEFAULT = 0;
// Specify how much to log
int LOG_LEVEL = LOG_LEVEL_DEFAULT;

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
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    return 0;
}

int run() {
    while(1) {
        int distance = calculateDistance();
        cout << "Got distance: " << distance;
        delay(1000);
    };
    return 1;
}
