#include "Label.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI
{
    void Label::create(const std::string& text, const FontHolder& fonts, const int size)
    {
        mText.setFont(fonts.get(Fonts::ID::Main));
        mText.setCharacterSize(size);
        mText.setString(text);
    }

    void Label::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        target.draw(mText, states);
    }

    void Label::setText(const std::string& text)
    {
        mText.setString(text);
    }

    sf::FloatRect Label::getLocalBounds() const
    {
        return mText.getLocalBounds();
    }

    sf::FloatRect Label::getGlobalBounds() const
    {
        return mText.getGlobalBounds();
    }

}
