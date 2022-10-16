#pragma once

#include "node_1d.h"

namespace godot {
	class AudioListener2D;
}

using namespace godot;

class AudioListener1D : public Node1D {
	GDCLASS(AudioListener1D, Node1D);

	// Viewport is hard-coded to work with AudioListener2D (and
	// AudioListener3D). We'll just use AudioListener2D as a
	// proxy so that we don't have to modify Viewport.
	AudioListener2D *_real_listener;

protected:
	static void _bind_methods();

public:
	void set_current(const bool p_current);
	bool is_current() const;

	AudioListener1D();
};
