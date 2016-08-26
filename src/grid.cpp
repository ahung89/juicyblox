#include <SDL.h>
#include <stdio.h>
#include <grid.h>
#include <constants.h>
#include <util/color.h>

int Grid::CellDimension = 20;
int Grid::NumRows = 20;
int Grid::NumCols = 10;

Grid::Grid()
{
	grid = std::vector<std::vector<int>>(NumRows, std::vector<int>(NumCols, -1));
}

void Grid::Update(Uint32 ticks) 
{
}

void Grid::Render(SDL_Renderer* renderer) 
{
	SDL_Rect cell_rect;

	for (int row = 0; row < grid.size(); row++)
	{
		for (int col = 0; col < grid[0].size(); col++) 
		{
			cell_rect = {col * CellDimension, row * CellDimension, CellDimension, CellDimension};

			if (grid[row][col] != -1)
			{
 				ColorValues color_values = ColorMap[grid[row][col]];
				SDL_SetRenderDrawColor(renderer, color_values.r, color_values.g, color_values.b, 255);
				SDL_RenderFillRect(renderer, &cell_rect);
			}

			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
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
		   && x < grid[0].size()
		   && y >= 0 
		   && y < grid.size();
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

void Grid::ClearIfNecessary()
{
	int num_clears = 0;

	for (int row = grid.size() - 1; row >= 0; row--) 
	{
		int num_filled = 0;
		for (int col = 0; col < grid[0].size(); col++)
		{
			if (grid[row][col] != -1)
			{
				num_filled++;
			}// Can't break out of nested loops in C++?
			if (num_clears > 0)
			{
				grid[row + num_clears][col] = grid[row][col];
				grid[row][col] = -1;
			}
		}
		if (num_filled == grid[0].size())
		{
			num_clears++;
		}
	}
}