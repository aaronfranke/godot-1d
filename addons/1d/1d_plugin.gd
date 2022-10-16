@tool
extends EditorPlugin


const AREA_1D_ICON = preload("res://addons/1d/icons/Area1D.svg")
const AUDIO_LISTENER_1D_ICON = preload("res://addons/1d/icons/AudioListener1D.svg")
const AUDIO_PLAYER_1D_ICON = preload("res://addons/1d/icons/AudioPlayer1D.svg")
const CAMERA_1D_ICON = preload("res://addons/1d/icons/Camera1D.svg")
const COLLISION_OBJECT_1D_ICON = preload("res://addons/1d/icons/CollisionObject1D.svg")
const KINEMATIC_BODY_1D_ICON = preload("res://addons/1d/icons/KinematicBody1D.svg")
const NODE_1D_ICON = preload("res://addons/1d/icons/Node1D.svg")
const SPRITE_1D_ICON = preload("res://addons/1d/icons/Sprite1D.svg")
const STATIC_BODY_1D_ICON = preload("res://addons/1d/icons/StaticBody1D.svg")


func _enter_tree():
	var theme = get_editor_interface().get_base_control().get_theme()
	theme.set_icon("Area1D", "EditorIcons", AREA_1D_ICON)
	theme.set_icon("AudioListener1D", "EditorIcons", AUDIO_LISTENER_1D_ICON)
	theme.set_icon("AudioPlayer1D", "EditorIcons", AUDIO_PLAYER_1D_ICON)
	theme.set_icon("Camera1D", "EditorIcons", CAMERA_1D_ICON)
	theme.set_icon("CollisionObject1D", "EditorIcons", COLLISION_OBJECT_1D_ICON)
	theme.set_icon("KinematicBody1D", "EditorIcons", KINEMATIC_BODY_1D_ICON)
	theme.set_icon("Node1D", "EditorIcons", NODE_1D_ICON)
	theme.set_icon("Sprite1D", "EditorIcons", SPRITE_1D_ICON)
	theme.set_icon("StaticBody1D", "EditorIcons", STATIC_BODY_1D_ICON)
