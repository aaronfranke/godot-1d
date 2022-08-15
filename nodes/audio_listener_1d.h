#ifndef AUDIO_LISTENER_1D_H
#define AUDIO_LISTENER_1D_H

#include "node_1d.h"
class AudioListener2D;

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

#endif // AUDIO_LISTENER_1D_H
