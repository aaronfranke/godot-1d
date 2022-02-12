#ifndef PHYSICS_SERVER_1D_H
#define PHYSICS_SERVER_1D_H

#include "area_1d.h"
#include "kinematic_body_1d.h"
#include "static_body_1d.h"

class PhysicsServer1D : public Object {
	GDCLASS(PhysicsServer1D, Object);

	static PhysicsServer1D *_singleton;

	Set<Area1D *> _areas;
	Set<KinematicBody1D *> _kinematic_bodies;
	Set<StaticBody1D *> _static_bodies;

public:
	static PhysicsServer1D *get_singleton();

	Set<Area1D *>::Element *register_area(Area1D *p_area);
	Set<KinematicBody1D *>::Element *register_kinematic_body(KinematicBody1D *p_body);
	Set<StaticBody1D *>::Element *register_static_body(StaticBody1D *p_body);

	void unregister_area(Set<Area1D *>::Element *p_area);
	void unregister_kinematic_body(Set<KinematicBody1D *>::Element *p_body);
	void unregister_static_body(Set<StaticBody1D *>::Element *p_body);

	real_t move_and_collide(KinematicBody1D *p_body, const real_t p_movement);
	void move_area(Area1D *p_area, const real_t p_movement);

	Array get_overlapping_areas(const Area1D *p_area) const;
	Array get_overlapping_bodies(const Area1D *p_body) const;
};

#endif // PHYSICS_SERVER_1D_H
