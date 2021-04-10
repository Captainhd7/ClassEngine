#include "MouseEventListener.h"
#include "../Core/CoreEngine.h"

CoreEngine* MouseEventListener::engineInstance = nullptr;
glm::vec2 MouseEventListener::mouse = glm::vec2();
glm::vec2 MouseEventListener::prevMouse = glm::vec2();
bool MouseEventListener::firstUpdate = true;

MouseEventListener::~MouseEventListener() {
	engineInstance = nullptr;
}

void MouseEventListener::RegisterEngineObject(CoreEngine* engine_) {
	engineInstance = engine_;
}

void MouseEventListener::Update(SDL_Event e_) {
	switch (e_.type) {
	case SDL_MOUSEBUTTONDOWN:
		UpdateMousePos();
		NotifyMousePressed(e_.button.button);
		break;
	case SDL_MOUSEBUTTONUP:
		UpdateMousePos();
		NotifyMousePressed(e_.button.button);
		break;
	case SDL_MOUSEMOTION: 
		UpdateMousePos();
		NotifyMouseMove();
		break;
	case SDL_MOUSEWHEEL:
		UpdateMousePos();
		NotifyMouseScrool(e_.wheel.y);
		break;
	
	default:
		break;
	}
}

void MouseEventListener::NotifyMousePressed(int buttonType_) {

}

void MouseEventListener::NotifyMouseReleased(int buttonType_) {

}

void MouseEventListener::NotifyMouseMove() {

}

void MouseEventListener::NotifyMouseScrool(int y_) {

}

glm::vec2 MouseEventListener::GetPrevMousePos() {
	return prevMouse;
}

glm::vec2 MouseEventListener::GetMousePos() {
	return mouse;
}

glm::vec2 MouseEventListener::GetMouseOffset() {
	return glm::vec2(mouse.x - prevMouse.x, prevMouse.y - mouse.y);
}

void MouseEventListener::UpdateMousePos() {
	int tmpX, tmpY;
	SDL_GetMouseState(&tmpX, &tmpY);
	tmpY = engineInstance->GetScreenHeight() - tmpY;
	if (firstUpdate) {
		prevMouse.x = mouse.x = tmpX;
		prevMouse.y = mouse.y = tmpY;
		firstUpdate = false;
	}
	else {
		prevMouse.x = mouse.x;
		prevMouse.y = mouse.y;
		mouse.x = tmpX;
		mouse.y = tmpY;
	}
}
