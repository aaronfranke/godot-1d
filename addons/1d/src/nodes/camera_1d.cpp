#include "camera_1d.h"

void Camera1D::set_thickness(const real_t p_thickness) {
	ERR_FAIL_COND_MSG(p_thickness < CMP_EPSILON, "Thickness must be greater than zero.");
	_thickness = p_thickness;
	_real_camera->set_zoom(Vector2(1.0, _thickness));
}

real_t Camera1D::get_thickness() const {
	return _thickness;
}

void Camera1D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_thickness", "thickness"), &Camera1D::set_thickness);
	ClassDB::bind_method(D_METHOD("get_thickness"), &Camera1D::get_thickness);

	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "thickness"), "set_thickness", "get_thickness");
}

Camera1D::Camera1D() {
	_real_camera = memnew(Camera2D);
	add_child(_real_camera);
	_real_camera->set_position(Vector2(0.0, 0.5));
	_real_camera->set_enabled(true);
	set_thickness(_thickness);
}
