#include <cassert>
#include "SceneNode.h"
#include "Category.h"
#include "Command.h"


SceneNode::SceneNode()
: mChildren()
, mParent(nullptr)
{

}

std::shared_ptr<SceneNode> SceneNode::detachChild(const SceneNode& node)
{
    const auto found = std::find_if(mChildren.begin(), mChildren.end(),
        [&] (const std::shared_ptr<SceneNode>& p) { return p.get() == &node; });
    assert(found != mChildren.end());

    std::shared_ptr<SceneNode> result = *found;
    result->mParent = nullptr;
    mChildren.erase(found);
    return result;
}

void SceneNode::update(const sf::Time delta)
{
    updateChildren(delta);
    updateCurrent(delta);
}

sf::Vector2f SceneNode::getWorldPosition() const
{
    return getWorldTransform() * sf::Vector2f();
}

sf::Transform SceneNode::getWorldTransform() const
{
    sf::Transform transform = sf::Transform::Identity;

    for (const SceneNode* node = this; node != nullptr; node = node->mParent)
        transform = node->getTransform() * transform;

    return transform;
}

void SceneNode::onCommand(const Command& command, const sf::Time dt)
{
    if (command.category & getCategory())
    {
        command.action(*this, dt);
    }

    for (auto& child : mChildren)
    {
        child->onCommand(command, dt);
    }
}

unsigned int SceneNode::getCategory() const
{
    return Category::Scene;
}

///// Private //////

void SceneNode::updateCurrent(sf::Time dt)
{
    // do nothing by default
}

void SceneNode::updateChildren(const sf::Time dt)
{
    for (const auto& child : mChildren)
    {
        child->update(dt);
    }
}

void SceneNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Apply transform of current node
    states.transform *= getTransform();

    // Draw node and child with changed transform
    drawChildren(target, states);
    drawCurrent(target, states);
}

void SceneNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
    // do nothing by default
}

void SceneNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
{
    for (const auto& child : mChildren)
    {
        child->draw(target, states);
    }
}
