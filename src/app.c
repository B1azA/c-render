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

	// CR_PixelsDrawTriangleMVP(pixels, -0.5, 0.75, 0, 0.5, 0.5, 0, -0.75, -0.5,
	// 0, 						 drawColor, app->model, app->view,
	// app->projection);

	Color color1 = {255, 0, 255, 255};
	Color color2 = {255, 255, 0, 255};
	Color color3 = {0, 0, 255, 255};
	Color color4 = {255, 0, 0, 255};
	Color color5 = {0, 0, 0, 255};
	Color color6 = {0, 255, 0, 255};

	CR_PixelsDrawTrianglesMVP(pixels,
							  (float[]){
								  -0.5,
								  0.5,
								  0.5,
								  0.5,
								  0.5,
								  0.5,
								  -0.5,
								  -0.5,
								  0.5,
								  -0.5,
								  -0.5,
								  0.5,
								  0.5,
								  0.5,
								  0.5,
								  0.5,
								  -0.5,
								  0.5,
							  },
							  18, color1, app->model, app->view,
							  app->projection);

	CR_PixelsDrawTrianglesMVP(pixels,
							  (float[]){

								  0.5,
								  0.5,
								  0.5,
								  0.5,
								  0.5,
								  -0.5,
								  0.5,
								  -0.5,
								  -0.5,
								  0.5,
								  -0.5,
								  -0.5,
								  0.5,
								  -0.5,
								  0.5,
								  0.5,
								  0.5,
								  0.5,
							  },
							  18, color2, app->model, app->view,
							  app->projection);
	CR_PixelsDrawTrianglesMVP(pixels,
							  (float[]){

								  0.5,
								  0.5,
								  -0.5,
								  -0.5,
								  0.5,
								  -0.5,
								  0.5,
								  -0.5,
								  -0.5,
								  0.5,
								  -0.5,
								  -0.5,
								  -0.5,
								  0.5,
								  -0.5,
								  -0.5,
								  -0.5,
								  -0.5,
							  },
							  18, color3, app->model, app->view,
							  app->projection);
	CR_PixelsDrawTrianglesMVP(pixels,
							  (float[]){

								  -0.5,
								  -0.5,
								  -0.5,
								  -0.5,
								  0.5,
								  -0.5,
								  -0.5,
								  0.5,
								  0.5,
								  -0.5,
								  0.5,
								  0.5,
								  -0.5,
								  -0.5,
								  0.5,
								  -0.5,
								  -0.5,
								  -0.5,
							  },
							  18, color4, app->model, app->view,
							  app->projection);
	CR_PixelsDrawTrianglesMVP(pixels,
							  (float[]){

								  -0.5,
								  0.5,
								  -0.5,
								  0.5,
								  0.5,
								  -0.5,
								  0.5,
								  0.5,
								  0.5,
								  0.5,
								  0.5,
								  0.5,
								  -0.5,
								  0.5,
								  0.5,
								  -0.5,
								  0.5,
								  -0.5,
							  },
							  18, color5, app->model, app->view,
							  app->projection);
	CR_PixelsDrawTrianglesMVP(pixels,
							  (float[]){

								  -0.5,
								  -0.5,
								  -0.5,
								  -0.5,
								  -0.5,
								  0.5,
								  0.5,
								  -0.5,
								  0.5,
								  0.5,
								  -0.5,
								  0.5,
								  0.5,
								  -0.5,
								  -0.5,
								  -0.5,
								  -0.5,
								  -0.5,
							  },
							  18, color6, app->model, app->view,
							  app->projection);
}

void appUpdate(App *app, double delta, int pixelsWidth, int pixelsHeight) {
	app->rotation += delta * 0.0005;
	if (app->rotation >= glm_rad(360))
		app->rotation = 0;

	Model model = CR_MODEL_IDENTITY;
	model.scaleX = 0.3;
	model.scaleY = 0.3;
	model.scaleZ = 0.3;

	View view = CR_VIEW_IDENTITY;
	view.rotX = app->rotation;
	view.rotY = app->rotation;

	Projection projection = {
		glm_rad(45), (float)pixelsWidth / (float)pixelsHeight, 0.1, 100};

	app->model = model;
	app->view = view;
	app->projection = projection;
}
