#ifndef CMAKESFMLPROJECT_RESOURCEIDENTIFIERS_HPP
#define CMAKESFMLPROJECT_RESOURCEIDENTIFIERS_HPP

namespace sf
{
    class Texture;
}

namespace Textures
{
    enum ID {
        Eagle,
        Raptor,
        Desert
    };
}

template<typename Resource, typename Identifier>
class ResourceHolder;

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

#endif //CMAKESFMLPROJECT_RESOURCEIDENTIFIERS_HPP