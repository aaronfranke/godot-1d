#pragma once

#include "collision_object_1d.h"

using namespace godot;

class StaticBody1D : public CollisionObject1D {
	GDCLASS(StaticBody1D, CollisionObject1D);

protected:
	void _notification(const int p_what);
};
