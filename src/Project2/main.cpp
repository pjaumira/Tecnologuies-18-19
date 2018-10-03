//SDL includes
#include <SDL.h>		// Always needs to be included for an SDL app
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

// includes normals
#include <exception>
#include <iostream>
#include <string>
#include <time.h>

//Game general information
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define FPS 60
#define DELAY_TIME 1000.0f / FPS

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
	const Uint8 mixFlags{ MIX_INIT_MP3 | MIX_INIT_OGG };
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	if (SDL_INIT_AUDIO < 0) throw "No es pot inicilaitzar l audio";

	// --- SPRITES ---

		//Background
		SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg")};
		if (bgTexture == nullptr) throw "Error: bgTexture init";
		SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

		//Player Cursor
		SDL_Texture *mouseTexture{ IMG_LoadTexture(m_renderer,"../../res/img/kintoun.png") };
		if (mouseTexture == nullptr) throw "Error: PlayerTexture init";
		SDL_Rect mouseRect{ 0,0, 90, 60 };
		SDL_Rect mouseTarget{ 0,0,80,80 };

	//-->Animated Sprite ---
		SDL_Texture *playerTexture{ IMG_LoadTexture(m_renderer, "../../res/img/sdp01.png") };
		SDL_Rect playerRect, playerPosition;
		int textwidth, textheight, framewidth, frameheight;
		SDL_QueryTexture(playerTexture, NULL, NULL, &textwidth, &textheight);
		framewidth = textwidth / 6;
		frameheight = textheight / 1;
		playerPosition.x = playerPosition.y = 0;
		playerRect.x = playerRect.y = 0;
		playerPosition.h = playerRect.h = frameheight;
		playerPosition.w = playerRect.w = frameheight;
		int frametime = 0;

	// --- TEXT ---
		TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",80) };
		if (font == nullptr) throw "no trobo la font";

		//Play
		SDL_Surface *tmpSurfP{ TTF_RenderText_Blended(font, "Play", SDL_Color{ 50,100,200,255 }) };
		if (tmpSurfP == nullptr) throw "no puc fer surface P";
		SDL_Texture *textTextureP{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfP) };
		SDL_Rect textRectP{ 340,75, tmpSurfP->w, tmpSurfP->h };
		SDL_FreeSurface(tmpSurfP);

		//Sound
		SDL_Surface *tmpSurfS{ TTF_RenderText_Blended(font, "Sound ON", SDL_Color{116,25,20,255}) };
		if (tmpSurfS == nullptr) throw "no puc fer surface S";
		SDL_Texture *textTextureS{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfS) };
		SDL_Rect textRectS{ 280,200, tmpSurfS->w, tmpSurfS->h };
		SDL_FreeSurface(tmpSurfS);

		//Quit
		SDL_Surface *tmpSurfQ{ TTF_RenderText_Blended(font, "Quit", SDL_Color{ 200,100,100,255 }) };
		if (tmpSurfQ == nullptr) throw "no puc fer surface Q";
		SDL_Texture *textTextureQ{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfQ) };
		SDL_Rect textRectQ{ 330,325, tmpSurfQ->w, tmpSurfQ->h };
		SDL_FreeSurface(tmpSurfQ);

		//Fin
		TTF_CloseFont(font);

	// --- AUDIO ---
		Mix_Music *ost = Mix_LoadMUS("../../res/au/mainTheme.mp3");
		if (!ost) throw "error finding the music";
		Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
		Mix_PlayMusic(ost, -1);

	// Time
		clock_t lastTime = clock();
		float timeDown = 10.;
		float deltaTime = 0;
		Uint32 frameStart, frameTime;

	// --- GAME LOOP ---
	SDL_Event event;
	frameStart = SDL_GetTicks();
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
				mouseTarget.x = event.motion.x -30; 
				mouseTarget.y = event.motion.y -30;
				break;
			case SDL_MOUSEBUTTONDOWN:
				break;
			default:;
			}
		}

		// UPDATE
		mouseRect.x += (mouseTarget.x - mouseRect.x) / 10;
		mouseRect.y += (mouseTarget.y - mouseRect.y) / 10;
		frametime++;
		if (FPS / frametime <= 9) {
			frametime = 0;
			playerRect.x += framewidth;
			if (playerRect.x >= textwidth)
				playerRect.x = 0;
		}
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		std::cout << timeDown << std::endl;
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) {
			SDL_Delay((int)(DELAY_TIME - frameTime));
		}

		// DRAW
		SDL_RenderClear(m_renderer);
		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
		//Text
		SDL_RenderCopy(m_renderer, textTextureP, nullptr, &textRectP);
		SDL_RenderCopy(m_renderer, textTextureS, nullptr, &textRectS);
		SDL_RenderCopy(m_renderer, textTextureQ, nullptr, &textRectQ);
		//Player
		SDL_RenderCopy(m_renderer,mouseTexture , nullptr, &mouseRect);
		SDL_RenderPresent(m_renderer);
		SDL_RenderCopy(m_renderer, playerTexture, &playerRect, &playerPosition);
	}

	// --- DESTROY ---
	SDL_DestroyTexture(bgTexture);
	SDL_DestroyTexture(playerTexture);
	SDL_DestroyTexture(textTextureP);
	SDL_DestroyTexture(textTextureQ);
	SDL_DestroyTexture(textTextureS);
	Mix_CloseAudio();
	IMG_Quit();
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);

	// --- QUIT ---
	SDL_Quit();
	TTF_Quit();
	Mix_Quit();

	return 0;
}