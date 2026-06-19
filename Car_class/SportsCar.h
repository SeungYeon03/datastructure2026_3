#pragma once
#include "Car.h"

class SportsCar : public Car {
public:
    bool turbo;

    void setTurbo(bool t) {
        turbo = t;
    }

    void speedUp() {
        if (turbo)
            speed += 20;
        else
            Car::speedUp();
    }
};
