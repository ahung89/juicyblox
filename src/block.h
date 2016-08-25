#pragma once

#include <SDL.h>
#include <grid.h>
#include <vector>
#include <game_object.h>

class Block : public IGameObject  {
public:
	Block(Grid*);
	void Update(Uint32);
	void Render(SDL_Renderer*);
	void Rotate();
	void MoveLaterally(int);
	static int MillisPerDrop;
private:
	// Oh cool the params don't need names
	bool CheckCollide(int, int, std::vector<SDL_Point>);
	SDL_Point pos;
	Grid* grid;
	std::vector<SDL_Point> offsets;
	int last_drop_time;
};