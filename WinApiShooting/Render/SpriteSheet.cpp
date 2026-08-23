#include "SpriteSheet.h"

bool SpriteSheet::loadFolder(const std::wstring& folder, const std::wstring& prefix,
                             int start, int end, int digits)
{
    frames.clear();
    frames.reserve(end - start + 1);

    for (int i = start; i <= end; ++i)
    {
        wchar_t num[16]{};
        if (digits == 2)
        {
            swprintf_s(num, L"%02d", i);
        }
        else
        {
            swprintf_s(num, L"%d", i);
        }
        std::wstring path = folder + L"\\" + prefix + num + L".png";
        Sprite spr;
        if (!spr.load(path))
        {
            frames.clear();
            return false;
        }
        frames.push_back(std::move(spr));
    }
    return !frames.empty();
}

bool SpriteSheet::loadList(const std::vector<std::wstring>& paths)
{
    frames.clear();
    frames.reserve(paths.size());
    for (const std::wstring& path : paths)
    {
        Sprite spr;
        if (!spr.load(path))
        {
            frames.clear();
            return false;
        }
        frames.push_back(std::move(spr));
    }
    return !frames.empty();
}

const Sprite& SpriteSheet::at(int index) const
{
    if (frames.empty())
    {
        // 빈 시트용 더미. image == nullptr 이라 GdiplusShutdown 이후 파괴도 안전.
        static Sprite fallback;
        return fallback;
    }
    const int i = clampInt(index, 0, static_cast<int>(frames.size()) - 1);
    return frames[i];
}
