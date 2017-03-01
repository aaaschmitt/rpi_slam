//
//  UltraSensor.cpp
//  rpi_slam
//
//  Created by Andrew Schmitt on 9/28/16.
//  Copyright © 2016 Andrew Schmitt. All rights reserved.
//

#include "UltraSensor.hpp"
#include "Exceptions.hpp"
#include <cstring>

UltraSensor::UltraSensor(char *iname, ConcurrentQueue<SensorData> *Q)
	: iname(iname)
	, Q(Q)
{};

int UltraSensor::setup() {
    wiringPiSetup();
    return serialOpen(iname, DEFAULT_BAUD);
}

void UltraSensor::start() {
    this->running = true;
    int fd = setup();
    if (!(fd > 0)) {
        char msg[100] = "Could not initialize serial port with iname: ";
        throw setupException(strcat(msg, iname));
    }
    this->serialPort = fd;
    
    // should spawn new thread here
    char *newData;
    SensorData *parsedData;
    while(isRunning()) {
        newData = readSerial();
        parsedData = parseData(newData);
        sendToQueue(parsedData);
    }
}
