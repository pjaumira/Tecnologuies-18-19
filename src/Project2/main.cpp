//SDL includes
#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>

// includes normals
#include <exception>
#include <iostream>
#include <string>

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

// Main
int main(int, char*[]) 
{
	// --- INIT SDL ---
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) 
		throw "No es pot inicialitzar SDL subsystems";

	// --- WINDOW ---
	SDL_Window *m_window{ SDL_CreateWindow("SDL...", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN) };
	if (m_window == nullptr) 
		throw "No es pot inicialitzar SDL_Window";

	// --- RENDERER ---
	SDL_Renderer *m_renderer{ SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC) };
	if (m_renderer == nullptr) 
		throw "No es pot inicialitzar SDL_Renderer";

	//-->SDL_Image 
	const Uint8 imgFlags{ IMG_INIT_PNG | IMG_INIT_JPG };
	if (!(IMG_Init(imgFlags) & imgFlags)) throw "Error: SDL_image init";

	//-->SDL_TTF
	if (TTF_Init() != 0) throw "No es pot inicialitzar les fonts";

	//-->SDL_Mix


	// --- SPRITES ---

		//Background
		SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg") };
		if (bgTexture == nullptr) throw "Error: bgTexture init";
		SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

		//Player Cursor
		SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer,"../../res/img/kintoun.png")};
		if (playerTexture == nullptr) throw "Error: PlayerTexture init";
		SDL_Rect playerRect{ 0,0, 350, 189 };
		SDL_Rect playerTarget{ 0,0,100,100 };

	//-->Animated Sprite ---


	// --- TEXT ---
		TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",80) };
		if (font == nullptr) throw "no trobo la font";
		SDL_Surface *tmpSurf{ TTF_RenderText_Blended(font, "My first SDL Game", SDL_Color{216,255,202,255}) };
		if (tmpSurf == nullptr) throw "no puc fer surface";
		SDL_Texture *textTexture{ SDL_CreateTextureFromSurface(m_renderer, tmpSurf)};
		SDL_Rect textRect{ 100,50, tmpSurf->w, tmpSurf->h };
		SDL_FreeSurface(tmpSurf);
		TTF_CloseFont(font);

	// --- AUDIO ---


	// --- GAME LOOP ---
	SDL_Event event;
	bool isRunning = true;
	while (isRunning) {
		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) { // per poder cargar totes els ordres rebudes del stack
			switch (event.type) {
			case SDL_QUIT:		
				isRunning = false; 
				break;
			case SDL_KEYDOWN:	
				if (event.key.keysym.sym == SDLK_ESCAPE) isRunning = false; 
				break;
			case SDL_MOUSEMOTION:
				playerTarget.x = event.motion.x -50; 
				playerTarget.y = event.motion.y -50;
				break;
			default:;
			}
		}

		// UPDATE
		playerRect.x += (playerTarget.x - playerRect.x) / 10;
		playerRect.y += (playerTarget.y - playerRect.y) / 10;

		// DRAW
		SDL_RenderClear(m_renderer);
			//Background
			SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
			//Player
			SDL_RenderCopy(m_renderer,playerTexture , nullptr, &playerRect);
			//Text
			SDL_RenderCopy(m_renderer, textTexture, nullptr, &textRect);
		SDL_RenderPresent(m_renderer);
	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(textTexture);
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();
	TTF_Quit();

	return 0;
}