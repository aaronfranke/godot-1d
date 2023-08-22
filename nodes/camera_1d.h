#ifndef CAMERA_1D_H
#define CAMERA_1D_H

#include "node_1d.h"
class Camera2D;

class Camera1D : public Node1D {
	GDCLASS(Camera1D, Node1D);

	// Viewport is hard-coded to accept Camera2D (and Camera3D). We'll just
	// use Camera2D as a proxy so that we don't have to modify Viewport.
	Camera2D *_real_camera;
	bool _is_vertical = false;
	real_t _thickness = 20;

protected:
	static void _bind_methods();

public:
	void set_is_vertical(const bool p_is_vertical);
	bool get_is_vertical() const;

	void set_thickness(const real_t p_thickness);
	real_t get_thickness() const;

	Camera1D();
};

#endif // CAMERA_1D_H
