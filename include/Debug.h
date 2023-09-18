#pragma once

#include <GL/glew.h>
#include <iostream>
#include <stdint.h>
#include <assert.h>

#define ASSERT(x) if (!(x)) assert(false)
#define INT2VOIDP(i) (void*)(uintptr_t)(i)


void  GLClearError();
bool  GLCheckError();

#ifdef DEBUG
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLCheckError())
#else
#define GLCall(x) x
#endif
