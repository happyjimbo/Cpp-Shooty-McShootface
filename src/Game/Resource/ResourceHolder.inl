#include <cassert>
#include <iostream>

#include "ResourceHolder.h"

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
    std::unique_ptr<Resource> resource = std::make_unique<Resource>();

    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

    insertResource(id, std::move(resource));
}

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::loadShader(Identifier id, const std::string& filename, sf::Shader::Type type)
{
    std::unique_ptr<Resource> resource = std::make_unique<Resource>();

    if (!resource->loadFromFile(filename, type))
        throw std::runtime_error("ResourceHolder::loadShader - Failed to load shader " + filename);

    insertResource(id, std::move(resource));
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    return const_cast<Resource&>(static_cast<const ResourceHolder*>(this)->get(id));
}

template<typename Resource, typename Identifier>
const Resource& ResourceHolder<Resource, Identifier>::get(Identifier id) const
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    return *found->second;
}

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::insertResource(Identifier id, std::unique_ptr<Resource> resource)
{
    auto inserted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    if (!inserted.second)
    {
        std::cerr << "Warning: Duplicate identifier detected in ResourceHolder" << std::endl;
    }
}