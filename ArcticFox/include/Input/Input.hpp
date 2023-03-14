#pragma once

#include "KeyCodes.hpp"

#include <glm/glm.hpp>

namespace ArcticFox {

class Input {
public:
    static bool IsKeyDown(KeyCode keycode);
    static bool IsMouseButtonDown(MouseButton button);

    static glm::vec2 GetMousePosition();

    static void SetCursorMode(CursorMode mode);
};

}