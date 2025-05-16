#include "utils.h"
#include <assert.h>
#include <stdio.h>

int main(){
    float number = random_f();
    assert(number <= 1.0f);
    printf("random number test passed\n");
}