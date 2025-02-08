#ifndef MVP_H_
#define MVP_H_
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

/// View (camera) matrix abstraction.
typedef struct {
	float posX;
	float posY;
	float posZ;

	float rotX;
	float rotY;
	float rotZ;
} View;

/// Perspective projection matrix abstraction.
typedef struct {
	float fov;
	float aspect;
	float nearZ;
	float farZ;
} Projection;

#define CR_MODEL_IDENTITY {0, 0, 0, 0, 0, 0, 1, 1, 1};
#define CR_VIEW_IDENTITY {0, 0, 0, 0, 0, 0};

#endif
