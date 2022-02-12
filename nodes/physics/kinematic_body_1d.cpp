#include "kinematic_body_1d.h"

#include "physics_server_1d.h"

void KinematicBody1D::_notification(const int p_what) {
	switch (p_what) {
		case NOTIFICATION_ENTER_TREE: {
			_server_element = PhysicsServer1D::get_singleton()->register_kinematic_body(this);
		} break;
		case NOTIFICATION_EXIT_TREE: {
			PhysicsServer1D::get_singleton()->unregister_kinematic_body(_server_element);
		} break;
	}
}

real_t KinematicBody1D::move_and_collide(const real_t p_movement) {
	return PhysicsServer1D::get_singleton()->move_and_collide(this, p_movement);
}

void KinematicBody1D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("move_and_collide", "movement"), &KinematicBody1D::move_and_collide);
}
