#ifndef AREA_1D_H
#define AREA_1D_H

#include "collision_object_1d.h"

class Area1D : public CollisionObject1D {
	GDCLASS(Area1D, CollisionObject1D);

	Set<Area1D *>::Element *_server_element;

protected:
	void _notification(const int p_what);
	static void _bind_methods();
};

#endif // AREA_1D_H
