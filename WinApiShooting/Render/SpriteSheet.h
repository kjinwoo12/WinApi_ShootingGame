#pragma once
#include "Sprite.h"
#include <vector>

class SpriteSheet
{
public:
    bool loadFolder(const std::wstring& folder, const std::wstring& prefix,
                    int start, int end, int digits = 2);
    bool loadList(const std::vector<std::wstring>& paths);

    const Sprite& at(int index) const;
    int count() const
    {
        return static_cast<int>(frames.size());
    }
    bool empty() const
    {
        return frames.empty();
    }

private:
    std::vector<Sprite> frames;
};
