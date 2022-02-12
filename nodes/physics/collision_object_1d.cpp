#include "collision_object_1d.h"

void CollisionObject1D::set_size(const real_t p_size) {
	ERR_FAIL_COND_MSG(p_size < CMP_EPSILON, "Size must be greater than zero.");
	_size = p_size;
}

real_t CollisionObject1D::get_size() const {
	return _size;
}

void CollisionObject1D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_size", "size"), &CollisionObject1D::set_size);
	ClassDB::bind_method(D_METHOD("get_size"), &CollisionObject1D::get_size);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "size"), "set_size", "get_size");
}
