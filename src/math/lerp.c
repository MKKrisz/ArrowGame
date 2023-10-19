#include "lerp.h"
#include "../../debugmalloc.h"


float Lerp(float a, float b, float t){
    return (b-a)*t + a;
}
