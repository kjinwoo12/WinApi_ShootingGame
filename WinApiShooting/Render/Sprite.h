#pragma once
#include "Common.h"
#include "GdiplusInclude.h"

class Sprite
{
public:
    Sprite() = default;
    ~Sprite();

    Sprite(const Sprite&) = delete;
    Sprite& operator=(const Sprite&) = delete;
    Sprite(Sprite&& other) noexcept;
    Sprite& operator=(Sprite&& other) noexcept;

    bool load(const std::wstring& path);
    void draw(Gdiplus::Graphics& g, float x, float y, float scale = 1.f,
              float alpha = 1.f, float rotationDeg = 0.f) const;
    void drawCentered(Gdiplus::Graphics& g, float cx, float cy, float scale = 1.f,
                      float alpha = 1.f, float rotationDeg = 0.f) const;

    int width() const
    {
        return imageWidth;
    }
    int height() const
    {
        return imageHeight;
    }
    bool valid() const
    {
        return image != nullptr;
    }

private:
    Gdiplus::Image* image = nullptr;
    int imageWidth = 0;
    int imageHeight = 0;
};
