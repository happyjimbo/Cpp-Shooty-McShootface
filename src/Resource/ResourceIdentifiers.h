#pragma once

namespace sf
{
    class Texture;
    class Font;
    class SoundBuffer;
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
        PlayerExplosion
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

template<typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;
using SoundHolder = ResourceHolder<sf::SoundBuffer, Sounds::ID>;