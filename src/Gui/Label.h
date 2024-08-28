#pragma once

#include "EntityObject.h"
#include <Resource/ResourceIdentifiers.h>
#include "SFML/Graphics/Text.hpp"

namespace GUI
{
    //class Label : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
    class Label final: public EntityObject
    {
    public:
        Label() = default;
        Label(const std::string& text, const FontHolder& fonts) = delete;

        void create(const std::string& text, const FontHolder& fonts);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
        void setText(const std::string& text);
        void update(sf::Time delta) override;

    private:
        sf::Text  mText;
    };
}