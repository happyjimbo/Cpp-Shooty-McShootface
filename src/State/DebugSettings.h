#pragma once
#include <memory>

namespace Debug
{
    class DebugSettings final
    {
    public:
        explicit DebugSettings() noexcept;
        ~DebugSettings() noexcept;

        void draw() const;
        bool isPaused() const;
        bool isMuted() const;

    private:
        struct Impl;
        std::unique_ptr<Impl> mImpl;
    };
}
