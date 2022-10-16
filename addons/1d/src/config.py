def can_build(env, platform):
    return True


def configure(env):
    pass


def get_doc_classes():
    return [
        "AudioListener1D",
        "AudioPlayer1D",
        "Camera1D",
        "Node1D",
        "Sprite1D",
        # Physics.
        "Area1D",
        "CollisionObject1D",
        "KinematicBody1D",
        "PhysicsServer1D",
        "StaticBody1D",
    ]


def get_doc_path():
    return "doc_classes"
