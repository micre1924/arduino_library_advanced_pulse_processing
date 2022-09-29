#include <Arduino.h>
#include "advanced_pulse_processing.h"

namespace mrc{

    void nullCallback(pulseArgs) {};

    advanced_pulse::advanced_pulse(uint16_t debounceTime, bool isMicro, bool *watchVariable){
        this->data.watchVariable = watchVariable;
        this->debounceTime = debounceTime;
        this->isMicro = isMicro;
        //this->onHigh = onHigh;
        //this->onLow = onLow;
        //this->onChange = onChange;
    }

    //poll from watchVariable
    void advanced_pulse::poll(){
        advanced_pulse::poll(*advanced_pulse::data.watchVariable);
    }

    //poll from Input
    void advanced_pulse::poll(bool input){
        unsigned long curTime = isMicro ? micros() : millis();
        data.pulseIn = false;
        data.pulseOut = false;
        if(input){
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