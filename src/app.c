#include "c-render/MVP.h"
#include "c-render/pixels.h"

#include "cglm/types.h"
#include "cglm/util.h"

typedef struct {
	vec4 A;
	vec4 B;
	vec4 C;
	float rotation;
	Model model;
	View view;
	Projection projection;
} App;

App appCreate() {
	App app = {{30, 5, 0, 1}, {60, 25, 0, 1}, {45, 25, 0, 1}, 0};
	return app;
}

void appRender(App *app, Pixels *pixels) {
	Color clearColor = {255, 255, 255, 255};
	CR_PixelsClear(pixels, clearColor);

	Color drawColor = {255, 0, 255, 255};
	// CR_PixelsDrawTriangle(pixels, app->A[0], app->A[1], app->B[0], app->B[1],
	// 					  app->C[0], app->C[1], drawColor);

	CR_PixelsDrawTriangleMVP(pixels, -0.5, 0.75, 0, 0.5, 0.5, 0, -0.75, -0.5, 0,
							 drawColor, app->model, app->view, app->projection);
}

void appUpdate(App *app, double delta, int pixelsWidth, int pixelsHeight) {
	app->rotation += delta * 0.1;
	if (app->rotation >= 180)
		app->rotation = 0;

	Model model = CR_MODEL_IDENTITY;
	model.scaleX = 0.3;
	model.scaleY = 0.3;
	model.scaleZ = 0.3;
	View view = CR_VIEW_IDENTITY;
	Projection projection = {
		glm_rad(45), (float)pixelsWidth / (float)pixelsHeight, 0.1, 100};

	app->model = model;
	app->view = view;
	app->projection = projection;
}
