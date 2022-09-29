#include "Arduino.h"
#include "advanced_pulse_processing.h"

#define TEST_BTN 12

uint8_t led_pins[10] = { 2,3,4,5,6,7,8,9,10,11 };
uint8_t test_value = 5;
bool test_variable = false;

char serial_buffer[100];

void onHigh_test(mrc::pulseArgs data){
    if(test_value < 10) test_value++; 
    else test_value = 0;
    sprintf(serial_buffer, "HIGH: %d, LOW: %d", (int)data.highTime, (int)data.lowTime);
    Serial.println(serial_buffer);
}

mrc::advanced_pulse pulse(&test_variable, 10, false);

void setup(){

    pulse.onLow = onHigh_test;

    Serial.begin(9600);
    Serial.println("Serial begun...");

    for(uint8_t p = 0; p < 10; p++){
        pinMode(led_pins[p], OUTPUT);
    }

}

void loop(){
    //test LED driver
    for(uint8_t l = 0; l < 10; l++){
        digitalWrite(led_pins[l], LOW);
        if(l < test_value) digitalWrite(led_pins[l], HIGH);
    }

    test_variable = digitalRead(TEST_BTN);
    //advanced_pulse driver polling
    pulse.poll();
}