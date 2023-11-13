#include "lerp.h"
#include "../../debugmalloc.h"


float Lerp(float a, float b, float t){
    return (1-t)*a + t*b;
}
