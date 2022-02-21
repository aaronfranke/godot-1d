#include "collision_object_1d.h"

void CollisionObject1D::set_size(const real_t p_size) {
	ERR_FAIL_COND_MSG(p_size < CMP_EPSILON, "Size must be greater than zero.");
	_size = p_size;
}

real_t CollisionObject1D::get_size() const {
	return _size;
}

real_t CollisionObject1D::get_global_size() const {
	Node1D *node_1d_parent = Object::cast_to<Node1D>(get_parent());
	if (node_1d_parent) {
		return _size * get_global_scale();
	}
	return _size;
}

void CollisionObject1D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_size", "size"), &CollisionObject1D::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &CollisionObject1D::get_size);

	ADD_PROPERTY(PropertyInfo(Variant::REAL, "size"), "set_size", "get_size");
}
