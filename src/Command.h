#ifndef CMAKESFMLPROJECT_COMMAND_H
#define CMAKESFMLPROJECT_COMMAND_H

#include <SFML/System/Time.hpp>

#include <functional>
#include <cassert>

class SceneNode;
class EntityObject;

struct Command
{                                                   Command();
    std::function<void(SceneNode&, sf::Time)>       action;
    std::function<void(EntityObject&, sf::Time)>    entityAction;
    unsigned int                                    category;
};

template<typename GameObject, typename Function>
std::function<void(SceneNode&, sf::Time)> derivedAction(Function fn)
{
    return [=] (SceneNode& node, sf::Time dt)
    {
        assert(dynamic_cast<GameObject*>(&node) != nullptr);
        fn(static_cast<GameObject&>(node), dt);
    };
}

template<typename GameObject, typename Function>
std::function<void(EntityObject&, sf::Time)> derivedEntityAction(Function fn)
{
    return [=] (EntityObject& node, sf::Time dt)
    {
        assert(dynamic_cast<GameObject*>(&node) != nullptr);
        fn(static_cast<GameObject&>(node), dt);
    };
}


#endif // CMAKESFMLPROJECT_COMMAND_H