#pragma once

#include <SDL.h>
#include <grid.h>
#include <vector>
#include <game_object.h>
#include <block_shape.h>
#include <point.h>

class Block : public IGameObject  {
public:
	Block(Grid*);
	void Update(Uint32);
	void Render(SDL_Renderer*);
	void Rotate();
	void Drop();
	void MoveLaterally(int);
private:
	// Oh cool the params don't need names
	bool CheckCollide(float, float, std::vector<Point>);
	Point center;
	Grid* grid;
	std::vector<Point> offsets;
	int last_drop_time;
};