#pragma once

#include <SDL.h>
#include <grid.h>
#include <vector>
#include <game_object.h>
#include <block_shape.h>
#include <point.h>
#include <util/color.h>

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
	void Reset();
	Point center;
	Grid* grid;
	std::vector<Point> offsets;
	Color color;
	int last_drop_time;
};