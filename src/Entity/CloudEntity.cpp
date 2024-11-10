#include "CloudEntity.h"

#include <iostream>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>
#include "ResourceIdentifiers.h"
#include "ResourceHolder.h"

void CloudEntity::create(
    const sf::Texture& texture,
    const TextureHolder& textures,
    ShaderHolder& shaders,
    const sf::IntRect& rect,
    const float scrollSpeed
)
{
    mSprite.setTexture(texture);
    mSprite.setTextureRect(rect);
    mSprite.setScale(sScaleX, sScaleY);

    shader = &shaders.get(Shaders::Clouds);

    auto& noise = textures.get(Textures::NoiseTexture);
    shader->setUniform("noiseTexture", noise);
    shader->setUniform("texture", sf::Shader::CurrentTexture);

    mCloudData.cloudRect = rect;
    mCloudData.scrollSpeed = scrollSpeed * 2.f;
}

void CloudEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    shader->setUniform("time", mAccumulatedTime);

    states.transform *= getTransform();
    states.shader = shader;
    target.draw(mSprite, states);
}

void CloudEntity::update(const sf::Time delta)
{
    EntityObject::update(delta);
    mAccumulatedTime += delta.asSeconds();

    if (mAccumulatedTime > 10.f)
    {
        mAccumulatedTime = fmod(mAccumulatedTime, 10.f);
    }
}