#include "Player.h"
#include "Command.h"
#include "CommandQueue.h"
#include "Aircraft.h"
#include "Category.h"
#include "ProjectileController.h"


struct AircraftMover
{
    AircraftMover(float vx, float vy)
    : velocity(vx, vy)
    {
    }

    // some magic in order to do a callback
    void operator() (Aircraft& aircraft, sf::Time) const
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

    mActionBinding[Fire].category = Category::PlayerProjectile;
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

    mActionBinding[MoveLeft].action = derivedAction<Aircraft>(AircraftMover(-horizontalSpeed, 0.f));
    mActionBinding[MoveRight].action = derivedAction<Aircraft>(AircraftMover(+horizontalSpeed, 0.f));
    mActionBinding[MoveUp].action = derivedAction<Aircraft>(AircraftMover(0.f, -playerSpeed));
    mActionBinding[MoveDown].action = derivedAction<Aircraft>(AircraftMover(0.f, +playerSpeed));
    mActionBinding[Fire].action = derivedAction<ProjectileController>([] (ProjectileController& b, sf::Time){
        b.spawn(Projectile::Player);
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