#include <Arduino.h>
#include "advanced_pulse_processing.h"

namespace mrc{

    void nullCallback(pulseArgs) {};

    advanced_pulse::advanced_pulse(bool *watchVariable, uint16_t debounceTime, bool isMicro/*, void(*onHigh)(pulseArgs) = nullCallback, void(*onLow)(pulseArgs) = nullCallback, void(*onChange)(pulseArgs) = nullCallback*/){
        this->data.watchVariable = watchVariable;
        this->debounceTime = debounceTime;
        this->isMicro = isMicro;
        //this->onHigh = onHigh;
        //this->onLow = onLow;
        //this->onChange = onChange;
    }


    void advanced_pulse::poll(){
        unsigned long curTime = isMicro ? micros() : millis();
        data.pulseIn = false;
        data.pulseOut = false;
        if(*data.watchVariable){
            if((data.outTimestamp + debounceTime) < curTime) data.triggerOut = false;
            if(!data.triggerIn){
                data.triggerIn = true;
                data.pulseIn = true;
                data.inTimestamp = curTime;
                data.lowTime = data.inTimestamp - data.outTimestamp;
                onHigh(data);
                onChange(data);
            }
        } else {
            if((data.inTimestamp + debounceTime) < curTime) data.triggerIn = false;
            if(!data.triggerOut){
                data.triggerOut = true;
                data.pulseOut = true;
                data.outTimestamp = curTime;
                data.highTime = data.outTimestamp - data.inTimestamp;
                onLow(data);
                onChange(data);
            }
        }
    }
}