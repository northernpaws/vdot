extends Node2D

@onready var cubismModel: CubismModel = $Sprite/CubismModel
@onready var fileDialog: FileDialog = $FileDialog
@onready var optionsWindow: Window = $OptionsWindow

@export_category("Live2D Model")
@export_file("*.model3.json") var model: String

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	if model:
		load_model(model)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func load_model(path: String):
	model = path
	
	print("Loading new Live2D model ", model)
	
	cubismModel.clear()
	cubismModel.assets = model

func open_model_file_dialog():
	fileDialog.show()

func _on_file_dialog_file_selected(path: String) -> void:
	load_model(path)
