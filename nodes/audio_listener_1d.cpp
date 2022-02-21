#include "audio_listener_1d.h"

#include "scene/2d/listener_2d.h"

void AudioListener1D::set_current(const bool p_current) {
	if (p_current) {
		_real_listener->make_current();
	} else {
		_real_listener->clear_current();
	}
}

bool AudioListener1D::is_current() const {
	return _real_listener->is_current();
}

void AudioListener1D::_bind_methods() {
	ClassDB::bind_method(D_METHOD("set_current", "current"), &AudioListener1D::set_current);
	ClassDB::bind_method(D_METHOD("is_current"), &AudioListener1D::is_current);

	ADD_PROPERTY(PropertyInfo(Variant::BOOL, "current"), "set_current", "is_current");
}

AudioListener1D::AudioListener1D() {
	_real_listener = memnew(Listener2D);
	add_child(_real_listener);
	_real_listener->make_current();
}
