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

		//Background Scene 1
		SDL_Texture* bgTexture{ IMG_LoadTexture(m_renderer, "../../res/img/bg.jpg")};
		if (bgTexture == nullptr) throw "Error: bgTexture init";
		SDL_Rect bgRect{ 0,0,SCREEN_WIDTH, SCREEN_HEIGHT };

		//Background Scene 2
		SDL_Texture* bgTextureC{ IMG_LoadTexture(m_renderer, "../../res/img/bgCastle.jpg") };
		if (bgTexture == nullptr) throw "Error: bgTexture init";

		//Player Cursor
		SDL_Texture *mouseTexture{ IMG_LoadTexture(m_renderer,"../../res/img/kintoun.png") };
		if (mouseTexture == nullptr) throw "Error: MouseTexture init";
		SDL_Rect mouseRect{ 0,0, 90, 60 };
		SDL_Rect mouseTarget{ 0,0,80,80 };

	//-->Animated Sprite ---

		//Player1
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

		//Player2

	// --- TEXT ---
		TTF_Font *font{ TTF_OpenFont("../../res/ttf/saiyan.ttf",80) };
		if (font == nullptr) throw "no trobo la font";

		//Play
		SDL_Surface *tmpSurfP{ TTF_RenderText_Blended(font, "Play", SDL_Color{ 50,100,200,255 }) };
		if (tmpSurfP == nullptr) throw "no puc fer surface P";
		SDL_Texture *textTextureP{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfP) };
		SDL_Rect textRectP{ 340,75, tmpSurfP->w, tmpSurfP->h };

		// Play Hover
		SDL_Surface *tmpSurfPH{ TTF_RenderText_Blended(font, "Play", SDL_Color{ 150,190,20,255 }) };
		if (tmpSurfPH == nullptr) throw "no puc fer surface PH";
		SDL_Texture *textTexturePH{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfPH) };

		//Play not Hover
		SDL_Surface *tmpSurfPNH{ TTF_RenderText_Blended(font, "Play", SDL_Color{ 50,100,200,255 }) };
		if (tmpSurfPNH == nullptr) throw "no puc fer surface PNH";
		SDL_Texture *textTexturePNH{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfPNH) };

		//Sound ON
		SDL_Surface *tmpSurfS{ TTF_RenderText_Blended(font, "Sound ON", SDL_Color{16,255,20,255}) };
		if (tmpSurfS == nullptr) throw "no puc fer surface S";
		SDL_Texture *textTextureS{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfS) };
		SDL_Rect textRectS{ 280,200, tmpSurfS->w, tmpSurfS->h };

		// Sound OFF
		SDL_Surface *tmpSurfSF{ TTF_RenderText_Blended(font, "Sound OFF", SDL_Color{ 255,25,20,255 }) };
		if (tmpSurfSF == nullptr) throw "no puc fer surface SF";
		SDL_Texture *textTextureSF{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfSF) };

		//Sound Normal
		SDL_Surface *tmpSurfSN{ TTF_RenderText_Blended(font, "Sound ON", SDL_Color{ 16,255,20,255 }) };
		if (tmpSurfSN == nullptr) throw "no puc fer surface SN";
		SDL_Texture *textTextureSN{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfSN) };

		//Quit
		SDL_Surface *tmpSurfQ{ TTF_RenderText_Blended(font, "Quit", SDL_Color{ 230,100,100,255 }) };
		if (tmpSurfQ == nullptr) throw "no puc fer surface Q";
		SDL_Texture *textTextureQ{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfQ) };
		SDL_Rect textRectQ{ 330,325, tmpSurfQ->w, tmpSurfQ->h };

		// Quit Hover
		SDL_Surface *tmpSurfQH{ TTF_RenderText_Blended(font, "Quit", SDL_Color{ 255,255,255,255 }) };
		if (tmpSurfQH == nullptr) throw "no puc fer surface QH";
		SDL_Texture *textTextureQH{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfQH) };

		// Quit No Hover
		SDL_Surface *tmpSurfQNH{ TTF_RenderText_Blended(font, "Quit", SDL_Color{ 230,100,100,255 }) };
		if (tmpSurfQNH == nullptr) throw "no puc fer surface QNH";
		SDL_Texture *textTextureQNH{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfQNH) };

		//Comptador Jugador 1
		SDL_Surface *tmpSurfC1{ TTF_RenderText_Blended(font, "Punts P1", SDL_Color{ 255,10,10,255 }) };
		if (tmpSurfC1 == nullptr) throw "no puc fer surface C1";
		SDL_Texture *textTextureC1{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfC1) };
		SDL_Rect textRectC1{ 10,10, tmpSurfC1->w, tmpSurfC1->h };
		SDL_FreeSurface(tmpSurfC1);

		//Comptador Jugador 2
		SDL_Surface *tmpSurfC2{ TTF_RenderText_Blended(font, "Punts P2", SDL_Color{ 255,10,10,255 }) };
		if (tmpSurfC2 == nullptr) throw "no puc fer surface C2";
		SDL_Texture *textTextureC2{ SDL_CreateTextureFromSurface(m_renderer, tmpSurfC2) };
		SDL_Rect textRectC2{ 10,10, tmpSurfC2->w, tmpSurfC2->h };
		SDL_FreeSurface(tmpSurfC2);

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

	//boolea per les tecles i events
	bool isRunning = true;
	while (isRunning) {

		struct vect2 {
			int x;
			int y;
		};

		bool sound = true;
		int Scene = 1;

		vect2 mouseCoord;
		mouseCoord.x = 0;
		mouseCoord.y = 0;

		//init bollean array
		bool key[10] = {};
		for (int i = 0; i > 9;i++) {
			key[i] = false;
		};

		// HANDLE EVENTS
		while (SDL_PollEvent(&event)) { // per poder cargar totes els ordres rebudes del stack
			switch (event.type) {
			case SDL_QUIT:		
				isRunning = false; 
				break;
			case SDL_KEYDOWN:
				//Esc tenca la pantalla
				if (event.key.keysym.sym == SDLK_ESCAPE) key[0] = true;
				//Controls Player 1
				if (event.key.keysym.sym == SDLK_UP) key[1] = true;
				if (event.key.keysym.sym == SDLK_DOWN) key[2] = true;
				if (event.key.keysym.sym == SDLK_LEFT) key[3] = true;
				if (event.key.keysym.sym == SDLK_RIGHT) key[4] = true;
				// Controls Player 2
				if (event.key.keysym.sym == SDLK_ESCAPE) key[5] = true;
				if (event.key.keysym.sym == SDLK_ESCAPE) key[6] = true;
				if (event.key.keysym.sym == SDLK_ESCAPE) key[7] = true;
				if (event.key.keysym.sym == SDLK_ESCAPE) key[8] = true;
				break;
			case SDL_MOUSEMOTION:
				mouseTarget.x = event.motion.x -30; 
				mouseTarget.y = event.motion.y -30;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT) key[9] = true;
				SDL_GetMouseState(&mouseCoord.x, &mouseCoord.y);
				break;
			default:;
			}
		}

		// UPDATE

		if (key[0] == true) isRunning = false;

		mouseRect.x += (mouseTarget.x - mouseRect.x) / 10;
		mouseRect.y += (mouseTarget.y - mouseRect.y) / 10;
		frametime++;
		if (FPS / frametime <= 9) {
			frametime = 0;
			playerRect.x += framewidth;
			if (playerRect.x >= textwidth)
				playerRect.x = 0;
		};
		deltaTime = (clock() - lastTime);
		lastTime = clock();
		deltaTime /= CLOCKS_PER_SEC;
		timeDown -= deltaTime;
		std::cout << timeDown << std::endl;
		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME) {
			SDL_Delay((int)(DELAY_TIME - frameTime));
		};

		//Si es la escena del menu
			//hover events
			if (mouseTarget.x >= textRectP.x && mouseTarget.x <= textRectP.x + textRectP.w && mouseTarget.y >= textRectP.y && mouseTarget.y <= textRectP.y + textRectP.h) {
				textTextureP = textTexturePH;
				SDL_FreeSurface(tmpSurfP);
			}
			else {
				textTextureP = textTexturePNH;
				SDL_FreeSurface(tmpSurfP);
			};

			if (mouseTarget.x >= textRectQ.x && mouseTarget.x <= textRectQ.x + textRectQ.w && mouseTarget.y >= textRectQ.y && mouseTarget.y <= textRectQ.y + textRectQ.h) {
				textTextureQ = textTextureQH;
				SDL_FreeSurface(tmpSurfQ);
			}
			else {
				textTextureQ = textTextureQNH;
				SDL_FreeSurface(tmpSurfQ);
			};

			//eventos de apretar
			if (mouseCoord.x >= textRectS.x && mouseCoord.x <= textRectS.x + textRectS.w && mouseCoord.y >= textRectS.y && mouseCoord.y <= textRectS.y + textRectS.h) {
				if (Mix_PlayingMusic) {
					Mix_PauseMusic();
					textTextureS = textTextureSF;
					SDL_FreeSurface(tmpSurfS);
				};
				if (!Mix_PlayingMusic) {
					Mix_ResumeMusic;
					textTextureS = textTextureSN;
					SDL_FreeSurface(tmpSurfS);
				};
			};

			if (mouseCoord.x >= textRectQ.x && mouseCoord.x <= textRectQ.x + textRectQ.w && mouseCoord.y >= textRectQ.y && mouseCoord.y <= textRectQ.y + textRectQ.h) {
				isRunning = false;
			};

		if (mouseCoord.x >= textRectP.x && mouseCoord.x <= textRectP.x + textRectP.w && mouseCoord.y >= textRectP.y && mouseCoord.y <= textRectP.y + textRectP.h) {
			Scene = 2;
		};

		//Si es la escena de joc
		if (Scene == 2) {
			bgTexture = bgTextureC;
			textTextureP = nullptr;
			textTexturePH = nullptr;
			textTexturePNH = nullptr;
			textTextureS = nullptr;
			textTextureQ = nullptr;
			textTextureQH = nullptr;
			textTextureQNH = nullptr;
			mouseTexture = nullptr;


		};

		// DRAW
		SDL_RenderClear(m_renderer);
		//Background
		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
		//Text
		SDL_RenderCopy(m_renderer, playerTexture, &playerRect, &playerPosition);
		SDL_RenderCopy(m_renderer, textTextureP, nullptr, &textRectP);
		SDL_RenderCopy(m_renderer, textTextureS, nullptr, &textRectS);
		SDL_RenderCopy(m_renderer, textTextureQ, nullptr, &textRectQ);
		//Mouse Scene 1
		SDL_RenderCopy(m_renderer,mouseTexture , nullptr, &mouseRect);
		SDL_RenderPresent(m_renderer);
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