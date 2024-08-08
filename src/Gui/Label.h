#ifndef CMAKESFMLPROJECT_LABEL_H
#define CMAKESFMLPROJECT_LABEL_H


#include "../ResourceIdentifiers.h"
#include "../SceneNode.h"
#include "SFML/Graphics/Text.hpp"

namespace GUI
{
    //class Label : public sf::Drawable, public sf::Transformable, private sf::NonCopyable
    class Label : public SceneNode
    {
        public:
                    Label(const std::string& text, const FontHolder& fonts);
            void    draw(sf::RenderTarget& target, sf::RenderStates states) const override;
            void    setText(const std::string& string);

        private:
            sf::Text            mText;
    };
}


#endif // CMAKESFMLPROJECT_LABEL_H