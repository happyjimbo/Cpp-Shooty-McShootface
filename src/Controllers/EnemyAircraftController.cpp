#include "EnemyAircraftController.h"
#include "Random.h"

EnemyAircraftController::EnemyAircraftController (
    EntitySystem<AircraftEntity>& entitySystem,
    ProjectileController& projectileController,
    const TextureHolder& textures,
    const AircraftEntity::Type type,
    const sf::Vector2f position,
    const sf::FloatRect worldBounds)
      : mEntitySystem(entitySystem)
      , mProjectileController(projectileController)
      , mTexture(textures)
      , mAircraftType(type)
      , mStartPosition(position)
      , mWorldBounds(worldBounds)
      , mTimeSinceLastSpawn()
{

}

void EnemyAircraftController::tick(const sf::Time& delta, const float speed) {
    mTimeSinceLastSpawn += delta.asSeconds();
    accelerate(speed / 50);
    spawn();
    checkBounds();

    for (const auto& aircraft : mEntitySystem.getEntities()) {
        aircraft->update(delta);
        aircraft->triggerProjectile(ProjectileEntity::Enemy);
    }
}

void EnemyAircraftController::spawn() {
    if (mTimeSinceLastSpawn > 0.1f) {
        mTimeSinceLastSpawn = 0;

        auto* aircraft = mEntitySystem.createObject(mProjectileController, mAircraftType, mTexture);

        const float x = getRandomFloat(0, mStartPosition.x);

        const auto startPosition = sf::Vector2f(x, mStartPosition.y);
        aircraft->setPosition(startPosition);
        aircraft->setRotation(180);
    }
}

void EnemyAircraftController::checkBounds() const {
    for (auto* aircraft : mEntitySystem.getEntities()) {
        if (aircraft->getPosition().y > mWorldBounds.height) {
            removeEntity(aircraft);
        }
    }
}

void EnemyAircraftController::accelerate(float const speed) const {
    for (const auto& aircraft : mEntitySystem.getEntities()) {
        aircraft->accelerate(0.f, -speed);
    }
}

void EnemyAircraftController::removeEntity(AircraftEntity* entity) const {
    mEntitySystem.removeObject(entity);
}

const std::vector<AircraftEntity*>& EnemyAircraftController::getEntities() const {
    return mEntitySystem.getEntities();
}