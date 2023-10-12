#pragma once

struct Vertex2D {
    float x, y;

    Vertex2D(float _x, float _y)
        : x(_x), y(_y){}
};

struct Vertex3D {
    float x, y, z;

    Vertex3D(float _x, float _y, float _z)
        : x(_x), y(_y), z(_z) {}
};



enum class GLType
{
    FLOAT,
    UNSIGNED_INT,
    UNSIGNED_BYTE,
    VERTEX2D,
    VERTEX3D
};


