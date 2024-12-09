class_name TrackerSettings extends VBoxContainer

@onready var tracker_name_label: Label = $TrackerName
@onready var tracker_desc_label: Label = $TrackerDescription

@onready var facial_tracker_settings: FacialTrackerSettings = $FacialTrackerSettings

func set_tracker(tracker: Tracker):
	tracker_name_label.text = tracker.get_tracker_name()
	tracker_desc_label.text = tracker.get_tracker_description()
	
	facial_tracker_settings.hide()
	
	if tracker is FaceTracker:
		facial_tracker_settings.show()
		facial_tracker_settings.set_tracker(tracker)


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	pass # Replace with function body.

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass
