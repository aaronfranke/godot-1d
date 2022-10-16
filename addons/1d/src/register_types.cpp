#include "register_types.h"

#include <godot/gdnative_interface.h>

#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/godot.hpp>

#include "nodes/audio_listener_1d.h"
//#include "nodes/audio_player_1d.h"
#include "nodes/camera_1d.h"
#include "nodes/physics/area_1d.h"
#include "nodes/physics/kinematic_body_1d.h"
#include "nodes/physics/physics_server_1d.h"
#include "nodes/physics/static_body_1d.h"
#include "nodes/sprite_1d.h"

using namespace godot;

void gdextension_initialize(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	ClassDB::register_class<Node1D>();
	ClassDB::register_class<AudioListener1D>();
//	ClassDB::register_class<AudioPlayer1D>();
	ClassDB::register_class<Camera1D>();
	ClassDB::register_class<Sprite1D>();

	// Physics.
	ClassDB::register_abstract_class<CollisionObject1D>();
	ClassDB::register_class<Area1D>();
	ClassDB::register_class<KinematicBody1D>();
	ClassDB::register_class<StaticBody1D>();
	PhysicsServer1D::initialize_singleton();
}

void gdextension_terminate(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE) {
		return;
	}
	PhysicsServer1D::uninitialize_singleton();
}

extern "C" {
	GDNativeBool GDN_EXPORT gdextension_init(const GDNativeInterface *p_interface, const GDNativeExtensionClassLibraryPtr p_library, GDNativeInitialization *r_initialization) {
		godot::GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);
		init_obj.register_initializer(gdextension_initialize);
		init_obj.register_terminator(gdextension_terminate);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);
		return init_obj.init();
	}
}
