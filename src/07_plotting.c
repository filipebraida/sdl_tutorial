#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#define MAX_INIMIGO 100

#define WIDTH 800
#define HEIGHT 600

//https://opengameart.org/content/2d-hero
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
} INIMIGO;

typedef struct
{
	INIMIGO *vetor[MAX_INIMIGO];
	int total;
} VETOR_INIMIGOS;

VETOR_INIMIGOS* criar_inimigos();
INIMIGO* get_inimigo(VETOR_INIMIGOS *, int);
void adiciona_inimigos(VETOR_INIMIGOS *, INIMIGO *);
void adiciona_inimigo_aleatorio(VETOR_INIMIGOS *, SDL_Renderer *, SDL_Texture *);
void carregar_inimigos(VETOR_INIMIGOS *,SDL_Renderer *, SDL_Texture *);
void imprimir_inimigos(VETOR_INIMIGOS *, SDL_Renderer *);
void animar_inimigos(VETOR_INIMIGOS *);
void destroi_inimigos(VETOR_INIMIGOS *);

INIMIGO* criar_inimigo(SDL_Renderer *, SDL_Texture *, int, int);
void imprimir_inimigo(INIMIGO *, SDL_Renderer *);
void animar_inimigo(INIMIGO *);
void destroi_inimigo(INIMIGO *);

int main(void)
{
    // variable declarations
	SDL_Window *win = NULL;
	SDL_Renderer *renderer = NULL;
	SDL_Texture *img_inimigo = NULL;
	
	// Initialize SDL.
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;
	
	// create the window and renderer
	// note that the renderer is accelerated
	win = SDL_CreateWindow("Image Loading", 100, 100, WIDTH, HEIGHT, 0);
	renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // load our image
	img_inimigo = IMG_LoadTexture(renderer, IMG_PATH);

	VETOR_INIMIGOS *p_inimigos = criar_inimigos();
	carregar_inimigos(p_inimigos, renderer, img_inimigo);

    // main loop
	while (1) {
		int tempo_inicial = SDL_GetTicks();
		// event handling
		SDL_Event e;
		if(SDL_PollEvent(&e))
        {
			if (e.type == SDL_QUIT)
				break;
            else if (e.type == SDL_KEYUP && e.key.keysym.sym == SDLK_ESCAPE)
				break;
            else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_c)
				adiciona_inimigo_aleatorio(p_inimigos, renderer, img_inimigo);
		} 
		
		// clear the screen
		SDL_RenderClear(renderer);
		// copy the texture to the rendering context
		//SDL_RenderCopy(renderer, img, NULL, &texr);

        animar_inimigos(p_inimigos);

        imprimir_inimigos(p_inimigos, renderer);

		// flip the backbuffer
		// this means that everything that we prepared behind the screens is actually shown
		SDL_RenderPresent(renderer);

        int tempo_decorrido = SDL_GetTicks() - tempo_inicial;

        if (tempo_decorrido < 33) 
        {
            int diff = 33 - tempo_decorrido;
            SDL_Delay(diff);
        }
        else 
        {
            SDL_Delay(1);
        }
	}

	destroi_inimigos(p_inimigos);

    SDL_DestroyTexture(img_inimigo);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(win);

	return 0;
}

void carregar_inimigos(VETOR_INIMIGOS *p_inimigos, SDL_Renderer *renderer, SDL_Texture *img)
{
	adiciona_inimigo_aleatorio(p_inimigos, renderer, img);
}

void adiciona_inimigo_aleatorio(VETOR_INIMIGOS *p_inimigos, SDL_Renderer *renderer, SDL_Texture *img)
{
    int x = rand() % WIDTH;
    int y = rand() % HEIGHT;
    adiciona_inimigos(p_inimigos, criar_inimigo(renderer, img, x, y));
}

void adiciona_inimigos(VETOR_INIMIGOS *p_inimigos, INIMIGO *inimigo)
{
    if(p_inimigos->total < MAX_INIMIGO)
    {
        p_inimigos->vetor[p_inimigos->total] = inimigo;
        p_inimigos->total++;
    }
}

INIMIGO* get_inimigo(VETOR_INIMIGOS *p_inimigos, int posicao)
{
	return p_inimigos->vetor[posicao];
}

void imprimir_inimigos(VETOR_INIMIGOS *p_inimigos, SDL_Renderer *renderer)
{
    for(int w = 0; w < p_inimigos->total; w++)
    {
        imprimir_inimigo(p_inimigos->vetor[w], renderer);
    }
}

void imprimir_inimigo(INIMIGO *inimigo, SDL_Renderer *renderer)
{
	SDL_Rect d_react; 
	d_react.x = inimigo->x; 
	d_react.y = inimigo->y;
	d_react.w = inimigo->w / 8; 
	d_react.h = inimigo->h / 5; 

	SDL_RenderCopy(renderer, inimigo->sprite, &(inimigo->walking[inimigo->state]), &d_react);
}

VETOR_INIMIGOS* criar_inimigos()
{
	VETOR_INIMIGOS *p;
	p = (VETOR_INIMIGOS *) malloc(sizeof(VETOR_INIMIGOS));
	p->total = 0;

	return p;
}

void destroi_inimigos(VETOR_INIMIGOS *p)
{
    for(int w = 0; w < p->total; w++)
    {
        destroi_inimigo(p->vetor[w]);
    }

	free(p);
}

void destroi_inimigo(INIMIGO *p)
{
    free(p);
}


INIMIGO* criar_inimigo(SDL_Renderer *renderer, SDL_Texture *img, int x, int y)
{
    INIMIGO *inimigo;
    inimigo = (INIMIGO *) malloc(sizeof(INIMIGO));

	int w, h; // texture width & height

    // get the width and height of the texture
	// put the location where we want the texture to be drawn into a rectangle
	// I'm also scaling the texture 2x simply by setting the width and height
	SDL_QueryTexture(img, NULL, NULL, &w, &h); 

	// position start
	inimigo->x = x;
	inimigo->y = y;
	inimigo->sprite = img;

	inimigo->w = w;
	inimigo->h = h;
	inimigo->state = 0;

	for(int i = 0; i < 6; i++)
	{
		SDL_Rect s_react; 
		s_react.x = (inimigo->w / 8) * i; 
		s_react.y = inimigo->h / 5;
		s_react.w = inimigo->w / 8; 
		s_react.h = inimigo->h / 5; 
		inimigo->walking[i] = s_react;
	}

    return inimigo;
}

void animar_inimigos(VETOR_INIMIGOS *p_inimigos)
{
    for(int i = 0; i < p_inimigos->total; i++)
    {
        animar_inimigo(p_inimigos->vetor[i]);
    }
}

void animar_inimigo(INIMIGO *inimigo)
{
	inimigo->state += 1;
	if(inimigo->state > 5)
		inimigo->state = 0;
}