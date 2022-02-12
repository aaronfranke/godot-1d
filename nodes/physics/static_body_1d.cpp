#include "static_body_1d.h"

#include "physics_server_1d.h"

void StaticBody1D::_notification(const int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			_server_element = PhysicsServer1D::get_singleton()->register_static_body(this);
		} break;
		case NOTIFICATION_EXIT_TREE: {
			PhysicsServer1D::get_singleton()->unregister_static_body(_server_element);
		} break;
	}
}
