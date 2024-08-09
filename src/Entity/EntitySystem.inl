#include <Entity/EntitySystem.h>

template<typename PtrType>
using EnabledIfSharedOrUniquePtr = std::enable_if_t<
    std::is_convertible_v<PtrType, std::unique_ptr<EntityObject>> ||
    std::is_convertible_v<PtrType, std::shared_ptr<EntityObject>>
>;

template<typename PtrType, typename = EnabledIfSharedOrUniquePtr<PtrType>>
void EntitySystem::addObject(PtrType&& entity)
{
    mEntities.emplace_back(std::forward<PtrType>(entity));
}

template<typename PtrType, typename = EnabledIfSharedOrUniquePtr<PtrType>>
void EntitySystem::removeObject(PtrType&& entity) {
    if (entity) {
        mEntitiesToRemove.insert(entity.get());
    }
}