#include <SDL2/SDL.h>  
#include <SDL2/SDL_image.h>

int main(void)
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* janela;
	janela = SDL_CreateWindow("joguinho", 500, 500, 640, 480, SDL_WINDOW_RESIZABLE);

	int jogando = 1;

	SDL_Renderer* renderer = SDL_CreateRenderer(janela, -1, 0);
	
	// Game loop
	while (jogando == 1)
	{
		SDL_SetRenderDrawColor(renderer, 111, 133, 255, 255); // Definindo a cor do fundo
		SDL_RenderClear(renderer); // Limpando o renderer
		
		// Desenhando no renderer
		// seu joguinho aqui
		
		// Apresentando o renderer
		SDL_RenderPresent(renderer);

		// Cria Pilha de eventos
		SDL_Event evento; 

		// Enquanto houver eventos...
		while(SDL_PollEvent(&evento)) 
		{
			// Se tentar fechar a janela do jogo...
			// Encerre o Game Loop.
			if(evento.type == SDL_QUIT)
				jogando = 0;
			
			// Se uma tecla for pressionada...
			if (evento.type == SDL_KEYDOWN)
			{ 
				        printf("Key %d ('%c') is stuck. Press and release it.\n", key, key);
				// Caso seja ESC...
				if (evento.key.keysym.sym == SDLK_ESCAPE)
				{
					jogando = 0;
				} 
			}
		}
	}

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(janela);

	SDL_Quit();

	return 0;
}