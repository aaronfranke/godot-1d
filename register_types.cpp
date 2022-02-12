#include "register_types.h"

#include "nodes/camera_1d.h"
#include "nodes/sprite_1d.h"

void register_1d_types() {
	ClassDB::register_class<Camera1D>();
	ClassDB::register_class<Node1D>();
	ClassDB::register_class<Sprite1D>();
}

void unregister_1d_types() {}
