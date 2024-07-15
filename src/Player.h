#ifndef CMAKESFMLPROJECT_PLAYER_H
#define CMAKESFMLPROJECT_PLAYER_H

#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <map>

struct Command;
class CommandQueue;

class Player
{
    public:
        enum Action
        {
            MoveLeft,
            MoveRight,
            MoveUp,
            MoveDown,
            ActionCount
        };

    public:
                            Player();
        void                handleEvent(const sf::Event& event, CommandQueue& commands);
        void                handleRealtimeInput(CommandQueue& commands);

        void                assignKey(Action action, sf::Keyboard::Key key);
        sf::Keyboard::Key   getAssignedKey(Action action) const;


    private:
        void                initializeActions();
        static bool         isRealtimeAction(Action action);

    private:
        std::map<sf::Keyboard::Key, Action>         mKeyBinding;
        std::map<Action, Command>                   mActionBinding;

};

#endif // CMAKESFMLPROJECT_PLAYER_H