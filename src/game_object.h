#pragma once

#include <SDL.h>

class IGameObject {
public:
	// virtual ~IGameObject() {}
	virtual void Update(Uint32) = 0; // pure virtual
	virtual void Render(SDL_Renderer*) = 0;
};