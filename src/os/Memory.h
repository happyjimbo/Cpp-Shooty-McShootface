#ifdef __APPLE__
#include <mach/mach.h>
#include <malloc/malloc.h>
#endif

namespace Memory
{
    inline float getProcessMemoryUsageMB()
    {
#ifdef __APPLE__
        task_basic_info info;
        mach_msg_type_number_t size = TASK_BASIC_INFO_COUNT;

        auto kern = task_info(mach_task_self(), TASK_BASIC_INFO, reinterpret_cast<task_info_t>(&info), &size);
        if (kern == KERN_SUCCESS)
        {
            return info.resident_size / (1024.0 * 1024.0); // Convert to MB
        }
#endif
        return 0.0f;
    }
}