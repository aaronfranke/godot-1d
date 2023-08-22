#include "camera_1d.h"

#include "scene/2d/camera_2d.h"

void Camera1D::set_is_vertical(const bool p_is_vertical) {
	_is_vertical = p_is_vertical;
	_real_camera->set_rotation(_is_vertical ? Math_TAU / 4.0 : 0.0);
	set_thickness(_thickness);
}

bool Camera1D::get_is_vertical() const {
	return _is_vertical;
}

void Camera1D::set_thickness(const real_t p_thickness) {
	ERR_FAIL_COND_MSG(p_thickness < CMP_EPSILON, "Thickness must be greater than zero.");
	_thickness = p_thickness;
	if (_is_vertical) {
		_real_camera->set_zoom(Vector2(_thickness, 1.0));
	} else {
		_real_camera->set_zoom(Vector2(1.0, _thickness));
	}
}

real_t Camera1D::get_thickness() const {
	return _thickness;
}

void Camera1D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_is_vertical", "is_vertical"), &Camera1D::set_is_vertical);
	ClassDB::bind_method(D_METHOD("get_is_vertical"), &Camera1D::get_is_vertical);
	ClassDB::bind_method(D_METHOD("set_thickness", "thickness"), &Camera1D::set_thickness);
	ClassDB::bind_method(D_METHOD("get_thickness"), &Camera1D::get_thickness);

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "is_vertical"), "set_is_vertical", "get_is_vertical");
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "thickness"), "set_thickness", "get_thickness");
}

Camera1D::Camera1D() {
	_real_camera = memnew(Camera2D);
	add_child(_real_camera);
	_real_camera->set_position(Vector2(0.0, 0.5));
	_real_camera->set_enabled(true);
	_real_camera->set_ignore_rotation(false);
	set_thickness(_thickness);
}
