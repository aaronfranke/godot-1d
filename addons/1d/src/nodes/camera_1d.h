#pragma once

#include "node_1d.h"

#include <godot_cpp/classes/camera2d.hpp>

using namespace godot;

class Camera1D : public Node1D {
	GDCLASS(Camera1D, Node1D);

	// Viewport is hard-coded to accept Camera2D (and Camera3D). We'll just
	// use Camera2D as a proxy so that we don't have to modify Viewport.
	Camera2D *_real_camera;
	real_t _thickness = 10;

protected:
	static void _bind_methods();

public:
	void set_thickness(const real_t p_thickness);
	real_t get_thickness() const;

	Camera1D();
};
