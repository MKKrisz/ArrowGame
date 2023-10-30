#pragma once

#include <SDL2/SDL.h>

/* This is a basic implementation of a 2 dimensional vector struct.
 * The struct is defined to have 2 real values as its fields
 * Most functions related to this struct start with vec2_
 * The funstions that end in "V" operate with values as opposed to references (pointers)
 * The struct can be directly casted into an "SDL_FPoint", and vice versa.
 * This struct may be referred to as just "vector" in the documentation
 */
typedef struct vector2 {
    float x, y;
} vec2;

/* Returns a vector with every field set to 0
 */
vec2 vec2_Zero();

/* Returns a vector with every field set to 1
 */
vec2 vce2_Ones();

// If you need heap-allocated vec2-s, you must create them explicitly using malloc
// as this class will not contain support for that

/* Creates a vector allocated on the stack from coordinates
 * float x: x coordinate
 * float y: y coordinate
 */
vec2 vec2_Make(float x, float y);

/* Creates a vector allocated on the stack from trigonometric representation
 * float angle: the angle of the vector
 * float magnitude: the magnitude of the vector
 */
vec2 vec2_MakeAM(float angle, float magnitude);

// Gets the length of the specified vector
float vec2_get_Length(vec2* v);

/* Sets the length of the vector to "len"
 * @Remarks: if the vector previously had a length of 0,
 *           the produced vector will look like (len, 0)
 */
void  vec2_set_Length(vec2* v, float len);


/*
 */
float vec2_get_Angle(vec2* v);
void  vec2_set_Angle(vec2* v, float theta);


vec2 vec2_Normalize(vec2* v);

vec2 vec2_Add(vec2* a, vec2* b);
vec2 vec2_AddV(vec2 a, vec2 b);

vec2 vec2_Neg(vec2* a);
vec2 vec2_NegV(vec2 a);

vec2 vec2_Sub(vec2* a, vec2* b);
vec2 vec2_SubV(vec2 a, vec2 b);

vec2 vec2_Mulf(vec2* a, float m);
vec2 vec2_MulfV(vec2 a, float m);

/* Remarks: this works like complex multiplication
 * @aka: rotating and scaling
 */
vec2 vec2_Mul(vec2* a, vec2* b);
vec2 vec2_MulV(vec2 a, vec2 b);

float vec2_Dot(vec2* a, vec2* b);
float vec2_DotV(vec2 a, vec2 b);
