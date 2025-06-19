#include "sdl.h"
#include "util.h"
#include "constants.h"

Video Video_Init(void) {
	Video ret;

	// initialise SDL2
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		FATAL("Failed to initialise SDL2");
	}

	ret.windowSize = (Vec2) {720, 400};

	ret.window = SDL_CreateWindow(
		APP_NAME, ret.windowSize.x, ret.windowSize.y, SDL_WINDOW_RESIZABLE
	);

	if (ret.window == NULL) {
		FATAL("Failed to create window");
	}

	ret.renderer = SDL_CreateRenderer(ret.window, NULL);

	if (ret.renderer == NULL) {
		FATAL("Failed to create renderer");
	}

	SDL_SetRenderVSync(ret.renderer, 1);

	printf("Renderer: %s\n", SDL_GetRendererName(ret.renderer));

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

void Video_OpenFont(Video* video, char* path) {
	SDL_Surface* surface = SDL_LoadBMP(path);

	if (surface == NULL) {
		Error("Failed to open font '%s': %s", path, SDL_GetError());
	}

	video->font = SDL_CreateTextureFromSurface(video->renderer, surface);

	if (video->font == NULL) {
		FATAL("Failed to open font"); // TODO: make a window for this and reset
	}

	video->charWidth  = surface->w / 16;
	video->charHeight = surface->h / 16;

	printf("Loaded %dx%d font\n", video->charWidth, video->charHeight);

	SDL_DestroySurface(surface);

	SDL_SetWindowMinimumSize(
		video->window, 21 * video->charWidth, 3 * video->charHeight
	);
}

void Video_DrawCharacter(Video* video, int x, int y, uchar ch, SDL_Colour colour) {
	if (ch == ' ') {
		return;
	}

	float fontWFloat;
	SDL_GetTextureSize(video->font, &fontWFloat, NULL); // TODO: is this slow?
	int fontW = (int) fontWFloat;

	SDL_SetTextureColorMod(video->font, colour.r, colour.g, colour.b);

	SDL_FRect src = {
		(float) ((((int) ch) % 16) * video->charWidth),
		(float) ((((int) ch) / 16) * video->charHeight),
		(float) video->charWidth, (float) video->charHeight
	};
	SDL_FRect dest = {
		(float) x, (float) y, (float) video->charWidth, (float) video->charHeight
	};

	SDL_RenderTexture(video->renderer, video->font, &src, &dest);
}
