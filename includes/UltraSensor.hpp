//
//  UltraSensor.hpp
//  rpi_slam
//
//  Created by Andrew Schmitt on 9/28/16.
//  Copyright © 2016 Andrew Schmitt. All rights reserved.
//

#ifndef UltraSensor_h
#define UltraSensor_h
#include "ConcurrentQueue.hpp"
#include <time.h>
#endif /* UltraSensor_h */

// Theta is the angle we are facing
// Distance was our observed distance to an object
// in centimeters
struct SensorData {
    int theta;
    int distance;
};

// Collects data from the ultra sonic sensor in the form
// of point pairs (angle, distance)
class UltraSensor {
public:
    UltraSensor(int triggerPin, int echoPin, ConcurrentQueue<SensorData> buffer);
    
    // start collecting data, spawns a new thread
    void start();
    
private:
    // We add values to the end of this Queue
    ConcurrentQueue<SensorData> buf;
    // The pin that will trigger the ultrasound pulse
    static int tpin;
    // The pin that we will receive the pulse on
    static int epin;
    // The angle that we are currently facing
    int theta;
    // This is so that our static callbacks can access the currently running instance
    static UltraSensor *INSTANCE;
    // These functions mimick the arduino pulseIn library function
    // Although ONLY FOR PULSE HIGH
    // It waits for the echo pin to go high, starts timing
    // then when the pin goes low it stops timing and
    // returns the amount of time that elasped (pulse duration)
    // Note: wiringPi only supports interrupt based events
    // so we need to use callbacks here.
    // The functions are called in the following order:
    void obtainDistanceData();
    static void receivePulseHigh();
    static void receivePulseLow();
    static int calculateDistance();
    static void writeDataToBuffer();
    // The time we started waiting for a pulse
    static time_t startTime;
};