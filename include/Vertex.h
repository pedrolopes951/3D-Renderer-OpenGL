#pragma once

struct Vertex {
    float x, y, z;

    Vertex(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z) {}
};



enum class GLType
{
    FLOAT,
    UNSIGNED_INT,
    UNSIGNED_BYTE
};