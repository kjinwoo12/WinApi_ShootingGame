#include "UiSprites.h"

namespace
{

std::wstring joinPath(const std::wstring& a, const std::wstring& b)
{
    if (a.empty())
        return b;
    if (a.back() == L'\\' || a.back() == L'/')
        return a + b;
    return a + L"\\" + b;
}

} // namespace

bool UiSprites::load(const std::wstring& spaceRageRoot)
{
    std::wstring assetsDir = spaceRageRoot;
    const size_t slash = assetsDir.find_last_of(L"\\/");
    if (slash != std::wstring::npos)
        assetsDir.resize(slash);

    const std::wstring candidates[] = {
        joinPath(assetsDir, L"WenrexaUi"),
        joinPath(assetsDir, L"WenrexaAssetsUI_SciFI\\PNG"),
    };

    std::wstring uiRoot;
    for (const std::wstring& candidate : candidates)
    {
        const std::wstring probe = joinPath(candidate, L"MainPanel03.png");
        const DWORD attr = GetFileAttributesW(probe.c_str());
        if (attr != INVALID_FILE_ATTRIBUTES && !(attr & FILE_ATTRIBUTE_DIRECTORY))
        {
            uiRoot = candidate;
            break;
        }
    }
    if (uiRoot.empty())
        return false;

    if (!mainHud.load(joinPath(uiRoot, L"MainPanel03.png")))
        return false;
    if (!mainTitle.load(joinPath(uiRoot, L"MainPanel01.png")))
        return false;
    if (!mainResult.load(joinPath(uiRoot, L"MainPanel02.png")))
        return false;
    if (!titleStrip.load(joinPath(uiRoot, L"TitlePanel01.png")))
        return false;
    if (!hiStrip.load(joinPath(uiRoot, L"TitlePanel02.png")))
        return false;
    if (!sliderTrack.load(joinPath(uiRoot, L"Slider01.png")))
        return false;
    if (!btnStart.load(joinPath(uiRoot, L"Button01.png")))
        return false;
    if (!btnPlate.load(joinPath(uiRoot, L"Button11.png")))
        return false;
    if (!btnBanner.load(joinPath(uiRoot, L"Button15.png")))
        return false;
    if (!hexFrame.load(joinPath(uiRoot, L"Button07.png")))
        return false;
    if (!lifeSlot.load(joinPath(uiRoot, L"Button02.png")))
        return false;
    sliderKnob.load(joinPath(uiRoot, L"Slider02.png"));
    return true;
}
