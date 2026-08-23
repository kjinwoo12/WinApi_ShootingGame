#pragma once

class DeltaTime
{
public:
    DeltaTime();

    void reset();
    // 프레임 간 경과(초). maxSeconds = 스파이럴 방지 상한.
    float tick(float maxSeconds = 0.05f);

private:
    long long frequency = 0;
    long long lastCounter = 0;
};
