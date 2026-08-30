#pragma once
#include <cstdint>

struct Rgba8
{
    uint8_t r = 255;
    uint8_t g = 255;
    uint8_t b = 255;
    uint8_t a = 255;
};

inline constexpr Rgba8 rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255)
{
    return {r, g, b, a};
}
