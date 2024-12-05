#pragma once
#include "SFML/Graphics/Shader.hpp"

namespace sf
{
    class Texture;
    class Font;
    class SoundBuffer;
    class Shader;
}

namespace Textures
{
    enum ID
    {
        Eagle,
        Raptor,
        Background,
        Bullet,
        EnemyBullet,
        Clouds,
        Explosion,
        PlayerExplosion,
        NoiseTexture,
        Star
    };
}

namespace Fonts
{
    enum ID
    {
        Main
    };
}

namespace Sounds
{
    enum ID
    {
        PlayerGunfire,
        EnemyGunfire,
        Explosion1,
        Explosion2,
    };
}

namespace Shaders
{
    enum ID
    {
        Clouds,
        Flash
    };
}

template<typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;
using SoundHolder = ResourceHolder<sf::SoundBuffer, Sounds::ID>;
using ShaderHolder = ResourceHolder<sf::Shader, Shaders::ID>;