#include "Controls.h"
#include <Command/CommandQueue.h>
#include "Entity/AircraftEntity.h"
#include "Category.h"

struct AircraftMover
{
    AircraftMover(const float vx, const float vy)
    : velocity(vx, vy)
    {
    }

    // some magic in order to do a callback
    void operator() (AircraftEntity& aircraft, sf::Time) const
    {
        aircraft.accelerate(velocity);
    }

    sf::Vector2f velocity;
};

Controls::Controls()
{
    mKeyBinding[sf::Keyboard::Left] = MoveLeft;
    mKeyBinding[sf::Keyboard::A] = MoveLeft;
    mKeyBinding[sf::Keyboard::Right] = MoveRight;
    mKeyBinding[sf::Keyboard::D] = MoveRight;
    mKeyBinding[sf::Keyboard::Up] = MoveUp;
    mKeyBinding[sf::Keyboard::W] = MoveUp;
    mKeyBinding[sf::Keyboard::Down] = MoveDown;
    mKeyBinding[sf::Keyboard::S] = MoveDown;
    mKeyBinding[sf::Keyboard::Space] = Fire;

    initializeActions();

    for (auto& pair : mActionBinding)
    {
        pair.second.category = Category::PlayerAircraft;
    }
}

void Controls::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
        auto found = mKeyBinding.find(event.key.code);
        if (found != mKeyBinding.end() && !isRealtimeAction(found->second))
        {
            commands.push(mActionBinding[found->second]);
        }
    }
}

void Controls::handleRealtimeInput(CommandQueue& commands)
{
    for (auto pair : mKeyBinding)
    {
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
        {
            commands.push(mActionBinding[pair.second]);
        }
    }
}


void Controls::initializeActions()
{
    mActionBinding[MoveLeft].action = derivedAction<AircraftEntity>(AircraftMover(-horizontalSpeed, 0.f));
    mActionBinding[MoveRight].action = derivedAction<AircraftEntity>(AircraftMover(+horizontalSpeed, 0.f));
    mActionBinding[MoveUp].action = derivedAction<AircraftEntity>(AircraftMover(0.f, -playerSpeed));
    mActionBinding[MoveDown].action = derivedAction<AircraftEntity>(AircraftMover(0.f, +playerSpeed));
    mActionBinding[Fire].action = derivedAction<AircraftEntity>([] (AircraftEntity& b, sf::Time){
        b.triggerProjectile(ProjectileEntity::Player, mPlayerProjectileSpawnSpeed);
    });
}

bool Controls::isRealtimeAction(const Action action)
{
    switch (action) {
        case MoveLeft:
        case MoveRight:
        case MoveUp:
        case MoveDown:
        case Fire:
            return true;

        default:
            return false;
    }
}