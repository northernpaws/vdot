extends Window

@onready var model_type_options: OptionButton = $VBoxContainer/ModelSetup/HBoxContainer/HBoxContainer/ModelTypeOptions
@onready var load_model_button: Button = $VBoxContainer/ModelSetup/HBoxContainer/LoadModelButton
@onready var load_model_dialog: FileDialog = $LoadModelDialog

@export var avatar_manager: AvatarManager

var selected_model_format: ModelFormat

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	load_model_dialog.hide()
	
	model_type_options.clear()
	for format in ModelLoader.get_model_formats():
		model_type_options.add_item(format.get_format_loader_name())
		model_type_options.set_item_metadata(model_type_options.item_count-1, format)
		if !selected_model_format:
			selected_model_format = format

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func _on_model_type_options_item_selected(index: int) -> void:
	selected_model_format = model_type_options.get_item_metadata(index)

func _on_load_model_button_pressed() -> void:
	if !selected_model_format:
		push_warning("No model format selected!")
		return

	var extensions = selected_model_format.get_recognized_extensions()
	for extension in extensions:
		load_model_dialog.add_filter("*." + extension, selected_model_format.get_format_loader_name())
	
	load_model_dialog.file_mode = FileDialog.FILE_MODE_OPEN_FILE
	load_model_dialog.access = FileDialog.ACCESS_FILESYSTEM
	load_model_dialog.show_hidden_files = true
	load_model_dialog.show()

func _on_create_avatar_button_pressed() -> void:
	var avatar: Avatar = Avatar.new()
	
	# NOTE: Add avatar to scene before adding the model
	#  to it, otherwise there are path problems.
	avatar_manager.add_child(avatar)
	
	avatar.global_position = avatar.get_viewport_rect().size / 2
	
	var model: Model = ModelLoader.load_from_path(load_model_dialog.current_path)
	if !model:
		push_error("Failed to load model!")
		return

	avatar.add_child(model)
	
	
