#include "PlayerControls.h"
#include "AircraftEntity.h"

void PlayerControls::initializeActions(AircraftEntity& player)
{
    mKeyBinding[sf::Keyboard::Left] = [&player]() -> void {
        player.accelerate(-horizontalSpeed, 0.f);
    };
    mKeyBinding[sf::Keyboard::A] = mKeyBinding[sf::Keyboard::Left];

    mKeyBinding[sf::Keyboard::Right] = [&player]() -> void {
        player.accelerate(+horizontalSpeed, 0.f);
    };
    mKeyBinding[sf::Keyboard::D] = mKeyBinding[sf::Keyboard::Right];

    mKeyBinding[sf::Keyboard::Up] = [&player]() -> void {
        player.accelerate(0.f, -playerSpeed);
    };
    mKeyBinding[sf::Keyboard::W] = mKeyBinding[sf::Keyboard::Up];

    mKeyBinding[sf::Keyboard::Down] = [&player]() -> void {
        player.accelerate(0.f, +playerSpeed);
    };
    mKeyBinding[sf::Keyboard::S] = mKeyBinding[sf::Keyboard::Down];

    mKeyBinding[sf::Keyboard::Space] = [&player]() -> void {
        player.triggerProjectile(ProjectileEntity::Player, sPlayerProjectileSpawnSpeed);
    };
}

void PlayerControls::handleRealtimeInput() const
{
    for (auto pair : mKeyBinding)
    {
        if (sf::Keyboard::isKeyPressed(pair.first))
        {
            pair.second();
        }
    }
}