/// Model matrix abstraction struct.
typedef struct {
	float transX;
	float transY;
	float transZ;

	float rotX;
	float rotY;
	float rotZ;

	float scaleX;
	float scaleY;
	float scaleZ;
} Model;

Model CR_ModelCreateIdentity();

void CR_ModelTranslateBy(Model *model, float x, float y, float z);

void CR_ModelRotateBy(Model *model, float x, float y, float z);

void CR_ModelScaleBy(Model *model, float x, float y, float z);
