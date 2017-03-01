//
//  Exceptions.hpp
//  rpi_slam
//
//  Created by Andrew Schmitt on 10/1/16.
//  Copyright © 2016 Andrew Schmitt. All rights reserved.
//

#ifndef Exceptions_h
#define Exceptions_h
#include <exception>
using std::exception;
#endif /* Exceptions_h */

// Obvious, but this is thrown if an exception happens during setup.
// This probably means we need to kill the application
class setupException: public exception {
public:
    setupException(const char *reason);
    virtual const char *what() const throw();
private:
    const char *reason;
};