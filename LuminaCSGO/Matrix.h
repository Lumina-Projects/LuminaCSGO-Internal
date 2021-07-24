#pragma once
#include <Windows.h>
#include "Vector.h"

class Matrix3x4 {
    float mat[3][4];
public:
    constexpr auto operator[](int i) const noexcept { return mat[i]; }
};

struct Matrix4x4 {
    union {
        struct {
            float _11, _12, _13, _14;
            float _21, _22, _23, _24;
            float _31, _32, _33, _34;
            float _41, _42, _43, _44;

        };
        float m[4][4];
    };
};