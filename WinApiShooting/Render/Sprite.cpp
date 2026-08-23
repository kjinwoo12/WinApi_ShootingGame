#include "Sprite.h"

Sprite::~Sprite()
{
    if (image != nullptr)
    {
        delete image;
        image = nullptr;
    }
}

Sprite::Sprite(Sprite&& other) noexcept
    : image(other.image), imageWidth(other.imageWidth), imageHeight(other.imageHeight)
{
    other.image = nullptr;
    other.imageWidth = 0;
    other.imageHeight = 0;
}

Sprite& Sprite::operator=(Sprite&& other) noexcept
{
    if (this != &other)
    {
        delete image;
        image = other.image;
        imageWidth = other.imageWidth;
        imageHeight = other.imageHeight;
        other.image = nullptr;
        other.imageWidth = 0;
        other.imageHeight = 0;
    }
    return *this;
}

bool Sprite::load(const std::wstring& path)
{
    delete image;
    image = nullptr;
    imageWidth = 0;
    imageHeight = 0;

    Gdiplus::Bitmap* bmp = Gdiplus::Bitmap::FromFile(path.c_str(), FALSE);
    if (!bmp || bmp->GetLastStatus() != Gdiplus::Ok)
    {
        delete bmp;
        return false;
    }

    image = bmp;
    imageWidth = static_cast<int>(bmp->GetWidth());
    imageHeight = static_cast<int>(bmp->GetHeight());
    return true;
}

void Sprite::draw(Gdiplus::Graphics& g, float x, float y, float scale,
                  float alpha, float rotationDeg) const
{
    if (!image)
        return;

    const float w = imageWidth * scale;
    const float h = imageHeight * scale;
    drawCentered(g, x + w * 0.5f, y + h * 0.5f, scale, alpha, rotationDeg);
}

void Sprite::drawCentered(Gdiplus::Graphics& g, float cx, float cy, float scale,
                          float alpha, float rotationDeg) const
{
    if (!image)
        return;

    const float w = imageWidth * scale;
    const float h = imageHeight * scale;

    Gdiplus::GraphicsState state = g.Save();
    g.TranslateTransform(cx, cy);
    if (std::fabs(rotationDeg) > 0.01f)
    {
        g.RotateTransform(rotationDeg);
    }

    if (alpha < 0.999f)
    {
        Gdiplus::ColorMatrix matrix = {
            1, 0, 0, 0, 0,
            0, 1, 0, 0, 0,
            0, 0, 1, 0, 0,
            0, 0, 0, clampFloat(alpha, 0.f, 1.f), 0,
            0, 0, 0, 0, 1};
        Gdiplus::ImageAttributes attrs;
        attrs.SetColorMatrix(&matrix, Gdiplus::ColorMatrixFlagsDefault,
                             Gdiplus::ColorAdjustTypeBitmap);
        const Gdiplus::RectF dest(-w * 0.5f, -h * 0.5f, w, h);
        g.DrawImage(image, dest, 0, 0, static_cast<Gdiplus::REAL>(imageWidth),
                    static_cast<Gdiplus::REAL>(imageHeight), Gdiplus::UnitPixel, &attrs);
    }
    else
    {
        g.DrawImage(image, -w * 0.5f, -h * 0.5f, w, h);
    }

    g.Restore(state);
}
