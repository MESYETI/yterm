#include "sdl.h"
#include "util.h"
#include "constants.h"

Video Video_Init(void) {
	Video ret;

	// initialise SDL2
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		FATAL("Failed to initialise SDL2");
	}

	ret.windowSize = (Vec2) {720, 400};

	ret.window = SDL_CreateWindow(
		APP_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		ret.windowSize.x, ret.windowSize.y, SDL_WINDOW_RESIZABLE
	);

	if (ret.window == NULL) {
		FATAL("Failed to create window");
	}

	ret.renderer = SDL_CreateRenderer(
		ret.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
	);

	if (ret.renderer == NULL) {
		FATAL("Failed to create renderer");
	}

	ret.font = NULL;
	return ret;
}

void Video_FreeFont(Video* video) {
	SDL_DestroyTexture(video->font);
}

void Video_Free(Video* video) {
	Video_FreeFont(video);
	
	SDL_DestroyWindow(video->window);
	SDL_DestroyRenderer(video->renderer);
	SDL_Quit();
}

void Video_OpenFont(Video* video, char* path, int charWidth, int charHeight) {
	SDL_Surface* surface = SDL_LoadBMP(path);

	if (surface == NULL) {
		FATAL("Failed to open font");
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(video->renderer, surface);

	if (texture == NULL) {
		FATAL("Failed to create texture");
	}

	SDL_FreeSurface(surface);

	SDL_SetWindowMinimumSize(
		video->window, 21 * video->charWidth, 3 * video->charHeight
	);

	video->charWidth  = charWidth;
	video->charHeight = charHeight;
}

void Video_DrawCharacter(Video* video, int x, int y, uchar ch, SDL_Colour colour) {
	if (ch == ' ') {
		return;
	}

	int fontW;
	int fontH;
	SDL_QueryTexture(video->font, NULL, NULL, &fontW, &fontH); // TODO: is this slow?

	//SDL_SetTextureColorMod(video->font, colour.r, colour.g, colour.b);

	SDL_Rect src = {
		(((int) ch) % (fontW / video->charWidth)) * video->charWidth,
		(((int) ch) / (fontW / video->charHeight)) * video->charHeight,
		video->charWidth, video->charHeight
	};
	SDL_Rect dest = {
		x, y, video->charWidth, video->charHeight
	};

	SDL_RenderCopy(video->renderer, video->font, &src, &dest);
}
