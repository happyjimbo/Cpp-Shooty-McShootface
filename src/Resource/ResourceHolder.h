#pragma once

#include <unordered_map>
#include <SFML/Graphics/Shader.hpp>

template <typename Resource, typename Identifier>
class ResourceHolder final
{
public:
    void load(Identifier id, const std::string& filename);
    void loadShader(Identifier id, const std::string& filename, sf::Shader::Type type);

    Resource& get(Identifier id);
    const Resource& get(Identifier id) const;

private:
    void insertResource(Identifier id, std::unique_ptr<Resource> resource);
    std::unordered_map<Identifier, std::unique_ptr<Resource>> mResourceMap;
};


#include "ResourceHolder.inl"