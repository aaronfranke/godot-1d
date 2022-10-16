extends Node

func _ready() -> void:
	add_child(Node1D.new())
	add_child(StaticBody1D.new())
	print("Hello GDScript!")
