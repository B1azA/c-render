#include "c-render/model.h"
#include "c-render/pixels.h"

#include "cglm/affine-pre.h"
#include "cglm/affine.h"
#include "cglm/cam.h"
#include "cglm/mat4.h"
#include "cglm/types.h"

typedef struct {
	vec4 A;
	vec4 B;
	vec4 C;
	Model model;
	float rotation;
} App;

App appCreate() {
	Model model = CR_ModelCreateIdentity();
	App app = {{30, 5, 0, 1}, {60, 25, 0, 1}, {45, 25, 0, 1}, model, 0};
	return app;
}

void appRender(App *app, Pixels *pixels) {
	Color clearColor = {255, 255, 255, 255};
	CR_PixelsClear(pixels, clearColor);

	Color drawColor = {255, 0, 255, 255};
	CR_PixelsDrawTriangle(pixels, app->A[0], app->A[1], app->B[0], app->B[1],
						  app->C[0], app->C[1], drawColor);
}

void appUpdate(App *app, double delta, int pixelsWidth, int pixelsHeight) {
	vec3 direction = {0.0, 0.0, 0};
	mat4 translation;

	vec3 scaledDirection;

	glm_vec3_scale(direction, delta, scaledDirection);

	glm_translate_make(translation, scaledDirection);

	mat4 model;
	mat4 rotation;
	vec3 axis = {0, 0, 1};

	vec3 pivot = {0, 0, 0};

	app->rotation += delta;

	glm_rotate_atm(rotation, pivot, app->rotation * 0.001, axis);

	glm_mat4_mul(rotation, translation, model);

	mat4 projection;
	glm_perspective(glm_rad(70), (float)pixelsWidth / (float)pixelsHeight, 0.1,
					100.0, projection);

	mat4 view = GLM_MAT4_IDENTITY_INIT;

	mat4 MVP;

	glm_mat4_mulN((mat4 *[]){&projection, &view, &model}, 3, MVP);

	glm_mat4_mulv(MVP, (vec4){-0.5, 0.5, 0, 1}, app->A);
	glm_mat4_mulv(MVP, (vec4){0.5, 0.5, 0, 1}, app->B);
	glm_mat4_mulv(MVP, (vec4){-0.5, -0.5, 0, 1}, app->C);

	CR_ModelTranslateBy(&app->model, 0.01, 0.01, 0);
	CR_ModelRotateBy(&app->model, 0, 0, 0.01);
	CR_ModelScaleBy(&app->model, 1, 1, 1);
}
