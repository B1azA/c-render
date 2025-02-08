#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL_events.h>
#include <SDL_log.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_scancode.h>
#include <SDL_video.h>

#include <cglm/affine.h>
#include <cglm/mat4.h>
#include <cglm/struct.h>
#include <cglm/types.h>
#include <cglm/vec3.h>
#include <cglm/vec4.h>

#include "app.c"
#include "c-render/pixels.h"

#define HEIGHT 64

int main(int argc, char *argv[]) {

	// returns zero on success else non-zero
	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		printf("error initializing SDL: %s\n", SDL_GetError());
	}

	int windowWidth = 800;
	int windowHeight = 600;
#ifndef NDEBUG
	SDL_Window *window = SDL_CreateWindow(
		"C-rend", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowWidth,
		windowHeight, SDL_WINDOW_RESIZABLE | SDL_WINDOW_UTILITY);
#else
	SDL_Window *window = SDL_CreateWindow("C-rend", SDL_WINDOWPOS_CENTERED,
										  SDL_WINDOWPOS_CENTERED, windowWidth,
										  windowHeight, SDL_WINDOW_RESIZABLE);
#endif
	SDL_Renderer *renderer =
		SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	int pixelsWidth =
		((float)windowWidth / (float)windowHeight) * (float)HEIGHT;
	int pixelsHeight = HEIGHT;

	SDL_Texture *texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
											 SDL_TEXTUREACCESS_STREAMING,
											 pixelsWidth, pixelsHeight);

	Color initColor = {255, 255, 0, 255};
	Pixels pixels = CR_PixelsCreate(initColor, pixelsWidth, pixelsHeight);

	bool close = false;
	int resized = 0;

	App app = appCreate();

	// time - last, now - used to calculate deltaTime
	uint64_t now = SDL_GetPerformanceCounter();
	uint64_t last = 0;
	while (!close) {
		// process events
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_QUIT:
				close = true;
				break;
			case SDL_KEYDOWN:
				// keyboard API for key pressed
				switch (event.key.keysym.scancode) {
				case SDL_SCANCODE_ESCAPE:
					close = true;
					break;
				case SDL_SCANCODE_W:
					SDL_Log("hello");
					break;
				default:
					break;
				}
			case SDL_WINDOWEVENT:
				switch (event.window.event) {
				case SDL_WINDOWEVENT_RESIZED: {
					resized += 1;
					windowWidth = event.window.data1;
					windowHeight = event.window.data1;
					int newWidth = ((float)event.window.data1 /
									(float)event.window.data2) *
								   (float)HEIGHT;
					int newHeight = HEIGHT;
					CR_PixelsResize(&pixels, newWidth, newHeight);
					SDL_DestroyTexture(texture);
					texture =
						SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA32,
										  SDL_TEXTUREACCESS_STREAMING,
										  pixels.width, pixels.height);
				} break;
				}
				break;
			}
		}

		last = now;
		now = SDL_GetPerformanceCounter();

		// time elapsed from last iteration
		double deltaTime =
			(double)(now - last) * 1000 / (double)SDL_GetPerformanceFrequency();

		appUpdate(&app, deltaTime, pixels.width, pixels.height);

		// render
		appRender(&app, &pixels);
		SDL_UpdateTexture(texture, NULL, pixels.pixelData, pixels.width * 4);
		SDL_RenderCopy(renderer, texture, NULL, NULL);

		SDL_RenderPresent(renderer);
	}

	CR_PixelsDestroy(&pixels);
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return EXIT_SUCCESS;
}
