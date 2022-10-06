#define GLFW_INCLUDE_NONE

#include <stdbool.h>
#include "test_counter.h"
#include "../src//gui.h"


#include <GLFW/glfw3.h>
#include <playground.h>
#include <stdio.h>

bool init = false;
Counter candyCounter = {0};
Counter lollipopCounter = {0};

void t_counter_update(Counter* candy, float frameTime)
{
    candy->timer -= frameTime;
    if(candy->timer <= 0)
    {
        candy->value++;
        candy->timer = 1.f / candy->freq;
    }
}

 
void test_counter_update(void)
{
    if (init == false) // Init test counter the first time
    {
        init = true;
        candyCounter.freq = 4.f; // candies per seconds
        candyCounter.value = 0;
        candyCounter.timer = 1.f / candyCounter.freq;
 
        lollipopCounter.freq = 0.5f;
        lollipopCounter.value = 0;
        lollipopCounter.timer = 1.f / lollipopCounter.freq;
    }
 
    float frameTime = pg_io_get_frame_time();
    t_counter_update(&candyCounter, frameTime);
    t_counter_update(&lollipopCounter, frameTime);
 
    if (im_button(1, 4, "Reset candies"))
        candyCounter.value = 0;
    if (im_button(1, 6, "Reset lollipops"))
        lollipopCounter.value = 0;
 
    im_print(1, 1 , "You have %d cand%s", candyCounter.value, (candyCounter.value == 1) ? "y" : "ies");
    im_print(1, 2, "You have %d lollipop%s", lollipopCounter.value,(lollipopCounter.value == 1) ? "s" : "");
}
