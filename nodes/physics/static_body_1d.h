#ifndef STATIC_BODY_1D_H
#define STATIC_BODY_1D_H

#include "collision_object_1d.h"

class StaticBody1D : public CollisionObject1D {
	GDCLASS(StaticBody1D, CollisionObject1D);

	Set<StaticBody1D *>::Element *_server_element;

protected:
	void _notification(const int p_what);
};

#endif // STATIC_BODY_1D_H
