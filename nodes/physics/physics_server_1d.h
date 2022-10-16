#ifndef PHYSICS_SERVER_1D_H
#define PHYSICS_SERVER_1D_H

#include "area_1d.h"
#include "kinematic_body_1d.h"
#include "static_body_1d.h"

class PhysicsServer1D : public Object {
	GDCLASS(PhysicsServer1D, Object);

	static PhysicsServer1D *_singleton;

	HashSet<Area1D *> _areas;
	HashSet<KinematicBody1D *> _kinematic_bodies;
	HashSet<StaticBody1D *> _static_bodies;

public:
	static PhysicsServer1D *get_singleton();
	static void initialize_singleton();
	static void uninitialize_singleton();

	void register_area(Area1D *p_area);
	void register_kinematic_body(KinematicBody1D *p_body);
	void register_static_body(StaticBody1D *p_body);

	void unregister_area(Area1D *p_area);
	void unregister_kinematic_body(KinematicBody1D *p_body);
	void unregister_static_body(StaticBody1D *p_body);

	real_t move_and_collide(KinematicBody1D *p_body, const real_t p_movement);
	void move_area(Area1D *p_area, const real_t p_movement);

	Array get_overlapping_areas(const Area1D *p_area) const;
	Array get_overlapping_bodies(const Area1D *p_body) const;
};

#endif // PHYSICS_SERVER_1D_H
