#pragma once
#include <Windows.h>
#include "Matrix.h"

class Vector {
public:
    float x, y, z;
    Vector() = default;
    constexpr Vector(float x, float y, float z) noexcept : x{ x }, y{ y }, z{ z } {}
    constexpr auto NotNull() const noexcept { return x || y || z; }
    friend constexpr auto operator==(const Vector & a, const Vector & b) noexcept { return a.x == b.x && a.y == b.y && a.z == b.z; }
    friend constexpr auto operator!=(const Vector & a, const Vector & b) noexcept { return !(a == b); }
    constexpr Vector& operator=(const float array[3]) noexcept {
        x = array[0];
        y = array[1];
        z = array[2];
        return *this;
    }
    constexpr Vector& operator+=(const Vector & v) noexcept {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }
    constexpr Vector& operator+=(float f) noexcept {
        x += f;
        y += f;
        z += f;
        return *this;
    }
    constexpr Vector& operator-=(const Vector & v) noexcept {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }
    constexpr Vector& operator-=(float f) noexcept {
        x -= f;
        y -= f;
        z -= f;
        return *this;
    }
    friend constexpr auto operator-(const Vector & a, const Vector & b) noexcept { return Vector{ a.x - b.x, a.y - b.y, a.z - b.z }; }
    friend constexpr auto operator+(const Vector & a, const Vector & b) noexcept { return Vector{ a.x + b.x, a.y + b.y, a.z + b.z }; }
    friend constexpr auto operator*(const Vector & a, const Vector & b) noexcept { return Vector{ a.x * b.x, a.y * b.y, a.z * b.z }; }
    constexpr Vector& operator/=(float div) noexcept {
        x /= div;
        y /= div;
        z /= div;
        return *this;
    }
    constexpr auto operator*(float mul) const noexcept { return Vector{ x * mul, y * mul, z * mul }; }
    constexpr auto operator-(float sub) const noexcept { return Vector{ x - sub, y - sub, z - sub }; }
    constexpr auto operator+(float add) const noexcept { return Vector{ x + add, y + add, z + add }; }
    auto Lenght() const noexcept { return sqrt(x * x + y * y + z * z); }
    auto DistanceTo(const Vector& v) const noexcept{ return (*this - v).Lenght(); }
    constexpr auto DotProduct(const Vector& v) const noexcept { return x * v.x + y * v.y + z * v.z; }
    constexpr auto Transform(const Matrix3x4& mat) const noexcept;
};

constexpr auto Vector::Transform(const Matrix3x4& mat) const noexcept {
    return Vector{
        DotProduct({ mat[0][0], mat[0][1], mat[0][2] }) + mat[0][3],
        DotProduct({ mat[1][0], mat[1][1], mat[1][2] }) + mat[1][3],
        DotProduct({ mat[2][0], mat[2][1], mat[2][2] }) + mat[2][3] 
    };
}