#ifndef AREA_1D_H
#define AREA_1D_H

#include "collision_object_1d.h"

class Area1D : public CollisionObject1D {
	GDCLASS(Area1D, CollisionObject1D);

protected:
	void _notification(const int p_what);
	static void _bind_methods();

public:
	void move(const real_t p_movement);

	Array get_overlapping_areas() const;
	Array get_overlapping_bodies() const;

	bool overlaps_area(const Area1D *p_area) const;
	bool overlaps_body(const CollisionObject1D *p_body) const;
};

#endif // AREA_1D_H
