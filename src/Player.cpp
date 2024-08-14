#include "Player.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Entity/AircraftEntity.h"
#include "Category.h"
#include "ProjectileController.h"


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

Player::Player()
{
    mKeyBinding[sf::Keyboard::Left] = MoveLeft;
    mKeyBinding[sf::Keyboard::Right] = MoveRight;
    mKeyBinding[sf::Keyboard::Up] = MoveUp;
    mKeyBinding[sf::Keyboard::Down] = MoveDown;
    mKeyBinding[sf::Keyboard::Space] = Fire;

    initializeActions();

    for (auto& pair : mActionBinding)
    {
        pair.second.category = Category::PlayerAircraft;
    }
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
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

void Player::handleRealtimeInput(CommandQueue& commands)
{
    for (auto pair : mKeyBinding)
    {
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealtimeAction(pair.second))
        {
            commands.push(mActionBinding[pair.second]);
        }
    }
}

void Player::assignKey(Action action, sf::Keyboard::Key key)
{
    for (auto itr = mKeyBinding.begin(); itr != mKeyBinding.end();)
    {
        if (itr->second == action)
        {
            mKeyBinding.erase(itr++);
        }
        else
        {
            ++itr;
        }

        mKeyBinding[key] = action;
    }
}

sf::Keyboard::Key Player::getAssignedKey(Action action) const
{
    for (auto pair : mKeyBinding)
    {
        if (pair.second == action)
        {
            return pair.first;
        }
    }
    return sf::Keyboard::Unknown;
}

//// private


void Player::initializeActions()
{
    constexpr float playerSpeed = 200.f;
    constexpr float horizontalSpeed = playerSpeed * 1.4f;

    mActionBinding[MoveLeft].entityAction = derivedEntityAction<AircraftEntity>(AircraftMover(-horizontalSpeed, 0.f));
    mActionBinding[MoveRight].entityAction = derivedEntityAction<AircraftEntity>(AircraftMover(+horizontalSpeed, 0.f));
    mActionBinding[MoveUp].entityAction = derivedEntityAction<AircraftEntity>(AircraftMover(0.f, -playerSpeed));
    mActionBinding[MoveDown].entityAction = derivedEntityAction<AircraftEntity>(AircraftMover(0.f, +playerSpeed));
    mActionBinding[Fire].entityAction = derivedEntityAction<AircraftEntity>([] (const AircraftEntity& b, sf::Time){
        b.triggerProjectile(ProjectileEntity::Player);
    });
}

bool Player::isRealtimeAction(Action action)
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