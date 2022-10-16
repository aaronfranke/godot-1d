#pragma once

#include "../node_1d.h"

// All derivatives of CollisionObject1D need HashSet.
#include <godot_cpp/templates/hash_set.hpp>

using namespace godot;

class CollisionObject1D : public Node1D {
	GDCLASS(CollisionObject1D, Node1D);

	// Unlike 2D and 3D, there is no purpose to collision SHAPES.
	// In 1D, the only available geometric shape is a line segment.
	// It only has a size. We interpret the node's position as the center.
	real_t _size = 64;

protected:
	static void _bind_methods();

public:
	void set_size(const real_t p_size);
	real_t get_size() const;
	real_t get_global_size() const;
};
