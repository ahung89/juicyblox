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
	void Drop(Uint32);
	void MoveLaterally(int);
private:
	// Oh cool the params don't need names
	bool CheckCollide(float, float, std::vector<Point>);
	void Reset();
	void RenderBlock(SDL_Renderer*, std::vector<Point>, Point, int);
	void RenderPreview(SDL_Renderer*);

	Point center;
	Grid* grid;
	std::vector<Point> offsets;
	Color color;

	// For the next block preview window
	int last_drop_time;
	Point preview_location = {13, 2};
	BlockShape next_shape;
};