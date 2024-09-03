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
        Label(const std::string&, const FontHolder&, int) = delete;
        ~Label() override = default;

        void create(const std::string& text, const FontHolder& fonts, int size = 16);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void setText(const std::string& text);

    private:
        sf::Text  mText;
    };
}