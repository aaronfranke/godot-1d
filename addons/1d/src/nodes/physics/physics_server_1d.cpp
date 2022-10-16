#include "physics_server_1d.h"

//#include "scene/scene_string_names.h"

#define IF_MOVEMENT_OVERLAPS_STILL_BODY(m_still_body)                          \
	real_t still_body_position = m_still_body->get_global_position();          \
	real_t still_body_extents = m_still_body->get_global_size() / 2;           \
	real_t still_body_left_extent = still_body_position - still_body_extents;  \
	real_t still_body_right_extent = still_body_position + still_body_extents; \
	if (left_extent < still_body_right_extent && still_body_left_extent < right_extent)

void PhysicsServer1D::register_area(Area1D *p_area) {
	_areas.insert(p_area);
}

void PhysicsServer1D::register_kinematic_body(KinematicBody1D *p_body) {
	_kinematic_bodies.insert(p_body);
}

void PhysicsServer1D::register_static_body(StaticBody1D *p_body) {
	_static_bodies.insert(p_body);
}

void PhysicsServer1D::unregister_area(Area1D *p_area) {
	_areas.erase(p_area);
}

void PhysicsServer1D::unregister_kinematic_body(KinematicBody1D *p_body) {
	_kinematic_bodies.erase(p_body);
}

void PhysicsServer1D::unregister_static_body(StaticBody1D *p_body) {
	_static_bodies.erase(p_body);
}

real_t PhysicsServer1D::move_and_collide(KinematicBody1D *p_body, const real_t p_movement) {
	real_t body_position = p_body->get_global_position();
	real_t body_extents = p_body->get_global_size() / 2;
	real_t start_left_extent = body_position - body_extents;
	real_t start_right_extent = body_position + body_extents;
	real_t left_extent = start_left_extent;
	real_t right_extent = start_right_extent;
	real_t p_global_movement = p_movement;
	{
		Node1D *node_1d_parent = Object::cast_to<Node1D>(p_body->get_parent());
		if (node_1d_parent) {
			p_global_movement *= node_1d_parent->get_global_scale();
		}
	}
	if (p_global_movement < 0) {
		left_extent += p_global_movement;
	} else {
		right_extent += p_global_movement;
	}
	// Start by assuming we can move the whole way.
	real_t new_body_position = body_position + p_global_movement;

	// Detect collisions with StaticBody1D nodes and push our movement back.
	for (StaticBody1D *still_body : _static_bodies) {
		IF_MOVEMENT_OVERLAPS_STILL_BODY(still_body) {
			if (body_position < still_body_position) {
				real_t farthest_possible_position = still_body_left_extent - body_extents;
				if (farthest_possible_position < new_body_position) {
					new_body_position = farthest_possible_position;
				}
			} else {
				real_t farthest_possible_position = still_body_right_extent + body_extents;
				if (farthest_possible_position > new_body_position) {
					new_body_position = farthest_possible_position;
				}
			}
		}
	}
	// Detect collisions with KinematicBody1D nodes and push our movement back.
	for (KinematicBody1D *still_body : _kinematic_bodies) {
		if (still_body == p_body) {
			// We don't want to collide with ourself!
			continue;
		}
		IF_MOVEMENT_OVERLAPS_STILL_BODY(still_body) {
			if (body_position < still_body_position) {
				real_t farthest_possible_position = still_body_left_extent - body_extents;
				if (farthest_possible_position < new_body_position) {
					new_body_position = farthest_possible_position;
				}
			} else {
				real_t farthest_possible_position = still_body_right_extent + body_extents;
				if (farthest_possible_position > new_body_position) {
					new_body_position = farthest_possible_position;
				}
			}
		}
	}
	// Now that we are done with everything we can collide with, set the new position.
	p_body->set_global_position(new_body_position);

	// Check overlapping areas. This is only for detection and not for collision.
	real_t end_left_extent = new_body_position - body_extents;
	real_t end_right_extent = new_body_position + body_extents;
	for (Area1D *still_body : _areas) {
		IF_MOVEMENT_OVERLAPS_STILL_BODY(still_body) {
			bool start_overlaps = start_left_extent < still_body_right_extent && still_body_left_extent < start_right_extent;
			bool end_overlaps = end_left_extent < still_body_right_extent && still_body_left_extent < end_right_extent;
			Variant body_variant = Variant(p_body);
			if (start_overlaps && end_overlaps) {
				// If both of these are true, we are starting and ending
				// inside the Area1D, therefore we are not entering or exiting.
			} else if (start_overlaps) {
				// If we started overlapping but are not overlapping
				// at the end, we are exiting the Area1D.
				still_body->emit_signal(StringName("body_exited"), body_variant);
			} else if (end_overlaps) {
				// If we ended overlapping but are not overlapping
				// at the start, we are entering the Area1D.
				still_body->emit_signal(StringName("body_entered"), body_variant);
			} else {
				// If we did not start overlapping and will not end
				// overlapping, we phased through the Area1D, therefore
				// we will emit both entered and exited signals since
				// this would happen if only the framerate was higher.
				still_body->emit_signal(StringName("body_entered"), body_variant);
				still_body->emit_signal(StringName("body_exited"), body_variant);
			}
		}
	}
	// Return the remainder of the movement after collision.
	return body_position + p_movement - new_body_position;
}

void PhysicsServer1D::move_area(Area1D *p_area, const real_t p_movement) {
	real_t area_position = p_area->get_global_position();
	real_t area_extents = p_area->get_global_size() / 2;
	real_t start_left_extent = area_position - area_extents;
	real_t start_right_extent = area_position + area_extents;
	real_t left_extent = start_left_extent;
	real_t right_extent = start_right_extent;
	real_t p_global_movement = p_movement;
	{
		Node1D *node_1d_parent = Object::cast_to<Node1D>(p_area->get_parent());
		if (node_1d_parent) {
			p_global_movement *= node_1d_parent->get_global_scale();
		}
	}
	if (p_global_movement < 0) {
		left_extent += p_global_movement;
	} else {
		right_extent += p_global_movement;
	}
	// Areas do n ot collide so they can always move the whole way.
	real_t new_body_position = area_position + p_global_movement;
	p_area->set_global_position(new_body_position);
	real_t end_left_extent = new_body_position - area_extents;
	real_t end_right_extent = new_body_position + area_extents;

	// Detect intersections with StaticBody1D nodes.
	for (StaticBody1D *still_body : _static_bodies) {
		IF_MOVEMENT_OVERLAPS_STILL_BODY(still_body) {
			bool start_overlaps = start_left_extent < still_body_right_extent && still_body_left_extent < start_right_extent;
			bool end_overlaps = end_left_extent < still_body_right_extent && still_body_left_extent < end_right_extent;
			Variant still_body_variant = Variant(still_body);
			if (start_overlaps && end_overlaps) {
				// Do nothing. See the comments in move_and_collide for details.
			} else if (start_overlaps) {
				p_area->emit_signal(StringName("body_exited"), still_body_variant);
			} else if (end_overlaps) {
				p_area->emit_signal(StringName("body_entered"), still_body_variant);
			} else {
				p_area->emit_signal(StringName("body_entered"), still_body_variant);
				p_area->emit_signal(StringName("body_exited"), still_body_variant);
			}
		}
	}
	// Detect intersections with KinematicBody1D nodes.
	for (KinematicBody1D *still_body : _kinematic_bodies) {
		IF_MOVEMENT_OVERLAPS_STILL_BODY(still_body) {
			bool start_overlaps = start_left_extent < still_body_right_extent && still_body_left_extent < start_right_extent;
			bool end_overlaps = end_left_extent < still_body_right_extent && still_body_left_extent < end_right_extent;
			Variant still_body_variant = Variant(still_body);
			if (start_overlaps && end_overlaps) {
				// Do nothing. See the comments in move_and_collide for details.
			} else if (start_overlaps) {
				p_area->emit_signal(StringName("body_exited"), still_body_variant);
			} else if (end_overlaps) {
				p_area->emit_signal(StringName("body_entered"), still_body_variant);
			} else {
				p_area->emit_signal(StringName("body_entered"), still_body_variant);
				p_area->emit_signal(StringName("body_exited"), still_body_variant);
			}
		}
	}
	// Detect intersections with Area1D nodes.
	for (Area1D *still_body : _areas) {
		IF_MOVEMENT_OVERLAPS_STILL_BODY(still_body) {
			bool start_overlaps = start_left_extent < still_body_right_extent && still_body_left_extent < start_right_extent;
			bool end_overlaps = end_left_extent < still_body_right_extent && still_body_left_extent < end_right_extent;
			Variant area_variant = Variant(p_area);
			Variant still_body_variant = Variant(still_body);
			if (start_overlaps && end_overlaps) {
				// Do nothing. See the comments in move_and_collide for details.
			} else if (start_overlaps) {
				still_body->emit_signal(StringName("area_exited"), area_variant);
				p_area->emit_signal(StringName("area_exited"), still_body_variant);
			} else if (end_overlaps) {
				still_body->emit_signal(StringName("area_entered"), area_variant);
				p_area->emit_signal(StringName("area_entered"), still_body_variant);
			} else {
				still_body->emit_signal(StringName("area_entered"), area_variant);
				p_area->emit_signal(StringName("area_entered"), still_body_variant);
				still_body->emit_signal(StringName("area_exited"), area_variant);
				p_area->emit_signal(StringName("area_exited"), still_body_variant);
			}
		}
	}
}

Array PhysicsServer1D::get_overlapping_areas(const Area1D *p_area) const {
	real_t area_position = p_area->get_global_position();
	real_t area_extents = p_area->get_global_size() / 2;
	real_t left_extent = area_position - area_extents;
	real_t right_extent = area_position + area_extents;
	Array ret;
	for (Area1D *still_body : _areas) {
		if (still_body == p_area) {
			// We don't want to overlap with ourself!
			continue;
		}
		IF_MOVEMENT_OVERLAPS_STILL_BODY(still_body) {
			ret.push_back(still_body);
		}
	}
	return ret;
}

Array PhysicsServer1D::get_overlapping_bodies(const Area1D *p_area) const {
	real_t area_position = p_area->get_global_position();
	real_t area_extents = p_area->get_global_size() / 2;
	real_t left_extent = area_position - area_extents;
	real_t right_extent = area_position + area_extents;
	Array ret;
	for (StaticBody1D *still_body : _static_bodies) {
		IF_MOVEMENT_OVERLAPS_STILL_BODY(still_body) {
			ret.push_back(still_body);
		}
	}
	for (KinematicBody1D *still_body : _kinematic_bodies) {
		IF_MOVEMENT_OVERLAPS_STILL_BODY(still_body) {
			ret.push_back(still_body);
		}
	}
	return ret;
}

PhysicsServer1D *PhysicsServer1D::_singleton = nullptr;

void PhysicsServer1D::initialize_singleton() {
	_singleton = memnew(PhysicsServer1D);
}

void PhysicsServer1D::uninitialize_singleton() {
	memdelete(_singleton);
}

PhysicsServer1D *PhysicsServer1D::get_singleton() {
	return _singleton;
}
