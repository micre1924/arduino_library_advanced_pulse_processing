#include "Arduino.h"

namespace mrc{

    struct pulseArgs{
        bool            *watchVariable;
        //is true for one program cycle once the variable has been changed to high
        bool            pulseIn = false;
        //is true for one program cycle once the variable has been changed to low
        bool            pulseOut = false;
        //is true once the button has been pressed, till button is released
        bool            triggerIn = true;
        //is true once the button has been released, till button is pressed
        bool            triggerOut = true;
        //is the time the variable has been changed to high, till it was low
        unsigned long   highTime = 0;
        //is the time the variable has been changed to low, till it was high
        unsigned long   lowTime = 0;
        //is the raw timestamp when the varibale has been changed to high
        unsigned long   inTimestamp = 0;
        //is the raw timestamp when the varibale has been chanded to low
        unsigned long   outTimestamp = 0;
    };

    void nullCallback(pulseArgs);
    static bool nullWatchVariable;

    class advanced_pulse {
    public:
        pulseArgs data;
        bool isMicro;
        uint16_t debounceTime = 0;
        void(*onHigh)(pulseArgs) = nullCallback;
        void(*onLow)(pulseArgs) = nullCallback;
        void(*onChange)(pulseArgs) = nullCallback;

        /**
         * @param debounceTime the time to wait to accept new change of state
         * @param isMicro when true micros() is used as a time basis, millis() otherwise (from Arduino.h)
         * @param watchVariable input variable to watch
         * */
        advanced_pulse(uint16_t debounceTime, bool isMicro, bool *watchVariable = &nullWatchVariable);

        void poll();
        void poll(bool input);
    };
}