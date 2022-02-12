#ifndef SPRITE_1D_H
#define SPRITE_1D_H

#include "node_1d.h"
#include "scene/resources/texture.h"

class Sprite1D : public Node1D {
	GDCLASS(Sprite1D, Node1D);

	Ref<Texture2D> _texture;

	int _frame_count = 1;
	int _frame = 0;

	void _get_rects(Rect2 &r_src_rect, Rect2 &r_dst_rect) const;
	void _texture_changed();

protected:
	void _notification(const int p_what);
	static void _bind_methods();
	virtual void _validate_property(PropertyInfo &property) const override;

public:
#ifdef TOOLS_ENABLED
	virtual Rect2 _edit_get_rect() const override;
	virtual bool _edit_use_rect() const override;
#endif

	void set_texture(const Ref<Texture2D> &p_texture);
	Ref<Texture2D> get_texture() const;

	void set_frame(const int p_frame);
	int get_frame() const;
	int get_frame_count() const;

	Rect2 get_rect() const;
	virtual Rect2 get_anchorable_rect() const override;

	Sprite1D();
};

#endif // SPRITE_1D_H
