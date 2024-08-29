#include "Label.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

namespace GUI
{
    void Label::create(const std::string& text, const FontHolder& fonts)
    {
        mText.setFont(fonts.get(Fonts::ID::Main));
        mText.setCharacterSize(16);
        mText.setString(text);
    }

    void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(mText, states);
    }

    void Label::setText(const std::string& text) {
        mText.setString(text);
    }

    void Label::update(sf::Time delta) {
        // do nothing
    }
}
