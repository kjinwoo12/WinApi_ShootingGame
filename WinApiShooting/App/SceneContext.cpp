#include "SceneContext.h"

SceneContext::SceneContext()
    : powerUps(fx),
      weapon(bullets, fx),
      combat(fx, bullets),
      player(weapon, combat),
      enemies(bullets, fx),
      waves(enemies)
{
}
