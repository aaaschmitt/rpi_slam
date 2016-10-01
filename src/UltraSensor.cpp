//
//  UltraSensor.cpp
//  rpi_slam
//
//  Created by Andrew Schmitt on 9/28/16.
//  Copyright © 2016 Andrew Schmitt. All rights reserved.
//

#include "UltraSensor.hpp"
#include <wiringPi.h>

UltraSensor::UltraSensor(int triggerPin, int echoPin, ConcurrentQueue<SensorData> buffer) :
    buf(buffer),
    theta(0)
{
    UltraSensor::INSTANCE = this;
    UltraSensor::TPIN = triggerPin;
    UltraSensor::EPIN = echoPin;
    UltraSensor::startTime = time(NULL);
};

void UltraSensor::obtainDistanceData()
{
    digitalWrite(tpin, LOW);
    delayMicroseconds(2);
    digitalWrite(tpin, HIGH);
    delayMicroseconds(10);
    digitalWrite(tpin, LOW);
    wiringPiISR(epin, INT_EDGE_RISING, &this->receivePulseHigh);
}

void UltraSensor::receivePulseHigh()
{
    time(&UltraSensor::startTime);
    wiringPiISR(UltraSensor::epin, INT_EDGE_FALLING, &receivePulseLow);
}