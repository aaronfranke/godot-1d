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

void Area1D::move(const real_t p_movement) {
	return PhysicsServer1D::get_singleton()->move_area(this, p_movement);
}

Array Area1D::get_overlapping_areas() const {
	return PhysicsServer1D::get_singleton()->get_overlapping_areas(this);
}

Array Area1D::get_overlapping_bodies() const {
	return PhysicsServer1D::get_singleton()->get_overlapping_bodies(this);
}

bool Area1D::overlaps_area(const Area1D *p_area) const {
	return overlaps_body(p_area);
}

bool Area1D::overlaps_body(const CollisionObject1D *p_body) const {
	real_t area_position = get_position();
	real_t area_extents = get_size() / 2;
	real_t left_extent = area_position - area_extents;
	real_t right_extent = area_position + area_extents;

	real_t body_position = p_body->get_position();
	real_t body_extents = p_body->get_size() / 2;
	real_t body_left_extent = body_position - body_extents;
	real_t body_right_extent = body_position + body_extents;

	return left_extent < body_right_extent && body_left_extent < right_extent;
}

void Area1D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("move", "movement"), &Area1D::move);
	ClassDB::bind_method(D_METHOD("get_overlapping_areas"), &Area1D::get_overlapping_areas);
	ClassDB::bind_method(D_METHOD("get_overlapping_bodies"), &Area1D::get_overlapping_bodies);
	ClassDB::bind_method(D_METHOD("overlaps_area", "area"), &Area1D::overlaps_area);
	ClassDB::bind_method(D_METHOD("overlaps_body", "body"), &Area1D::overlaps_body);

	PropertyInfo body_arg;
	body_arg.type = Variant::OBJECT;
	body_arg.name = "body";
	body_arg.class_name = SNAME("CollisionObject1D");

	MethodInfo body_entered_methodinfo;
	body_entered_methodinfo.name = SceneStringNames::get_singleton()->body_exited;
	body_entered_methodinfo.arguments.push_back(body_arg);
	ClassDB::add_signal(SNAME("Area1D"), body_entered_methodinfo);

	MethodInfo body_exited_methodinfo;
	body_exited_methodinfo.name = SceneStringNames::get_singleton()->body_entered;
	body_exited_methodinfo.arguments.push_back(body_arg);
	ClassDB::add_signal(SNAME("Area1D"), body_exited_methodinfo);

	PropertyInfo area_arg;
	area_arg.type = Variant::OBJECT;
	area_arg.name = "area";
	area_arg.class_name = SNAME("Area1D");

	MethodInfo area_entered_methodinfo;
	area_entered_methodinfo.name = SceneStringNames::get_singleton()->area_exited;
	area_entered_methodinfo.arguments.push_back(area_arg);
	ClassDB::add_signal(SNAME("Area1D"), area_entered_methodinfo);

	MethodInfo area_exited_methodinfo;
	area_exited_methodinfo.name = SceneStringNames::get_singleton()->area_entered;
	area_exited_methodinfo.arguments.push_back(area_arg);
	ClassDB::add_signal(SNAME("Area1D"), area_exited_methodinfo);
}
