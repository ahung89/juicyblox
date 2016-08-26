#pragma once

#include <game_object.h>
#include <SDL.h>

class Grid : public IGameObject {
public:
	Grid ();
	void Render(SDL_Renderer*);
	void Update(Uint32);
	int GetVal(int, int);
	void SetVal(int, int, int);
	bool InGridBounds(int, int);
	// works just like statics in other languages. shared by all instances
	static int CellDimension;
private:
	void SetViewport(SDL_Renderer*);
	void ClearIfNecessary();
	int grid[20][10];
};