#pragma once
#include <cstdio>
#include <cstring>

class Car {
protected:
    int speed;
    char name[40];

public:
    int gear;

    Car() {
        speed = 0;
        gear = 0;
        strcpy_s(name, "NoName");
    }

    Car(int s, const char* n, int g) : speed(s), gear(g) {
        strcpy_s(name, n);
    }

    void changeGear(int g = 4) {
        gear = g;
    }

    void speedUp() {
        speed += 5;
    }

    void display() {
        printf("[%s] Gear=%d Speed=%d\n", name, gear, speed);
    }
};
