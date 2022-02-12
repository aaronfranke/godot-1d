#include "register_types.h"

#include "nodes/node_1d.h"

void register_1d_types() {
	ClassDB::register_class<Node1D>();
}

void unregister_1d_types() {}
