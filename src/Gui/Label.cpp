#include "Label.h"
#include <Resource/ResourceHolder.h>

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Time.hpp>

namespace GUI
{
    Label::Label(const std::string& text, const FontHolder& fonts)
    : mText(text, fonts.get(Fonts::ID::Main), 16)
    {
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
