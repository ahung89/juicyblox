#pragma once

#include <game_object.h>
#include <SDL.h>
#include <vector>

class Grid : public IGameObject {
public:
	Grid ();
	void Render(SDL_Renderer*);
	void Update(Uint32);
	int GetVal(int, int);
	void SetVal(int, int, int);
	void ClearIfNecessary();
	bool InGridBounds(int, int);
	// works just like statics in other languages. shared by all instances
	static int CellDimension;
	static int NumRows;
	static int NumCols;
private:
	void SetViewport(SDL_Renderer*);
	std::vector<std::vector<int>> grid;
};