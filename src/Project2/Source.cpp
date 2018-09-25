#include <SDL_image.h>

int main(int argc, char *argv[]) {
	bool quit = false;
	while (!quit) {

		SDL_Renderer *m_renderer = nullptr;
		SDL_Window *m_window = nullptr;

		// INIT
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) throw "Noes es pot inicialitzar SDL";

		//WINDOW
		m_window = SDL_CreateWindow("My first SDL Project", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_window == nullptr) throw "No es pot inicialitzar SDL Window";

		// RENDERER
		m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_PRESENTSYNC);
		if (m_renderer == nullptr) throw "No es pot inicialitzar SDL Renderer";

		// Pintar de negre
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);

		//SDL Image
		const Uint8 imgFlags(IMG_INIT_PNG | IMG_INIT_JPG);
		if (!(IMG_Init(imgFlags) & imgFlags)) throw "SDL images peta";

		IMG_Quit();

		//SDL Texture
		SDL_Texture *bgTexture(IMG_LoadTexture(m_renderer, "../../res/img/background.jpg"));
		if (bgTexture == nullptr) throw "No ha trobat la imatge";
		SDL_Rect bgRect{0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

		SDL_RenderCopy(m_renderer, bgTexture, nullptr, &bgRect);
		SDL_RenderPresent(m_renderer);
		SDL_DestroyTexture(bgTexture);

	}
	return 0;
}