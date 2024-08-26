#pragma once

namespace sf {
    class Texture;
    class Font;
}

namespace Textures {
    enum ID {
        Eagle,
        Raptor,
        Background,
        Bullet,
        Clouds
    };
}

namespace Fonts {
    enum ID {
        Main
    };
}

template<typename Resource, typename Identifier>
class ResourceHolder;

using TextureHolder = ResourceHolder<sf::Texture, Textures::ID>;
using FontHolder = ResourceHolder<sf::Font, Fonts::ID>;