#include "register_types.h"

#include "nodes/audio_listener_1d.h"
#include "nodes/audio_player_1d.h"
#include "nodes/camera_1d.h"
#include "nodes/physics/area_1d.h"
#include "nodes/physics/kinematic_body_1d.h"
#include "nodes/physics/physics_server_1d.h"
#include "nodes/physics/static_body_1d.h"
#include "nodes/sprite_1d.h"

void initialize_1d_module(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<AudioListener1D>();
	ClassDB::register_class<AudioPlayer1D>();
	ClassDB::register_class<Camera1D>();
	ClassDB::register_class<Node1D>();
	ClassDB::register_class<Sprite1D>();

	// Physics.
	ClassDB::register_abstract_class<CollisionObject1D>();
	ClassDB::register_class<Area1D>();
	ClassDB::register_class<KinematicBody1D>();
	ClassDB::register_class<StaticBody1D>();
	PhysicsServer1D::get_singleton();
}

void uninitialize_1d_module(ModuleInitializationLevel p_level) {}
