#pragma once

#include "CircularBuffer.h"
#include "IGameMode.h"
#include "GameSettings.h"
#include "Settings.h"

namespace GameMode
{
    class EditorGameMode final : public IGameMode
    {
    public:
        sf::VideoMode determineVideoMode(const GameSettingsData& settings) const override;
        void init(sf::RenderWindow& window, std::shared_ptr<GameSettings>& gameSettings) override;
        bool isWindowOpen(sf::RenderWindow& window) override;
        void processEvent(sf::Event& event) override;
        bool update(sf::RenderWindow& window, const sf::Time& elapsedTime) override;
        void render(sf::RenderWindow& window) override;
        void shutdown() override;
        void setWorld(World* world) override;
    private:
        bool mSuccess {false};
        std::unique_ptr<Settings> mSettingsPanel {};
        World* mWorld;

        static constexpr size_t MaxSampleSize {10000}; // 40kb
        static constexpr size_t GraphHeight {40};
        CircularBuffer<float, MaxSampleSize> mFramesBuffer;
        CircularBuffer<float, MaxSampleSize> mMemoryBuffer;

        CircularBuffer<float, MaxSampleSize> mProjectileBuffer;
        CircularBuffer<float, MaxSampleSize> mPlayerAircraftBuffer;
        CircularBuffer<float, MaxSampleSize> mEnemyAircraftBuffer;
        CircularBuffer<float, MaxSampleSize> mBackgroundBuffer;
        CircularBuffer<float, MaxSampleSize> mCloudBuffer;
        CircularBuffer<float, MaxSampleSize> mExplosionBuffer;
        CircularBuffer<float, MaxSampleSize> mLabelBuffer;
        CircularBuffer<float, MaxSampleSize> mStarBuffer;
    };
}