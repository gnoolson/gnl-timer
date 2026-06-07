extern "C" {
#include <gnl_timer.h>
}

gnl_timer_t timer;

void print_function(int* p_value) {
    Serial.print("value = ");
    Serial.println(*p_value);
    (*p_value)++;
}

void setup() {
    Serial.begin(9600);
    gnl_timer_setup(&timer, 1000 /*period ms*/, true /*loop*/);
}

void loop() {
    static int some_value = 1;
    if (gnl_timer_check(&timer)) {
        print_function(&some_value);
    }
}