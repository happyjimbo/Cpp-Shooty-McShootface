#pragma once

#include "EntityObject.h"
#include "ResourceIdentifiers.h"
#include <SFML/Graphics/Text.hpp>

namespace GUI
{
    class Label final: public EntityObject
    {
    public:
        Label() = default;
        ~Label() override = default;

        Label(const Label&) = delete;
        Label operator=(const Label&) = delete;

        Label(const Label&&) = delete;
        Label operator=(const Label&&) = delete;

        void create(const std::string& text, const FontHolder& fonts, int size = 16);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void setText(const std::string& text);
        sf::FloatRect getLocalBounds() const;
        sf::FloatRect getGlobalBounds() const;

    private:
        sf::Text  mText;
    };
}