#include "PlayerControls.h"

#include <iostream>
#include <SFML/Window/Event.hpp>

#include "AircraftEntity.h"

namespace
{
    constexpr float playerSpeed = 400.f;
    constexpr float horizontalSpeed = playerSpeed * 1.4f;
    constexpr float sPlayerProjectileSpawnSpeed = 0.1f;
}

PlayerControls::PlayerControls(Aircraft::AircraftEntity& player)
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

void PlayerControls::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyPressed)
    {
        mActiveKeys.insert(event.key.code);
    }
    else if (event.type == sf::Event::KeyReleased)
    {
        mActiveKeys.erase(event.key.code);
    }
}

void PlayerControls::update() const
{
    for (const auto& key : mActiveKeys)
    {
        auto it = mKeyBinding.find(key);
        if (it != mKeyBinding.end())
        {
            it->second();
        }
    }
}