#include <cassert>
#include "ResourceHolder.h"

template<typename Resource, typename Identifier>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

    insertResource(id, std::move(resource));
}

template<typename Resource, typename Identifier>
template<typename Paramter>
void ResourceHolder<Resource, Identifier>::load(Identifier id, const std::string& filename, const Paramter& secondParameter)
{
    std::unique_ptr<Resource> resource(new Resource());
    if (!resource->loadFromFile(filename, secondParameter))
        throw std::runtime_error("ResourceHolder::load - Failed to load " + filename);

    insertResource(id, std::move(resource));
}

template<typename Resource, typename Identifier>
Resource& ResourceHolder<Resource, Identifier>::get(Identifier id)
{
    auto found = mResourceMap.find(id);
    assert(found != mResourceMap.end());

    return *found->second;
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
    auto inseted = mResourceMap.insert(std::make_pair(id, std::move(resource)));
    assert(inseted.second);
}