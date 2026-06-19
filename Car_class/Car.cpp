#include "SportsCar.h"

int main() {
    SportsCar car;

    car = SportsCar(); 
    car.changeGear(3);
    car.setTurbo(true);

    car.speedUp();
    car.speedUp();

    car.display();

    return 0;
}