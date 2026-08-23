#pragma once

#define NOMINMAX
#include <windows.h>
#include <windowsx.h>
#include <objidl.h>
#include <gdiplus.h>

#include <algorithm>
#include <cmath>
#include <cstdint>
#include <random>
#include <string>
#include <vector>

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")

inline constexpr int ScreenWidth = 700;
inline constexpr int ScreenHeight = 800;
inline constexpr float Pi = 3.14159265f;

struct Vec2
{
    float x = 0.f;
    float y = 0.f;

    Vec2() = default;
    Vec2(float x, float y)
        : x(x), y(y) {}

    Vec2 operator+(const Vec2& o) const
    {
        return {x + o.x, y + o.y};
    }
    Vec2 operator-(const Vec2& o) const
    {
        return {x - o.x, y - o.y};
    }
    Vec2 operator*(float s) const
    {
        return {x * s, y * s};
    }
    Vec2& operator+=(const Vec2& o)
    {
        x += o.x;
        y += o.y;
        return *this;
    }
};

inline float length(const Vec2& v)
{
    return std::sqrt(v.x * v.x + v.y * v.y);
}

inline Vec2 normalize(const Vec2& v)
{
    const float len = length(v);
    if (len < 0.0001f)
        return {0.f, 0.f};
    return {v.x / len, v.y / len};
}

inline float clampFloat(float v, float lo, float hi)
{
    return (std::max)(lo, (std::min)(hi, v));
}

inline int clampInt(int v, int lo, int hi)
{
    return (std::max)(lo, (std::min)(hi, v));
}

inline float lerp(float a, float b, float t)
{
    return a + (b - a) * t;
}

inline bool rectsOverlap(float ax, float ay, float aw, float ah,
                         float bx, float by, float bw, float bh)
{
    return ax < bx + bw && ax + aw > bx && ay < by + bh && ay + ah > by;
}
