#pragma once

#include "collision_object_1d.h"

using namespace godot;

class KinematicBody1D : public CollisionObject1D {
	GDCLASS(KinematicBody1D, CollisionObject1D);

protected:
	void _notification(const int p_what);
	static void _bind_methods();

public:
	real_t move_and_collide(const real_t p_movement);
};
