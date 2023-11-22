#ifndef __TASK_DETECT_CAR_IN_WASHING_AREA__
#define __TASK_DETECT_CAR_IN_WASHING_AREA__

#include <Task.h>
#include <Components/Components.h>
#include <Sonar.h>
#include "CarInWashingAreaListener.h"


class DetectCarInWashingArea : public Task {
    private:
        Sonar* sonar;
        CarInWashingAreaListener* listener;
        bool isCarInWashingArea;
    public:
        DetectCarInWashingArea(Components* components, CarInWashingAreaListener* listener);
        void init(int period);
        void tick();
};

#endif