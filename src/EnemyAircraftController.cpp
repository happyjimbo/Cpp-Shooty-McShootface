#include "EnemyAircraftController.h"

#include <iostream>

#include "EntitySystem.h"
#include "Random.h"

EnemyAircraftController::EnemyAircraftController(
    EntitySystem& entitySystem,
    ProjectileController& projectileController,
    const TextureHolder& textures,
    const Aircraft::Type type,
    const sf::Vector2f position,
    const sf::FloatRect worldBounds)
: mTexture(textures)
, mEntitySystem(entitySystem)
, mProjectileController(projectileController)
, mAircraftType(type)
, mWorldBounds(worldBounds)
, mStartPosition(position)
, mAircrafts()
, mTimeSinceLastSpawn()
{

}

void EnemyAircraftController::tick(const sf::Time& delta, const float speed) {
    mTimeSinceLastSpawn += delta.asSeconds();
    accelerate(speed / 50);
    spawn();
    checkBounds();
}

void EnemyAircraftController::spawn() {
    if (mTimeSinceLastSpawn > 0.1f) {
        mTimeSinceLastSpawn = 0;

        const auto aircraft = std::make_shared<Aircraft>(mProjectileController, mAircraftType, mTexture);

        const float x = getRandomFloat(0, mStartPosition.x);
        const auto startPosition = sf::Vector2f(x, mStartPosition.y);
        aircraft->setPosition(startPosition);

        aircraft->setRotation(180);

        mAircrafts.push_back(aircraft);

        mEntitySystem.addObject(aircraft);
    }
}

void EnemyAircraftController::checkBounds() {

    std::vector<std::shared_ptr<Aircraft>> toRemove;

    for (auto& aircraft : mAircrafts) {
        if (aircraft->getPosition().y > mWorldBounds.height) {
            toRemove.push_back(aircraft);
        }
    }

    for (auto& aircraft : toRemove) {
        destroy(aircraft);
    }
}


void EnemyAircraftController::accelerate(float const speed) const {
    for (const auto& aircraft : mAircrafts) {
        aircraft->accelerate(0.f, -speed);
    }
}

std::vector<std::shared_ptr<Aircraft>>& EnemyAircraftController::getAircrafts() {
    return mAircrafts;
}

void EnemyAircraftController::destroy(std::shared_ptr<Aircraft>& aircraft) {
    auto found = std::find_if(mAircrafts.begin(), mAircrafts.end(),
        [&](const std::shared_ptr<Aircraft>& a) {
        return a.get() == aircraft.get();
    });
    if (found != mAircrafts.end()) {
        mAircrafts.erase(found);
        mEntitySystem.removeObject(aircraft);
    }
}

