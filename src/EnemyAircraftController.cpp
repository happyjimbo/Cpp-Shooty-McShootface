#include "EnemyAircraftController.h"

#include "Logger.h"
#include "Random.h"

EnemyAircraftController::EnemyAircraftController(const TextureHolder &textures, Aircraft::Type type, sf::Vector2f position)
: mTexture(textures)
, mAircraftType(type)
, mStartPosition(position)
, mAircrafts()
, mTimeSinceLastSpawn()
{

}

void EnemyAircraftController::spawn() {
    if (mTimeSinceLastSpawn > 0.1f) {
        mTimeSinceLastSpawn = 0;

        auto aircraft = std::make_shared<Aircraft>(mAircraftType, mTexture);

        float x = getRandomFloat(0, mStartPosition.x);
        sf::Vector2f startPosition = sf::Vector2f(x, mStartPosition.y);
        aircraft->setPosition(startPosition);

        aircraft->setRotation(180);

        mAircrafts.push_back(aircraft.get());

        attachChild(aircraft);
    }
}

void EnemyAircraftController::tick(sf::Time const delta, float const speed) {
    mTimeSinceLastSpawn += delta.asSeconds();
    accelerate(speed / 50);
    spawn();
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

