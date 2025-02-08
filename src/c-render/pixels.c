#include "pixels.h"
#include <SDL_log.h>
#include <stdint.h>
#include <stdlib.h>

Pixels CR_PixelsCreate(Color initColor, int width, int height) {
	struct Pixels pixels;
	pixels.width = width;
	pixels.height = height;
	pixels.pixelData = malloc(width * height * 4);

	// set all the pixels to the initColor
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {
			pixels.pixelData[4 * x + y * width * 4] = initColor.r;
			pixels.pixelData[4 * x + y * width * 4 + 1] = initColor.g;
			pixels.pixelData[4 * x + y * width * 4 + 2] = initColor.b;
			pixels.pixelData[4 * x + y * width * 4 + 3] = initColor.a;
		}
	}

	return pixels;
}

void CR_PixelsDestroy(Pixels *pixels) { free(pixels->pixelData); }

void CR_PixelsDrawPixel(Pixels *pixels, float x, float y, Color color) {
	// convert from relative (1…-1) to absolute coordinates (real pixels)
	float heightPixels = (float)pixels->height / 2.0;
	float widthPixels =
		(float)pixels->width / (float)pixels->height * heightPixels;

	// real coordinates
	int xCoord = (x + 1) * widthPixels;
	int yCoord = (-y + 1) * heightPixels;

	CR_PixelsDrawRealPixel(pixels, xCoord, yCoord, color);
}

void CR_PixelsDrawRealPixel(Pixels *pixels, int x, int y, Color color) {
	if (x >= 0 && x < pixels->width && y >= 0 && y < pixels->height) {
		pixels->pixelData[4 * x + y * pixels->width * 4] = color.r;
		pixels->pixelData[4 * x + y * pixels->width * 4 + 1] = color.g;
		pixels->pixelData[4 * x + y * pixels->width * 4 + 2] = color.b;
		pixels->pixelData[4 * x + y * pixels->width * 4 + 3] = color.a;
	}
}

void CR_PixelsResize(Pixels *pixels, int newWidth, int newHeight) {
	free(pixels->pixelData);
	pixels->pixelData = malloc(newWidth * newHeight * 4);
	pixels->width = newWidth;
	pixels->height = newHeight;
}

void CR_PixelsClear(Pixels *pixels, Color color) {
	for (int x = 0; x < pixels->width; x++) {
		for (int y = 0; y < pixels->height; y++) {
			pixels->pixelData[4 * x + y * pixels->width * 4] = color.r;
			pixels->pixelData[4 * x + y * pixels->width * 4 + 1] = color.g;
			pixels->pixelData[4 * x + y * pixels->width * 4 + 2] = color.b;
			pixels->pixelData[4 * x + y * pixels->width * 4 + 3] = color.a;
		}
	}
}

void CR_PixelsDrawLine(Pixels *pixels, float x0, float y0, float x1, float y1,
					   Color color) {
	// convert from relative (1…-1) to absolute coordinates (real pixels)
	float heightPixels = (float)pixels->height / 2.0;
	float widthPixels =
		(float)pixels->width / (float)pixels->height * heightPixels;

	// real coordinates
	int x0Coord = (x0 + 1) * widthPixels;
	int y0Coord = (-y0 + 1) * heightPixels;
	int x1Coord = (x1 + 1) * widthPixels;
	int y1Coord = (-y1 + 1) * heightPixels;

	int dx = abs(x1Coord - x0Coord);
	int sx = x0Coord < x1Coord ? 1 : -1;
	int dy = -abs(y1Coord - y0Coord);
	int sy = y0Coord < y1Coord ? 1 : -1;
	int error = dx + dy;

	while (1) {
		CR_PixelsDrawRealPixel(pixels, x0Coord, y0Coord, color);

		if (x0Coord == x1Coord && y0Coord == y1Coord)
			break;

		int e2 = 2 * error;

		if (e2 >= dy) {
			error += dy;
			x0Coord += sx;
		}

		if (e2 <= dx) {
			error += dx;
			y0Coord += sy;
		}
	}
}

/// Returns positive or negative integer depending on what side of the line (0 -
/// 1) is the point 2.
static int edgeFunction(int x0, int y0, int x1, int y1, int x2, int y2) {
	return (x1 - x0) * (y2 - y0) - (y1 - y0) * (x2 - x0);
}

void CR_PixelsDrawTriangle(Pixels *pixels, float x0, float y0, float x1,
						   float y1, float x2, float y2, Color color) {
	// convert from relative (1…-1) to absolute coordinates (real pixels)
	float heightPixels = (float)pixels->height / 2.0;
	float widthPixels =
		(float)pixels->width / (float)pixels->height * heightPixels;

	// real coordinates
	int x0Coord = (x0 + 1) * widthPixels;
	int y0Coord = (-y0 + 1) * heightPixels;
	int x1Coord = (x1 + 1) * widthPixels;
	int y1Coord = (-y1 + 1) * heightPixels;
	int x2Coord = (x2 + 1) * widthPixels;
	int y2Coord = (-y2 + 1) * heightPixels;

	// minimal and maximal x and y coordinates (fit triangle into rectangle)
	int xMin = x0Coord < x1Coord ? x0Coord : x1Coord;
	xMin = xMin < x2Coord ? xMin : x2Coord;
	xMin = xMin < 0 ? 0 : xMin;
	int yMin = y0Coord < y1Coord ? y0Coord : y1Coord;
	yMin = yMin < y2Coord ? yMin : y2Coord;
	yMin = yMin < 0 ? 0 : yMin;
	int xMax = x0Coord > x1Coord ? x0Coord : x1Coord;
	xMax = xMax > x2Coord ? xMax : x2Coord;
	xMax = xMax > pixels->width ? pixels->width : xMax;
	int yMax = y0Coord > y1Coord ? y0Coord : y1Coord;
	yMax = yMax > y2Coord ? yMax : y2Coord;
	yMax = yMax > pixels->height ? pixels->height : yMax;

	char clockwise = 0;
	for (int x = xMin; x < xMax + 1; x++) {
		for (int y = yMin; y < yMax + 1; y++) {
			int ABP = edgeFunction(x0Coord, y0Coord, x1Coord, y1Coord, x, y);
			int BCP = edgeFunction(x1Coord, y1Coord, x2Coord, y2Coord, x, y);
			int CAP = edgeFunction(x2Coord, y2Coord, x0Coord, y0Coord, x, y);

			if (ABP >= 0 && BCP >= 0 && CAP >= 0) {
				CR_PixelsDrawRealPixel(pixels, x, y, color);
				clockwise = 1;
			}
		}
	}

	// Draw lines for smoother (more aesthetic) edges.
	if (clockwise) {
		CR_PixelsDrawLine(pixels, x0, y0, x1, y1, color);
		CR_PixelsDrawLine(pixels, x1, y1, x2, y2, color);
		CR_PixelsDrawLine(pixels, x0, y0, x2, y2, color);
	}
}
