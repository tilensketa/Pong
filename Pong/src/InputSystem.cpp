#include "InputSystem.h"

#include <spdlog/spdlog.h>

void InputSystem::Init() {
	spdlog::info("Initializing InputSystem");
}

void InputSystem::Update() {
	glfwPollEvents();
}

void InputSystem::Close() {
	spdlog::info("Closing InputSystem");
}