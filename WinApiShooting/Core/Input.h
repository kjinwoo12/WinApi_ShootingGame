#pragma once
#include "Common.h"

struct InputState
{
    bool keys[256]{};

    void setKey(WPARAM key, bool down)
    {
        if (key < 256)
            keys[key] = down;
    }

    bool down(int key) const
    {
        return key >= 0 && key < 256 && keys[key];
    }

    bool moveUp() const
    {
        return down('W') || down('w') || down(VK_UP);
    }
    bool moveDown() const
    {
        return down('S') || down('s') || down(VK_DOWN);
    }
    bool moveLeft() const
    {
        return down('A') || down('a') || down(VK_LEFT);
    }
    bool moveRight() const
    {
        return down('D') || down('d') || down(VK_RIGHT);
    }
    bool focus() const
    {
        return down(VK_SHIFT);
    }
    bool fire() const
    {
        return down(VK_SPACE) || down('Z') || down('z');
    }
    bool confirm() const
    {
        return down(VK_RETURN) || down(VK_SPACE);
    }

    bool bombEdge = false;

    bool consumeBombEdge()
    {
        const bool pressed = bombEdge;
        bombEdge = false;
        return pressed;
    }
};
