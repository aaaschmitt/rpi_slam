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
#endif /* UltraSensor_h */

// Theta is the angle we are facing
// Distance was our observed distance to an object
// in centimeters
struct SensorData {
    int theta;
    int distance;
};

// Collects data from a Serial interface in the form
// of point pairs (angle, distance)
class UltraSensor {
public:
    UltraSensor(char *iname, ConcurrentQueue<SensorData> *Q);
    
    // start collecting data, spawns a new thread
    void start();
	// baud rate for the serial port
    static const int DEFAULT_BAUD = 9600;
    
private:
    // We add values to the end of this Queue
    ConcurrentQueue<SensorData> *Q;
    // Name of the serial interface to collect data from
    char *iname;
    // returns the fd on the serial port or -1 on error
    int setup();
    int serialPort;
    // Handle transferring of receiving data, parsing it, and
    // passing to the Queue to be inferred upon
    char *readSerial();
    SensorData *parseData(char *data);
    void sendToQueue(SensorData *);
    // A locked method that tells the thread whether it should continue running
    bool isRunning();
};