#include "lerp.h"

float Lerp(float a, float b, float t){
    return (b-a)*t + a;
}
