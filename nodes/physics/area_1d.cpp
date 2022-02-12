#include "area_1d.h"

#include "physics_server_1d.h"
#include "scene/scene_string_names.h"

void Area1D::_notification(const int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			_server_element = PhysicsServer1D::get_singleton()->register_area(this);
		} break;
		case NOTIFICATION_EXIT_TREE: {
			PhysicsServer1D::get_singleton()->unregister_area(_server_element);
		} break;
	}
}

void Area1D::_bind_methods() {
	PropertyInfo arg;
	arg.type = Variant::OBJECT;
	arg.name = "body";
	arg.class_name = SNAME("CollisionObject1D");

	MethodInfo body_entered_methodinfo;
	body_entered_methodinfo.name = SceneStringNames::get_singleton()->body_exited;
	body_entered_methodinfo.arguments.push_back(arg);
	ClassDB::add_signal(SNAME("Area1D"), body_entered_methodinfo);

	MethodInfo body_exited_methodinfo;
	body_exited_methodinfo.name = SceneStringNames::get_singleton()->body_entered;
	body_exited_methodinfo.arguments.push_back(arg);
	ClassDB::add_signal(SNAME("Area1D"), body_exited_methodinfo);
}
