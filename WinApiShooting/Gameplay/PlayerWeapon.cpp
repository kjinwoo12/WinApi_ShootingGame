#include "PlayerWeapon.h"

PlayerWeapon::PlayerWeapon(BulletSystem& bulletSys, EffectsEngine& effects)
    : bullets(bulletSys), fx(effects) {}

void PlayerWeapon::fire(World& world, RandomSource& rng)
{
    PlayerState& player = world.player;
    const float muzzleY = player.pos.y - 28.f;
    const float rateMul = player.raging() ? 0.75f : 1.f;
    const float x = player.pos.x;
    const int rageBonus = player.raging() ? 1 : 0;

    using FireFn = void (*)(BulletSystem&, World&, float x, float muzzleY, float rateMul, int rageBonus);
    static const FireFn kFire[] = {
        [](BulletSystem& b, World& w, float px, float my, float rm, int rb)
        {
            b.spawn(w, BulletOwner::Player, WeaponLevel::Vulcan, {px, my}, {0.f, -780.f}, 1 + rb);
            w.player.fireCooldown = 0.12f * rm;
        },
        [](BulletSystem& b, World& w, float px, float my, float rm, int rb)
        {
            b.spawn(w, BulletOwner::Player, WeaponLevel::Plasma, {px - 10.f, my}, {-40.f, -820.f}, 2 + rb);
            b.spawn(w, BulletOwner::Player, WeaponLevel::Plasma, {px + 10.f, my}, {40.f, -820.f}, 2 + rb);
            w.player.fireCooldown = 0.14f * rm;
        },
        [](BulletSystem& b, World& w, float px, float my, float rm, int rb)
        {
            b.spawn(w, BulletOwner::Player, WeaponLevel::Proton, {px, my}, {0.f, -900.f}, 3 + rb);
            b.spawn(w, BulletOwner::Player, WeaponLevel::Proton, {px - 16.f, my + 6.f}, {-90.f, -860.f}, 2 + rb);
            b.spawn(w, BulletOwner::Player, WeaponLevel::Proton, {px + 16.f, my + 6.f}, {90.f, -860.f}, 2 + rb);
            w.player.fireCooldown = 0.11f * rm;
        },
    };

    const int w = static_cast<int>(player.weapon);
    if (w >= 0 && w < 3)
        kFire[w](bullets, world, x, muzzleY, rateMul, rageBonus);
    fx.spawnMuzzleSparks(world, rng, {player.pos.x, muzzleY});
}
