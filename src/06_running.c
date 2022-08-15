#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define WIDTH 800
#define HEIGHT 600
#define HERO_WALK_RATE 10
#define IMG_PATH "assets/hero_spritesheet.png"

typedef struct
{
	int x;
	int y;
	int w;
	int h;
	int state;
	SDL_Texture *sprite;
	SDL_Rect walking[6];
} HERO;

void print_hero(HERO *, SDL_Renderer *);
void move_hero(HERO *, int, int, int, int);
void initialize_hero(HERO *, SDL_Renderer *, SDL_Texture *);

int main (int argc, char *argv[])
{
	// variable declarations
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *img = NULL;
	
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
			return 1;
	
	// create the window and renderer
	// note that the renderer is accelerated
	win = SDL_CreateWindow("Image Loading", 100, 100, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);

	HERO hero;
	initialize_hero(&hero, renderer, img);

	// main loop
	while (1) {
		
		// event handling
		SDL_Event e;
		if(SDL_PollEvent(&e))
        {
			if (e.type == SDL_QUIT)
				break;
			else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_w)
				move_hero(&hero, 1, 0, 0, 0);
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_s)
				move_hero(&hero, 0, 1, 0, 0);
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_a)
				move_hero(&hero, 0, 0, 1, 0);
			else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_d)
				move_hero(&hero, 0, 0, 0, 1);
		} 
		
		// clear the screen
		SDL_RenderClear(renderer);
		// copy the texture to the rendering context
		//SDL_RenderCopy(renderer, img, NULL, &texr);

		print_hero(&hero, renderer);

		// flip the backbuffer
		// this means that everything that we prepared behind the screens is actually shown
		SDL_RenderPresent(renderer);
	}
	
	SDL_DestroyTexture(img);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);
	
	return 0;
}

void initialize_hero(HERO *hero, SDL_Renderer *renderer, SDL_Texture *img)
{
	int w, h; // texture width & height
	// load our image
	img = IMG_LoadTexture(renderer, IMG_PATH);

    // get the width and height of the texture
	// put the location where we want the texture to be drawn into a rectangle
	// I'm also scaling the texture 2x simply by setting the width and height
	SDL_QueryTexture(img, NULL, NULL, &w, &h); 

	// position start
	hero->x = 200;
	hero->y = 200;
	hero->sprite = img;

	hero->w = w;
	hero->h = h;
	hero->state = 0;

	for(int i = 0; i < 6; i++)
	{
		SDL_Rect s_react; 
		s_react.x = (hero->w / 8) * i; 
		s_react.y = hero->h / 5;
		s_react.w = hero->w / 8; 
		s_react.h = hero->h / 5; 
		hero->walking[i] = s_react;
	}
}

void move_hero(HERO *hero, int up, int down, int left, int right)
{
	hero->y -= up * HERO_WALK_RATE;
	hero->y += down * HERO_WALK_RATE;
	hero->x -= left * HERO_WALK_RATE;
	hero->x += right * HERO_WALK_RATE;
	hero->state += 1;
	if(hero->state > 5)
		hero->state = 0;
}

void print_hero(HERO *hero, SDL_Renderer *renderer)
{
	SDL_Rect s_react; 
	s_react.x = 0; 
	s_react.y = 0;
	s_react.w = hero->w / 8; 
	s_react.h = hero->h / 5; 

	SDL_Rect d_react; 
	d_react.x = hero->x; 
	d_react.y = hero->y;
	d_react.w = hero->w / 8; 
	d_react.h = hero->h / 5; 

	SDL_RenderCopy(renderer, hero->sprite, &(hero->walking[hero->state]), &d_react);
}