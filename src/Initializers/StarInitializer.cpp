#include "StarInitializer.h"
#include "ResourceHolder.h"
#include "StarEntity.h"

StarInitializer::StarInitializer(
    EntitySystem<StarEntity>& entitySystem,
    const TextureHolder& textures
    )
{
    const auto& starTexture = textures.get(Textures::Star);
    entitySystem.createObject(starTexture);
}
