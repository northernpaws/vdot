class_name FacialTrackerSettings extends HSplitContainer

var tracker: FaceTracker

@onready var blendshapes_list: ItemList = $SettingsContainer/TabContainer/BlendShapes/BlendShapesList
@onready var preview_mesh: MeshInstance3D = $PreviewContainer/PreviewTexture/PreviewViewport/MeshInstance3D

func set_tracker(tracker: FaceTracker):
	if self.tracker:
		self.tracker.blend_shapes_updated.disconnect(_tracker_blend_shapes_updated)
	
	self.tracker = tracker
	
	tracker.blend_shapes_updated.connect(_tracker_blend_shapes_updated)

func _enter_tree() -> void:
	if tracker:
		tracker.blend_shapes_updated.connect(_tracker_blend_shapes_updated)
	
func _exit_tree() -> void:
	if tracker:
		tracker.blend_shapes_updated.disconnect(_tracker_blend_shapes_updated)

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
	
func _tracker_blend_shapes_updated():
	blendshapes_list.clear()
	
	var shapes = tracker.blend_shapes
	
	for index in range(shapes.size()):
		var name = tracker.get_blend_shape_name(index)
		var weight = shapes[index]
		blendshapes_list.add_item("%d: Shape: %s = %f" % [index, name, weight])	
	
	# TODO: We should be using a unifed expressions model to avoid this ARKit conversion.
	for arkit_shape in range(51):
		var shape_index = tracker.get_arkit_blend_shape(arkit_shape)
		if shape_index != 143: # max supported blend shape
			var weight = shapes[shape_index]
			if weight != 0:
				preview_mesh.set_blend_shape_value(preview_mesh.find_blend_shape_by_name(KEY_MAP[arkit_shape]), weight)

const KEY_MAP = [
	"eyeBlinkLeft",
	"eyeLookDownLeft",
	"eyeLookInLeft",
	"eyeLookOutLeft",
	"eyeLookUpLeft",
	"eyeSquintLeft",
	"eyeWideLeft",
	"eyeBlinkRight",
	"eyeLookDownRight",
	"eyeLookInRight",
	"eyeLookOutRight",
	"eyeLookUpRight",
	"eyeSquintRight",
	"eyeWideRight",
	"jawForward",
	"jawRight",
	"jawLeft",
	"jawOpen",
	"mouthClose",
	"mouthFunnel",
	"mouthPucker",
	"mouthRight",
	"mouthLeft",
	"mouthSmileLeft",
	"mouthSmileRight",
	"mouthFrownLeft",
	"mouthFrownRight",
	"mouthDimpleLeft",
	"mouthDimpleRight",
	"mouthStretchLeft",
	"mouthStretchRight",
	"mouthRollLower",
	"mouthRollUpper",
	"mouthShrugLower",
	"mouthShrugUpper",
	"mouthPressLeft",
	"mouthPressRight",
	"mouthLowerDownLeft",
	"mouthLowerDownRight",
	"mouthUpperUpLeft",
	"mouthUpperUpRight",
	"browDownLeft",
	"browDownRight",
	"browInnerUp",
	"browOuterUpLeft",
	"browOuterUpRight",
	"cheekPuff",
	"cheekSquintLeft",
	"cheekSquintRight",
	"noseSneerLeft",
	"noseSneerRight",
	"tongueOut",
	"headYaw",
	"headPitch",
	"headRoll",
	"leftEyeYaw",
	"leftEyePitch",
	"leftEyeRoll",
	"rightEyeYaw",
	"rightEyePitch",
	"rightEyeRoll"
]
