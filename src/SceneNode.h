#ifndef CMAKESFMLPROJECT_SCENENODE_H
#define CMAKESFMLPROJECT_SCENENODE_H

#include <SFML/Graphics.hpp>

struct Command;

class SceneNode : public sf::Transformable, public sf::Drawable, private sf::NonCopyable {
    public:
        template<typename PtrType>
        using EnabledIfSharedOrUniquePtr = std::enable_if_t<
            std::is_convertible_v<PtrType, std::unique_ptr<SceneNode>> ||
            std::is_convertible_v<PtrType, std::shared_ptr<SceneNode>>
        >;

    public:
        template<typename PtrType, typename = EnabledIfSharedOrUniquePtr<PtrType>>
        void attachChild(PtrType&& child)
        {
            child->mParent = this;
            mChildren.emplace_back(std::forward<PtrType>(child));
        }

    public:
                                    SceneNode();

        std::shared_ptr<SceneNode>  detachChild(const SceneNode& node);

        void                        update(sf::Time);

        sf::Vector2f                getWorldPosition() const;
        sf::Transform               getWorldTransform() const;

        void                        onCommand(const Command& command, sf::Time dt);
        virtual unsigned int        getCategory() const;

    private:
        virtual void                updateCurrent(sf::Time dt);
        void                        updateChildren(sf::Time dt);

        void                        draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        virtual void                drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;
        virtual void                drawChildren(sf::RenderTarget& target, sf::RenderStates states) const;

    private:
        std::vector<std::shared_ptr<SceneNode>>         mChildren;
        SceneNode*                                      mParent;
};

#endif //CMAKESFMLPROJECT_SCENENODE_H