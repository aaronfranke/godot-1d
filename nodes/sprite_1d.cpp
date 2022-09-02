#include "sprite_1d.h"

#include "core/core_string_names.h"
#include "scene/main/viewport.h"
#include "scene/scene_string_names.h"

#ifdef TOOLS_ENABLED
Rect2 Sprite1D::_edit_get_rect() const {
	return get_rect();
}

bool Sprite1D::_edit_use_rect() const {
	return _texture.is_valid();
}
#endif

Rect2 Sprite1D::get_anchorable_rect() const {
	return get_rect();
}

void Sprite1D::_get_rects(Rect2 &r_src_rect, Rect2 &r_dst_rect) const {
	int size = _texture->get_width();

	real_t dest_offset = -size / 2;
	if (get_viewport() && get_viewport()->is_snap_2d_transforms_to_pixel_enabled()) {
		dest_offset = Math::floor(dest_offset);
	}

	r_src_rect = Rect2(0, _frame, size, 1);
	r_dst_rect = Rect2(dest_offset, 0, size, 1);
}

void Sprite1D::_notification(const int p_what) {
	switch (p_what) {
		case NOTIFICATION_DRAW: {
			if (_texture.is_null()) {
				return;
			}

			RID ci = get_canvas_item();

			Rect2 src_rect, dst_rect;
			_get_rects(src_rect, dst_rect);

			_texture->draw_rect_region(ci, dst_rect, src_rect, Color(1, 1, 1), false, false);
		} break;
	}
}

void Sprite1D::set_texture(const Ref<Texture2D> &p_texture) {
	if (p_texture == _texture) {
		return;
	}

	if (_texture.is_valid()) {
		_texture->disconnect(CoreStringNames::get_singleton()->changed, callable_mp(this, &Sprite1D::_texture_changed));
	}

	_texture = p_texture;

	if (_texture.is_valid()) {
		_texture->connect(CoreStringNames::get_singleton()->changed, callable_mp(this, &Sprite1D::_texture_changed));
		_frame_count = _texture->get_height();
	}

	queue_redraw();
	_texture_changed();
	emit_signal(SceneStringNames::get_singleton()->texture_changed);
	item_rect_changed();
}

Ref<Texture2D> Sprite1D::get_texture() const {
	return _texture;
}

void Sprite1D::set_frame(const int p_frame) {
	ERR_FAIL_INDEX(p_frame, _frame_count);

	if (_frame != p_frame) {
		item_rect_changed();
	}

	_frame = p_frame;

	emit_signal(SceneStringNames::get_singleton()->frame_changed);
}

int Sprite1D::get_frame() const {
	return _frame;
}

int Sprite1D::get_frame_count() const {
	return _frame_count;
}

Rect2 Sprite1D::get_rect() const {
	if (_texture.is_null()) {
		return Rect2(0, 0, 1, 1);
	}

	int size = _texture->get_width();

	real_t dest_offset = -size / 2;
	if (get_viewport() && get_viewport()->is_snap_2d_transforms_to_pixel_enabled()) {
		dest_offset = Math::floor(dest_offset);
	}

	return Rect2(dest_offset, 0, size, 1);
}

void Sprite1D::_validate_property(PropertyInfo &property) const {
	if (property.name == "frame") {
		property.hint = PROPERTY_HINT_RANGE;
		property.hint_string = "0," + itos(_frame_count - 1) + ",1";
		property.usage |= PROPERTY_USAGE_KEYING_INCREMENTS;
	}
}

void Sprite1D::_texture_changed() {
	// Changes to the texture need to trigger an update to make
	// the editor redraw the sprite with the updated texture.
	if (_texture.is_valid()) {
		_frame_count = _texture->get_height();
		queue_redraw();
	}
}

Sprite1D::Sprite1D() {
	set_texture_filter(TextureFilter::TEXTURE_FILTER_NEAREST);
}

void Sprite1D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_texture", "texture"), &Sprite1D::set_texture);
	ClassDB::bind_method(D_METHOD("get_texture"), &Sprite1D::get_texture);

	ClassDB::bind_method(D_METHOD("set_frame", "frame"), &Sprite1D::set_frame);
	ClassDB::bind_method(D_METHOD("get_frame"), &Sprite1D::get_frame);
	ClassDB::bind_method(D_METHOD("get_frame_count"), &Sprite1D::get_frame_count);

	ClassDB::bind_method(D_METHOD("get_rect"), &Sprite1D::get_rect);

	ADD_SIGNAL(MethodInfo("frame_changed"));
	ADD_SIGNAL(MethodInfo("texture_changed"));

	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "texture", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "set_texture", "get_texture");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "frame"), "set_frame", "get_frame");
}
