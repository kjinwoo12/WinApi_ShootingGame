#include "SessionState.h"

void PresentationSession::advanceScroll(float speed, float bgHeight)
{
    backgroundOffset += speed;
    if (bgHeight > 0.f && backgroundOffset >= bgHeight)
        backgroundOffset -= bgHeight;
}

void PresentationSession::decayShake(float dt)
{
    if (shake > 0.f)
        shake = (std::max)(0.f, shake - dt * 8.f);
}
