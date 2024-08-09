#ifndef CMAKESFMLPROJECT_CATEGORY_H
#define CMAKESFMLPROJECT_CATEGORY_H

namespace Category
{
    enum Type
    {
        None            = 0,
        Scene           = 1 << 0,
        PlayerAircraft  = 1 << 1,
        AlliedAircraft  = 1 << 2,
        EnemyAircraft   = 1 << 3,
    };
}

#endif //CMAKESFMLPROJECT_CATEGORY_H