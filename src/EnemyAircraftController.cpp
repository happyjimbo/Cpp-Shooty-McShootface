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

        std::unique_ptr<Aircraft> aircraft = std::make_unique<Aircraft>(mAircraftType, mTexture);

        float x = getRandomFloat(0, mStartPosition.x);
        sf::Vector2f startPosition = sf::Vector2f(x, mStartPosition.y);
        aircraft->setPosition(startPosition);

        aircraft->setRotation(180);

        mAircrafts.push_back(aircraft.get());

        attachChild(std::move(aircraft));
    }
}

void EnemyAircraftController::tick(sf::Time delta, float speed) {
    mTimeSinceLastSpawn += delta.asSeconds();
    accelerate(speed / 50);
    spawn();
}

void EnemyAircraftController::accelerate(float speed) {
    for (Aircraft* aircraft : mAircrafts) {
        aircraft->accelerate(0.f, -speed);
    }
}

