#ifndef KINEMATIC_BODY_1D_H
#define KINEMATIC_BODY_1D_H

#include "collision_object_1d.h"

class KinematicBody1D : public CollisionObject1D {
	GDCLASS(KinematicBody1D, CollisionObject1D);

	Set<KinematicBody1D *>::Element *_server_element;

protected:
	void _notification(const int p_what);
	static void _bind_methods();

public:
	real_t move_and_collide(const real_t p_movement);
};

#endif // KINEMATIC_BODY_1D_H
