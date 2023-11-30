#include <Arduino.h>
#include <Scheduler.h>
#include <Config.h>
#include "StateExitingWashingArea.h"
#include "Components/Components.h"
#include "Tasks/DetectCarExitingWashingArea/DetectCarExitWashingArea.h"

StateName StateExitingWashingArea::name() {
    return StateName::ReadyToWash;
}

StateExitingWashingArea::StateExitingWashingArea(int carWashed, Components* components, Scheduler* scheduler): State(carWashed) {
    this->components = components;
    this->scheduler = scheduler;

    // print to the screen
    this->components->userLcd->clear();
    this->components->userLcd->setCursor(0, 0);
    this->components->userLcd->print("Washing complete");
    this->components->userLcd->setCursor(0, 1);
    this->components->userLcd->print("you can leave");
    
    // switch on L3
    this->components->l3->switchOn();

    // open gate
    this->components->gate->setPosition(90);

    // distance < MAXDIST for N4 secs
    Task* carExited = new DetectCarExitWashingArea(components->carDistanceDetector, this);
    carExited->init(100);
    this->scheduler->addTask(carExited);
}

bool StateExitingWashingArea::goNext() {
    return this->isCarExited;
}

void StateExitingWashingArea::carExitedWashingArea(bool isCarExited) {
    if(isCarExited) {
        if(this->time == 0) {
            time = millis();
        } else if((millis() - this->time) > (N4 * 1000)) {
            this->isCarExited = true;
        }
    } else {
        // reset if previously set
        this->isCarExited = false;
        this->time = 0;
    }
}

StateExitingWashingArea::~StateExitingWashingArea() {
    this->scheduler->removeLastTask(); // remove distance detector
    this->components->l3->switchOff();
    this->components->gate->setPosition(0);
}
