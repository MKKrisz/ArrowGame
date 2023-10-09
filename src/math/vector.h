#pragma once

#include <SDL2/SDL.h>

// Yes, I am using glm naming scheme, because I am a madlad and I want to cause havoc
typedef struct vector2 {
    float x, y;
} vec2;


vec2 vec2_Zero();
vec2 vce2_Ones();

/* Creates a 2 dimensional vector allocated on the stack
 * @param float x: x coordinate
 * @param float y: y coordinate
 */
vec2 vec2_Make(float x, float y);

vec2 vec2_MakeAM(float angle, float magnitude);

// Gets the length of the specified vector
float vec2_get_Length(vec2* v);

/* Sets the length of the vector to "len"
 * @Remarks: if the vector previously had a length of 0,
 *           the produced vector will look like (len, 0)
 */
void  vec2_set_Length(vec2* v, float len);



float vec2_get_Angle(vec2* v);
void  vec2_set_Angle(vec2* v, float theta);


vec2 vec2_Normalize(vec2* v);

vec2 vec2_Add(vec2* a, vec2* b);
vec2 vec2_AddV(vec2 a, vec2 b);

vec2 vec2_Neg(vec2* a);
vec2 vec2_NegV(vec2 a);

vec2 vec2_Mulf(vec2* a, float m);
vec2 vec2_MulfV(vec2 a, float m);

/* Remarks: this works like complex multiplication
 * @aka: rotating and scaling
 */
vec2 vec2_Mul(vec2* a, vec2* b);
vec2 vec2_MulV(vec2 a, vec2 b);

float vec2_Dot(vec2* a, vec2* b);
float vec2_DotV(vec2 a, vec2 b);
