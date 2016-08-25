#include <grid.h>
#include <stdio.h>
#include <block.h>

int Block::MillisPerDrop = 800;

Block::Block(Grid* grid) : 
	last_drop_time{0},
	pos{5, 5},
	offsets{{0, 0}, {0, 1}, {0, 2}, {0, 3}},
	grid {grid}
	{}

void Block::Update(Uint32 ticks)
{
	if (ticks >= last_drop_time + MillisPerDrop)
	{
		if (!CheckCollide(pos.x, pos.y + 1, offsets))
		{
			pos.y += 1;
			last_drop_time = ticks;
		}
		else 
		{
			// Set blocks in grid.
		}
	}
}

void Block::Render(SDL_Renderer* renderer)
 {
	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);

	std::vector<SDL_Point>::iterator it;
	SDL_Rect cellRect;

	for (it = offsets.begin(); it != offsets.end(); it++)
	{	
		cellRect = {(pos.x + it->x) * Grid::CellDimension, (pos.y + it->y) * Grid::CellDimension,
			Grid::CellDimension, Grid::CellDimension};
		SDL_RenderFillRect(renderer, &cellRect);
	}
}

bool Block::CheckCollide(int x, int y, std::vector<SDL_Point> offsets)
{
	std::vector<SDL_Point>::iterator it;
	for (it = offsets.begin(); it!= offsets.end(); it++) 
	{
		int currX = x + it->x, currY = y + it->y;
		if (!grid->InGridBounds(currX, currY) || grid->GetVal(currX, currY) != 0)
		{
			return true;
		}
	}
	return false;
}

void Block::MoveLaterally(int dir)
{
	if (!CheckCollide(pos.x + dir, pos.y, offsets))
		pos.x += dir;
}