#include <stdio.h>
#include <block.h>
#include <stdlib.h>
#include <algorithm>

static int MillisPerDrop = 800;
static std::vector<BlockShape> BlockShapes = {
	{{0, 0}, {{-1.5, -.5}, {-.5, -.5}, {.5, -.5}, {1.5, -.5}}, Color::LightBlue}, // Line
	{{.5, .5}, {{-1, -1}, {-1, 0}, {0, 0}, {1, 0}}, Color::DarkBlue},             // L
	{{.5, .5}, {{-1, 0}, {0, 0}, {1, 0}, {1, -1}}, Color::Orange},                // Reverse L
	{{0, 0}, {{-.5, -.5}, {-.5, .5}, {.5, -.5}, {.5, .5}}, Color::Yellow},        // Square
	{{.5, .5}, {{-1, 0}, {0, 0}, {0, -1}, {1, -1}}, Color::Green},                // Tut
	{{.5, .5}, {{-1, 0}, {0, 0}, {0, -1}, {1, 0}}, Color::Purple},                // Hat
	{{.5, .5}, {{-1, -1}, {0, -1}, {0, 0}, {1, 0}}, Color::Red}                   // Reverse Tut
};
static float BlockCenterOffset = .5;

Block::Block(Grid* grid) : 
	last_drop_time(0),
	grid {grid}
{
	next_shape = BlockShapes[rand() % BlockShapes.size()];
	BlockShape curr_shape = BlockShapes[rand() % BlockShapes.size()];
	center = {curr_shape.origin_offset.x + 5, curr_shape.origin_offset.y + 1};
	offsets = curr_shape.offsets;
	color = curr_shape.color;
}

void Block::Reset()
{
	center = {next_shape.origin_offset.x + 5, next_shape.origin_offset.y + 1};
	offsets = next_shape.offsets;
	color = next_shape.color;
	next_shape = BlockShapes[rand() % BlockShapes.size()];
}

void Block::Update(Uint32 ticks)
{
	if (ticks >= last_drop_time + MillisPerDrop)
	{
		Drop(ticks);
	}
}

void Block::Render(SDL_Renderer* renderer)
 {
 	RenderPreview(renderer);
 	RenderBlock(renderer, offsets, center, color);
 }

void Block::RenderBlock(SDL_Renderer* renderer, std::vector<Point> offsets, Point center, int color)
{
 	ColorValues color_values = ColorMap[color];

	std::vector<Point>::iterator it;
	SDL_Rect cell_rect;

	for (it = offsets.begin(); it != offsets.end(); it++)
	{	
		cell_rect = {(center.x + it->x - BlockCenterOffset) * Grid::CellDimension, (center.y + it->y - BlockCenterOffset)
		 * Grid::CellDimension, Grid::CellDimension, Grid::CellDimension};
		SDL_SetRenderDrawColor(renderer, color_values.r, color_values.g, color_values.b, 0xFF);
		SDL_RenderFillRect(renderer, &cell_rect);
	}

}

void Block::RenderPreview(SDL_Renderer* renderer)
{
	RenderBlock(renderer, next_shape.offsets, preview_location, next_shape.color);
}

bool Block::CheckCollide(float x, float y, std::vector<Point> offsets_to_check)
{
	std::vector<Point>::iterator it;
	for (it = offsets_to_check.begin(); it != offsets_to_check.end(); it++) 
	{
		int currX = x + it->x - BlockCenterOffset;
		int currY = y + it->y - BlockCenterOffset;
		if (!grid->InGridBounds(currX, currY) || grid->GetVal(currX, currY) != -1)
		{
			return true;
		}
	}
	return false;
}

void Block::MoveLaterally(int dir)
{
	if (!CheckCollide(center.x + dir, center.y, offsets))
		center.x += dir;
}

void Block::Rotate()
{
	std::vector<Point> new_offsets;
	std::for_each(offsets.begin(), offsets.end(), [&] (Point p) { new_offsets.push_back({-p.y, p.x}); });
	if (!CheckCollide(center.x, center.y, new_offsets)) {
		offsets = new_offsets;
	}
}

void Block::Drop(Uint32 ticks)
{
	if (!CheckCollide(center.x, center.y + 1, offsets))
	{
		center.y += 1;
		last_drop_time = ticks;
	}
	else 
	{
		// Set blocks in grid.
		std::for_each(offsets.begin(), offsets.end(), [&] (Point p) {
			grid->SetVal(center.x + p.x - BlockCenterOffset, center.y + p.y - BlockCenterOffset, color);
		});
		grid->ClearIfNecessary();
		Reset();
	}
}