#include <SDL.h>
#include <stdio.h>
#include <grid.h>
#include <constants.h>
#include <util/color.h>

int Grid::CellDimension = 20;

Grid::Grid() 
{
	for (int row = 0; row < sizeof(grid)/sizeof(grid[0]); row++) {
		for (int col = 0; col < sizeof(grid[0])/sizeof(int); col++) {
			grid[row][col] = -1;
		}
	}
}

void Grid::Update(Uint32 ticks) 
{
}

void Grid::Render(SDL_Renderer* renderer) 
{
	SDL_Rect cell_rect;
	for (int row = 0; row < sizeof(grid)/sizeof(grid[0]); row++)
	{
		for (int col = 0; col < sizeof(grid[0])/sizeof(int); col++) 
		{
			cell_rect = {col * CellDimension, row * CellDimension, CellDimension, CellDimension};
			if (grid[row][col] != -1)
			{
 				ColorValues color_values = ColorMap[grid[row][col]];
				SDL_SetRenderDrawColor(renderer, color_values.r, color_values.g, color_values.b, 0xFF);
				SDL_RenderFillRect(renderer, &cell_rect);
			}

			SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderDrawRect(renderer, &cell_rect);
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

void Grid::SetVal(int x, int y, int val)
{
	grid[y][x] = val;
}