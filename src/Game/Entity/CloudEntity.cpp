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
    if (mSprite.getTexture() != &texture)
    {
        mSprite.setTexture(texture);
    }
    mSprite.setTextureRect(rect);
    mSprite.setScale(sScaleX, sScaleY);

    if (const auto shader = &shaders.get(Shaders::Clouds); shader != mShader)
    {
        mShader = shader;
    }

    auto& noise = textures.get(Textures::NoiseTexture);
    mShader->setUniform("noiseTexture", noise);
    mShader->setUniform("texture", sf::Shader::CurrentTexture);

    mCloudData.cloudRect = rect;
    mCloudData.scrollSpeed = scrollSpeed * 2.f;
}

void CloudEntity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    mShader->setUniform("time", mAccumulatedTime);

    states.transform *= getTransform();
    states.shader = mShader;
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