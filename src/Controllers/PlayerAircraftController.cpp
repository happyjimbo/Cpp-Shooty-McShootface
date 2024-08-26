#include "PlayerAircraftController.h"
#include <Entity/AircraftEntity.h>
#include "Command/CommandQueue.h"

PlayerAircraftController::PlayerAircraftController(
    EntitySystem<AircraftEntity>& entitySystem,
    ProjectileController& projectileController,
    CommandQueue& commandQueue,
    const sf::Vector2f worldCenter,
    const sf::Vector2f worldSize,
    const float scrollSpeed
    ) noexcept
        : mEntitySystem(entitySystem)
        , mProjectileController(projectileController)
        , mCommandQueue(commandQueue)
        , mWorldCenter(worldCenter)
        , mWorldSize(worldSize)
        , mScrollSpeed(scrollSpeed)
{
    mViewBounds = sf::FloatRect(mWorldCenter - mWorldSize / 2.f, mWorldSize);
}

void PlayerAircraftController::create(const TextureHolder& textures, const sf::Vector2f spawnPosition)
{
    mPlayerAircraft = mEntitySystem.createObject(mProjectileController, AircraftEntity::Eagle, textures);
    mPlayerAircraft->setPosition(spawnPosition);
}

void PlayerAircraftController::tick(const sf::Time delta) const
{
    mPlayerAircraft->setVelocity(0.f, 0.f);

    while (!mCommandQueue.isEmpty())
    {
        mEntitySystem.onCommand(mCommandQueue.pop(), delta);
    }

    adaptPlayerVelocity();
    adaptPlayerPosition();
}

void PlayerAircraftController::adaptPlayerVelocity() const
{
    auto position = mPlayerAircraft->getPosition();
    position.x = std::max(position.x, mViewBounds.left + mBorderDistance);
    position.x = std::min(position.x, mViewBounds.left + mViewBounds.width - mBorderDistance);
    position.y = std::max(position.y, mViewBounds.top + mBorderDistance);
    position.y = std::min(position.y, mViewBounds.top + mViewBounds.height - mBorderDistance);
    mPlayerAircraft->setPosition(position);
}

void PlayerAircraftController::adaptPlayerPosition() const
{
    sf::Vector2f velocity = mPlayerAircraft->getVelocity();

    if (velocity.x != 0.f && velocity.y != 0.f)
        mPlayerAircraft->setVelocity(velocity / std::sqrt(2.f));

    mPlayerAircraft->accelerate(0.f, mScrollSpeed/2);
}
