#pragma once

#define init_pasta(type) \
    \
    typedef struct __element__##type { \
	type *sauce; \
	struct __element__##type *next; \
    } __element__##type; \
    \
    typedef struct __pasta__##type { \
	__element__##type* first; \
	int count; \
    } __pasta__##type; \
    \
    __pasta__##type new_pasta_##type() { \
	return (__pasta__##type) {.first = NULL, .count = false}; \
    } \
    \
    __element__##type* new_element_##type(type* data) { \
	__element__##type* p = (__element__##type*)malloc(sizeof(__element__##type)); \
	p->sauce = data; \
	return p; \
    } \
    \
    void add_element_##type##_after(__element__##type *after, __element__##type *element){ \
	element->next = after->next; \
	after->next = element; \
    } \
    \
    void remove_element_##type_after(__element__##type *element) { \
	if(element->next == NULL) return; \
	__element__##type* rossz = element->next; \
	element->next = element->next->next; \
	free(rossz->sauce); \
	free(rossz); \
    } \
    
