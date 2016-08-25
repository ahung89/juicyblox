#include <SDL.h>
#include <stdio.h>
#include <grid.h>
#include <block.h>
#include <constants.h>
#include <game_object.h>
#include <algorithm>
#include <vector>

// Must be a vec of pointers - can't have an abstract class as the type (why?)
typedef std::vector<IGameObject*> obj_vec;

static SDL_Window* window = nullptr;
static SDL_Renderer* renderer = nullptr;
static bool quit = false;
static bool key_lifted = true;

void Init();
void ClearScreen();
void HandleInput(Block &block);
void Update(obj_vec game_objects);
void Render(obj_vec game_objects);

int main(int argc, char* args[]) 
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		Init();

		Grid grid;
		Block block {&grid};
		obj_vec game_objects {&block, &grid};

		while (!quit) 
		{
			HandleInput(block);
			Update(game_objects);
			Render(game_objects);
		}
		
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}

void Init()
{
	window = SDL_CreateWindow("JuicyBlox", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
		SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

void Update(obj_vec game_objects)
{
	Uint32 ticks = SDL_GetTicks();
	std::for_each(game_objects.begin(), game_objects.end(), [&] (IGameObject* obj) { obj->Update(ticks); });
}

void Render(obj_vec game_objects) 
{
	ClearScreen();
	std::for_each(game_objects.begin(), game_objects.end(), [] (IGameObject* obj) { obj->Render(renderer); });
	SDL_RenderPresent(renderer);
}

void HandleInput(Block &block) 
{
	SDL_Event e;

	while (SDL_PollEvent(&e) != 0)
	{
		if (e.type == SDL_QUIT)
		{
			quit = true;
		} 
		else if (e.type == SDL_KEYDOWN && key_lifted)
		{
			key_lifted = false;
			if (e.key.keysym.sym == SDLK_LEFT)
			{
				block.MoveLaterally(-1);
			} 
			else if (e.key.keysym.sym == SDLK_RIGHT) 
			{
				block.MoveLaterally(1);
			}
		} 
		else if (e.type == SDL_KEYUP) {
			key_lifted = true;
		}
	}
}

void ClearScreen() 
{
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear(renderer);
}