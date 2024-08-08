#include "EnemyAircraftController.h"

#include <iostream>

#include "Random.h"

EnemyAircraftController::EnemyAircraftController(
    const TextureHolder& textures,
    const Aircraft::Type type,
    const sf::Vector2f position,
    const sf::FloatRect worldBounds)
: mTexture(textures)
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

        const auto aircraft = std::make_shared<Aircraft>(mAircraftType, mTexture);

        const float x = getRandomFloat(0, mStartPosition.x);
        const auto startPosition = sf::Vector2f(x, mStartPosition.y);
        aircraft->setPosition(startPosition);

        aircraft->setRotation(180);

        mAircrafts.push_back(aircraft.get());

        attachChild(aircraft);
    }
}

void EnemyAircraftController::checkBounds() {
    for (const Aircraft* aircraft : mAircrafts) {
        if (aircraft->getPosition().y > mWorldBounds.height) {
            destroy(*aircraft);
        }
    }
}


void EnemyAircraftController::accelerate(float const speed) const {
    for (Aircraft* aircraft : mAircrafts) {
        aircraft->accelerate(0.f, -speed);
    }
}

std::vector<Aircraft*> EnemyAircraftController::getAircrafts() {
    return mAircrafts;
}

void EnemyAircraftController::destroy(const Aircraft& aircraft) {
    auto it = std::find(mAircrafts.begin(), mAircrafts.end(), &aircraft);
    if (it != mAircrafts.end()) {
        mAircrafts.erase(it);
        detachChild(aircraft);
    }
}

