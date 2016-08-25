#include <SDL.h>
#include <stdio.h>
#include <grid.h>
#include <constants.h>

int Grid::CellDimension = 20;

Grid::Grid() {}

void Grid::Update(Uint32 ticks) {
}

void Grid::Render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_Rect cellRect;
	for (int row = 0; row < sizeof(grid)/sizeof(grid[0]); row++) {
		for (int col = 0; col < sizeof(grid[0])/sizeof(int); col++) {
			grid[row][col] = 0;
			cellRect = {col * CellDimension, row * CellDimension, CellDimension, CellDimension};
			SDL_RenderDrawRect(renderer, &cellRect);
		}
	}
}

int Grid::GetVal(int x, int y)
{
	return grid[y][x];
}

bool Grid::InGridBounds(int x, int y)
{
	return x >= 0 
		   && x < sizeof(grid[0])/sizeof(int)
		   && y >= 0 
		   && y < sizeof(grid)/sizeof(grid[0]);
}

void Grid::SetViewport(SDL_Renderer* renderer) {
	SDL_Rect viewport;
	viewport.x = 0;
	viewport.y = 0;
	viewport.w = SCREEN_WIDTH * (2./3.); // If you don't make these float literals, it'll be 0
	viewport.h = SCREEN_HEIGHT;
	SDL_RenderSetViewport(renderer, &viewport);
}