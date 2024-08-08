#ifndef CMAKESFMLPROJECT_ENTTY_SYSTEM_H
#define CMAKESFMLPROJECT_ENTTY_SYSTEM_H

#include <vector>
#include <SFML/Graphics.hpp>

class EntityObject;
struct Command;

class EntitySystem {
public:
    template<typename PtrType>
    using EnabledIfSharedOrUniquePtr = std::enable_if_t<
        std::is_convertible_v<PtrType, std::unique_ptr<EntityObject>> ||
        std::is_convertible_v<PtrType, std::shared_ptr<EntityObject>>
    >;

public:
    template<typename PtrType, typename = EnabledIfSharedOrUniquePtr<PtrType>>
    void addObject(PtrType&& child)
    {
        mEntities.emplace_back(std::forward<PtrType>(child));
    }

    void removeObject(const EntityObject& object);
    void update(sf::Time dt);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    void onCommand(const Command& command, sf::Time dt);
    std::vector<std::shared_ptr<EntityObject>> getEntities() const;


private:
    std::vector<std::shared_ptr<EntityObject>> mEntities;
};

#endif // CMAKESFMLPROJECT_ENTTY_SYSTEM_H