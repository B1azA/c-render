#include "model.h"

Model CR_ModelCreateIdentity() {
	Model model = {0, 0, 0, 0, 0, 0, 1, 1, 1};
	return model;
}

void CR_ModelTranslateBy(Model *model, float x, float y, float z) {
	model->transX += x;
	model->transY += y;
	model->transZ += z;
}

void CR_ModelRotateBy(Model *model, float x, float y, float z) {
	model->rotX += x;
	model->rotY += y;
	model->rotZ += z;
}

void CR_ModelScaleBy(Model *model, float x, float y, float z) {
	model->scaleX *= x;
	model->scaleY *= y;
	model->scaleZ *= z;
}
