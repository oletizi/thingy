#include "loop.h"
void theloop::setup() {
    pinMode(MY_LED, OUTPUT);
}

void theloop::loop() {
    digitalWrite(MY_LED, HIGH);
    delay(1000);
    digitalWrite(MY_LED, LOW);
    delay(1000);
}