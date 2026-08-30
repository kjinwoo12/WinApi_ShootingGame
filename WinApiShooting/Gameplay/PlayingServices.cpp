#include "PlayingServices.h"

PlayingServices::PlayingServices(EffectsEngine& fx)
    : powerUps(fx),
      weapon(bullets, fx),
      combat(fx, bullets, powerUps),
      player(weapon, combat),
      enemies(bullets, fx),
      waves(enemies)
{
}
