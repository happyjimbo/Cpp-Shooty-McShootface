#pragma once
#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

#include "Category.h"

class EntityObject;

struct Command final
{
    explicit Command() = default;
    std::function<void(EntityObject&, sf::Time)> action;
    unsigned int category = Category::None;
};

template<typename GameObject, typename Function>
std::function<void(EntityObject&, sf::Time)> derivedAction(Function fn)
{
    return [=] (EntityObject& node, sf::Time dt)
    {
        assert(dynamic_cast<GameObject*>(&node) != nullptr);
        fn(static_cast<GameObject&>(node), dt);
    };
}