#include "node_1d.h"

#ifdef TOOLS_ENABLED
Dictionary Node1D::_edit_get_state() const {
	Dictionary state;
	state["position"] = _position;
	state["scale"] = _scale;
	return state;
}

void Node1D::_edit_set_state(const Dictionary &p_state) {
	_position = p_state["position"];
	_scale = p_state["scale"];
	_update_transform();
}

void Node1D::_edit_set_position(const Point2 &p_position) {
	set_position(p_position.x);
}

Point2 Node1D::_edit_get_position() const {
	return Point2(_position, 0.0);
}

void Node1D::_edit_set_scale(const Size2 &p_scale) {
	set_scale(p_scale.x);
}

Size2 Node1D::_edit_get_scale() const {
	return Size2(_scale, 1.0);
}

void Node1D::_edit_set_rotation(real_t p_rotation) {}

real_t Node1D::_edit_get_rotation() const {
	return 0.0;
}

bool Node1D::_edit_use_rotation() const {
	return false;
}

void Node1D::_edit_set_rect(const Rect2 &p_edit_rect) {
	ERR_FAIL_COND(!_edit_use_rect());

	Rect2 r = _edit_get_rect();

	real_t zero_offset = 0.0;
	real_t new_scale = 1.0;

	if (r.size.x != 0) {
		zero_offset = -r.position.x / r.size.x;
		new_scale = p_edit_rect.size.x / r.size.x;
	}

	real_t new_pos = p_edit_rect.position.x + p_edit_rect.size.x * zero_offset;

	_position += new_pos * _scale;
	_scale *= new_scale;
	_update_transform();
}
#endif // TOOLS_ENABLED

void Node1D::_update_transform() {
	VisualServer::get_singleton()->canvas_item_set_transform(get_canvas_item(), get_transform());
	if (!is_inside_tree()) {
		return;
	}
	_notify_transform();
}

real_t Node1D::get_position() const {
	return _position;
}

real_t Node1D::get_scale() const {
	return _scale;
}

void Node1D::set_position(const real_t p_position) {
	_position = p_position;
	_update_transform();
}

void Node1D::set_scale(const real_t p_scale) {
	// Avoid having 0 scale values, can lead to errors in physics and rendering.
	if (Math::is_zero_approx(p_scale)) {
		_scale = CMP_EPSILON;
	} else {
		_scale = p_scale;
	}
	_update_transform();
}

Transform2D Node1D::get_transform() const {
	return Transform2D(_scale, 0, 0, 1, _position, 0);
}

void Node1D::translate(const real_t p_amount) {
	set_position(_position + p_amount);
}

void Node1D::apply_scale(const real_t p_amount) {
	set_scale(_scale * p_amount);
}

real_t Node1D::get_global_position() const {
	Node1D *node_1d_parent = Object::cast_to<Node1D>(get_parent());
	if (node_1d_parent) {
		return node_1d_parent->get_global_position() + _position * node_1d_parent->get_global_scale();
	}
	return _position;
}

real_t Node1D::get_global_scale() const {
	Node1D *node_1d_parent = Object::cast_to<Node1D>(get_parent());
	if (node_1d_parent) {
		return _scale * node_1d_parent->get_global_scale();
	}
	return _scale;
}

void Node1D::set_global_position(const real_t p_global_position) {
	Node1D *node_1d_parent = Object::cast_to<Node1D>(get_parent());
	if (node_1d_parent) {
		set_position((p_global_position - node_1d_parent->get_global_position()) / node_1d_parent->get_global_scale());
	} else {
		set_position(p_global_position);
	}
}

void Node1D::set_global_scale(const real_t p_global_scale) {
	Node1D *node_1d_parent = Object::cast_to<Node1D>(get_parent());
	if (node_1d_parent) {
		set_scale(p_global_scale / node_1d_parent->get_global_scale());
	} else {
		set_scale(p_global_scale);
	}
}

void Node1D::set_z_index(const int p_z) {
	ERR_FAIL_COND(p_z < VS::CANVAS_ITEM_Z_MIN);
	ERR_FAIL_COND(p_z > VS::CANVAS_ITEM_Z_MAX);
	_z_index = p_z;
	VS::get_singleton()->canvas_item_set_z_index(get_canvas_item(), _z_index);
}

void Node1D::set_z_as_relative(const bool p_enabled) {
	if (_z_relative == p_enabled) {
		return;
	}
	_z_relative = p_enabled;
	VS::get_singleton()->canvas_item_set_z_as_relative_to_parent(get_canvas_item(), p_enabled);
}

bool Node1D::is_z_relative() const {
	return _z_relative;
}

int Node1D::get_z_index() const {
	return _z_index;
}

void Node1D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_position"), &Node1D::get_position);
	ClassDB::bind_method(D_METHOD("get_scale"), &Node1D::get_scale);
	ClassDB::bind_method(D_METHOD("set_position", "position"), &Node1D::set_position);
	ClassDB::bind_method(D_METHOD("set_scale", "scale"), &Node1D::set_scale);
	ClassDB::bind_method(D_METHOD("translate", "offset"), &Node1D::translate);
	ClassDB::bind_method(D_METHOD("apply_scale", "ratio"), &Node1D::apply_scale);

	ClassDB::bind_method(D_METHOD("get_global_position"), &Node1D::get_global_position);
	ClassDB::bind_method(D_METHOD("get_global_scale"), &Node1D::get_global_scale);
	ClassDB::bind_method(D_METHOD("set_global_position", "global_position"), &Node1D::set_global_position);
	ClassDB::bind_method(D_METHOD("set_global_scale", "global_scale"), &Node1D::set_global_scale);

	ClassDB::bind_method(D_METHOD("set_z_index", "z_index"), &Node1D::set_z_index);
	ClassDB::bind_method(D_METHOD("get_z_index"), &Node1D::get_z_index);
	ClassDB::bind_method(D_METHOD("set_z_as_relative", "enable"), &Node1D::set_z_as_relative);
	ClassDB::bind_method(D_METHOD("is_z_relative"), &Node1D::is_z_relative);

	ADD_PROPERTY(PropertyInfo(Variant::REAL, "position", PROPERTY_HINT_RANGE, "-99999,99999,0.001,or_lesser,or_greater,noslider,suffix:px"), "set_position", "get_position");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "scale"), "set_scale", "get_scale");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "global_position", PROPERTY_HINT_RANGE, "-99999,99999,0.001,or_lesser,or_greater,noslider,suffix:px", 0), "set_global_position", "get_global_position");
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "global_scale", PROPERTY_HINT_NONE, "", 0), "set_global_scale", "get_global_scale");

	ADD_GROUP("Ordering", "");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "z_index", PROPERTY_HINT_RANGE, itos(VS::CANVAS_ITEM_Z_MIN) + "," + itos(VS::CANVAS_ITEM_Z_MAX) + ",1"), "set_z_index", "get_z_index");
	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "z_as_relative"), "set_z_as_relative", "is_z_relative");
}
