#include "utils.h"
#include <stdlib.h>
#include <math.h>

unsigned int random_seed(){ 
    time_t current_time;
    return (unsigned int) time(&current_time);
}

float random_f(){
    unsigned int seed = random_seed();
    return fabs(((float)rand_r(&seed))/(float)__INT32_MAX__);
}

