//
//  Exceptions.cpp
//  rpi_slam
//
//  Created by Andrew Schmitt on 10/1/16.
//  Copyright © 2016 Andrew Schmitt. All rights reserved.
//

#include "Exceptions.hpp"

setupException::setupException(const char *reason) : reason(reason) {};
const char *setupException::what() const throw() { return reason; };