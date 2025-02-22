#ifndef PIXELS_H_
#define PIXELS_H_

#include "MVP.h"
#include <stdint.h>

/// Buffer of RGBA pixels. Basic struct for drawing.
struct Pixels {
	uint8_t *pixelData;
	int width;
	int height;
};

typedef struct Pixels Pixels;

struct Color {
	uint8_t r;
	uint8_t g;
	uint8_t b;
	uint8_t a;
};

typedef struct Color Color;

/**  Create a Pixels struct, data are stored in 4 * 8bit RGBA format.
 *  \param initColor 4 * 8 bit RGBA values, all pixels are set to initColor
 *  \param width width of the pixel 2D array
 *  \param height height of the pixel 2D array
 */
Pixels CR_PixelsCreate(Color initColor, int width, int height);

void CR_PixelsDestroy(Pixels *pixels);

/**  Draw a pixel in relative coordinates (1 … -1).
 */
void CR_PixelsDrawPixel(Pixels *pixels, float x, float y, Color color);

/**  Draw a pixel in absolute (real pixel) coordinates.
 */
void CR_PixelsDrawRealPixel(Pixels *pixels, int x, int y, Color color);

void CR_PixelsResize(Pixels *pixels, int newWidth, int newHeight);

/** Set all pixels to color.
 */
void CR_PixelsClear(Pixels *pixels, Color color);

/** Draw a line from point 0 to 1 using color.
 */
void CR_PixelsDrawLine(Pixels *pixels, float x0, float y0, float x1, float y1,
					   Color color);

/**  Draw a triangle filled with color to Pixels.
 *	All verticies have to be clockwise, otherwise the triangle won't render.
 */
void CR_PixelsDrawTriangle(Pixels *pixels, float x0, float y0, float x1,
						   float y1, float x2, float y2, Color color);

void CR_PixelsDrawTriangleMVP(Pixels *pixels, float x0, float y0, float z0,
							  float x1, float y1, float z1, float x2, float y2,
							  float z2, Color color, Model model, View view,
							  Projection projection);

void CR_PixelsDrawTriangles(Pixels *pixels, float *vertices, int verticesLength,
							Color color);

void CR_PixelsDrawTrianglesMVP(Pixels *pixels, float *vertices,
							   int verticesLength, Color color, Model model,
							   View view, Projection projection);
#endif
