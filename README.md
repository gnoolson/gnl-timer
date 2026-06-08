# gnl-timer
## Simple timer for Arduino

A lightweight timer library for Arduino that allows you to execute tasks at fixed time intervals without using delay(). Timers can run once or repeatedly and can either be checked manually or execute a callback function automatically.

## API  
### Timer Initialization    
Initialize an existing timer  
`void gnl_timer_setup(gnl_timer_t* p_timer, uint32_t period, bool loop);`  

Allocate and initialize a new timer on the heap  
`gnl_timer_t* gnl_timer_new_and_setup(uint32_t period, bool loop);`  

### Timer Destruction  
Delete a timer allocated on the heap  
`void gnl_timer_delete(gnl_timer_t* p_timer);`

### Timer Execution  
Check whether the timer has elapsed. Returns true when the timer is ready to run    
`bool gnl_timer_check(gnl_timer_t* p_timer);`  

Check the timer and execute the specified callback function  when the timer has elapsed  
`void gnl_timer_check_and_execute(gnl_timer_t* p_timer, void (*p_func)(void* p_value), void* p_value);`

### Timer Control  
Start a stopped timer  
`void gnl_timer_start(gnl_timer_t* p_timer);`  

Stop the timer  
`void gnl_timer_stop(gnl_timer_t* p_timer);`  

Reset the timer countdown  
`void gnl_timer_reset(gnl_timer_t* p_timer);`  


### Example: Automatic Callback Execution  
```
extern "C" {
#include <gnl_timer.h>
}

gnl_timer_t *p_timer = NULL;

void print_function(int *p_value) {
    Serial.print("value = ");
    Serial.println(*p_value);
    (*p_value)++;
}

void setup() {
    Serial.begin(9600);
    p_timer = gnl_timer_new_and_setup(1000 /* period ms */, true /* loop */);
}

void loop() {
    static int some_value = 1;
    gnl_timer_check_and_execute(p_timer, &print_function, &some_value);
}
```


### Example: Manual Timer Check
```
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
    gnl_timer_setup(&timer, 1000 /* period ms */, true /* loop */);
}

void loop() {
    static int some_value = 1;

    if (gnl_timer_check(&timer)) {
        print_function(&some_value);
    }
}
```