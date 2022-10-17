#include "register_types.h"

#include "nodes/audio_listener_1d.h"
#include "nodes/camera_1d.h"
#include "nodes/physics/area_1d.h"
#include "nodes/physics/kinematic_body_1d.h"
#include "nodes/physics/physics_server_1d.h"
#include "nodes/physics/static_body_1d.h"
#include "nodes/sprite_1d.h"

void register_1d_types() {
	ClassDB::register_class<AudioListener1D>();
	ClassDB::register_class<Camera1D>();
	ClassDB::register_class<Node1D>();
	ClassDB::register_class<Sprite1D>();

	// Physics.
	ClassDB::register_virtual_class<CollisionObject1D>();
	ClassDB::register_class<Area1D>();
	ClassDB::register_class<KinematicBody1D>();
	ClassDB::register_class<StaticBody1D>();
	PhysicsServer1D::initialize_singleton();
}

void unregister_1d_types() {
	PhysicsServer1D::uninitialize_singleton();
}
