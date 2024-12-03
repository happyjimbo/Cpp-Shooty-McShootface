#include <imgui.h>

#include "Button.h"

struct CursorState
{
    ImVec2 position;
    ImVec2 size;

#ifdef EDITOR_MODE
    bool isMouseOverObject(const sf::Shape& shape, const sf::RenderTexture& renderTexture) const
    {
        const ImVec2 mousePos = ImGui::GetMousePos();

        if (mousePos.x < position.x ||
            mousePos.x > position.x + size.x ||
            mousePos.y < position.y ||
            mousePos.y > position.y + size.y) {
            return false;
            }

        const float relativeX = (mousePos.x - position.x) / size.x * renderTexture.getSize().x;
        const float relativeY = (mousePos.y - position.y) / size.y * renderTexture.getSize().y;
        const sf::Vector2f renderTexturePos(relativeX, relativeY);

        return shape.getGlobalBounds().contains(renderTexturePos);
    }
#else
    bool isMouseOverObject(const sf::Shape& shape, const sf::RenderTexture&) const 
    {
        const ImVec2 mousePos = ImGui::GetMousePos();
        return shape.getGlobalBounds().contains(sf::Vector2f(mousePos.x, mousePos.y));
    }
#endif
};
