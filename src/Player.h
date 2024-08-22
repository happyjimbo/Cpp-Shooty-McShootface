#pragma once

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <map>

struct Command;
class CommandQueue;

class Player final
{
public:
    enum Action
    {
        MoveLeft,
        MoveRight,
        MoveUp,
        MoveDown,
        Fire,
        ActionCount
    };

    explicit Player();
    void handleEvent(const sf::Event& event, CommandQueue& commands);
    void handleRealtimeInput(CommandQueue& commands);


private:
    void initializeActions();
    static bool isRealtimeAction(Action action);

private:
    std::map<sf::Keyboard::Key, Action> mKeyBinding;
    std::map<Action, Command> mActionBinding;

    constexpr static float playerSpeed = 400.f;
    constexpr static float horizontalSpeed = playerSpeed * 1.4f;
    constexpr static float mPlayerProjectileSpawnSpeed = 0.1f;

};
