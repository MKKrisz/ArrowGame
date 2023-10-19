#include <math.h>

#include "../../debugmalloc.h"
#include "vector.h"

#define PI 3.1415926f

vec2 vec2_Zero() {
    return (vec2){0, 0};
}

vec2 vec2_Ones() {
    return (vec2){1, 1};
}

vec2 vec2_Make(float x, float y){
    return (vec2){x, y};
}

//theta because I like imaginary math
vec2 vec2_MakeAM(float theta, float magnitude){
    theta = fmodf(theta, 2*PI);
    return (vec2){cosf(theta) * magnitude, sinf(theta) * magnitude};
}

float vec2_get_Length(vec2* v){
    return sqrtf((v->x * v->x) + (v->y * v->y));
}

void vec2_set_Length(vec2* v, float len){
    float c_len = vec2_get_Length(v);
    if(c_len == 0) {
	v->x = len;
	v->y = 0;
	return;
    }
    v->x *= len/c_len;
    v->y *= len/c_len;
}

float vec2_get_Angle(vec2* v){
    return atan2f(v->y, v->x);
}

void vec2_set_Angle(vec2* v, float theta){
    theta = fmodf(theta, 2.0f*PI);
    float len = vec2_get_Length(v);
    float c_ang = vec2_get_Angle(v);
    v->x = cosf(theta - c_ang) * len;
    v->y = sinf(theta - c_ang) * len;
}

vec2 vec2_Normalize(vec2* v){
    float l = vec2_get_Length(v);
    return (vec2){v->x/l, v->y/l};
}

vec2 vec2_Add(vec2* a, vec2* b){
    return (vec2){a->x + b->x, a->y + b->y};
}
vec2 vec2_AddV(vec2 a, vec2 b){
    return (vec2){a.x + b.x, a.y + b.y};   
}

vec2 vec2_Neg(vec2* a){
    return (vec2){-a->x, -a->y};
}
vec2 vec2_NegV(vec2 a){
    return (vec2){-a.x, -a.y};
}

vec2 vec2_Mulf(vec2* a, float m){
    return (vec2){a->x * m, a->y * m};
}
vec2 vec2_MulfV(vec2 a, float m){
    return (vec2){a.x * m, a.y * m};
}

/* Remarks: this works like complex multiplication
 * @aka: rotating and scaling
 */
vec2 vec2_Mul(vec2* a, vec2* b){
    return (vec2){(a->x * b->x) - (a->y * b->y), (a->x * b->y) + (a->y*b->x)};
}

vec2 vec2_MulV(vec2 a, vec2 b){
   return (vec2){(a.x * b.x) - (a.y * b.y), (a.x * b.y) + (a.y*b.x)};
}

float vec2_Dot(vec2* a, vec2* b){
    return (a->x * b->x) + (a->y * b->y);
}

float vec2_DotV(vec2 a, vec2 b){
    return (a.x * b.x) + (a.y * b.y);   
}



