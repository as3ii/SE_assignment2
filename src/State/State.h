#ifndef __LIGHT__
#define __LIGHT__

class State {
    public:
        StateName name;
        /*
        Check if the current state activities are finished,
        and the state can be changed
        */
        virtual bool goNext(); 
};

#endif