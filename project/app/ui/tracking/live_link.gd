extends MarginContainer

@onready var settings_panel: Control = $LiveLinkSettings
@onready var initialize_panel: Control = $LiveLinkUninitialized
@onready var server_status: Label = $LiveLinkSettings/StatusBarContainer/StatusBar/ServerStatus
@onready var tracker_list: ItemList = $LiveLinkSettings/HSplitContainer/TrackerListContainer/TrackerList
@onready var tracker_settings: TrackerSettings = $LiveLinkSettings/HSplitContainer/TrackerSettings


# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	if LiveLinkInterface.is_initialized():
		initialize_panel.hide()
		settings_panel.show()
	else:
		settings_panel.hide()
		initialize_panel.show()
		
	LiveLinkInterface.tracker_connected.connect(_tracker_connected)
	
	_update_ui()

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	pass

func _update_ui():
	var status = "Uninitialized"
	
	if LiveLinkInterface.is_initialized():
		status = "Running"
	else:
		status = "Offline"
		
	var addresses = ""
	var first = true
	for ip in IP.get_local_addresses():
		# TODO: need to expand to properly find all local ranges
		if ip.begins_with("10.") or ip.begins_with("172.16.") or ip.begins_with("192.168."):
			if first:
				addresses = ip
				first = false
			else:
				addresses = addresses + ", " + ip
	
	server_status.text = "Server: %s - Address: %s - Port: %d" % [status, addresses, LiveLinkInterface.server.port]
	
	tracker_list.clear()
	for key in LiveLinkInterface.trackers:
		var tracker = LiveLinkInterface.trackers[key]
		var index = tracker_list.add_item((tracker as LiveLinkFaceTracker).get_tracker_name())
		tracker_list.set_item_metadata(index, tracker)

func _on_initialize_button_pressed() -> void:
	var err = LiveLinkInterface.initialize()
	
	if err != true:
		print("Error initializing LiveLink interface")
	else:
		initialize_panel.hide()
		settings_panel.show()
	
	_update_ui()

func _tracker_connected(tracker: LiveLinkFaceTracker):
	var index = tracker_list.add_item(tracker.get_tracker_name())
	tracker_list.set_item_metadata(index, tracker)

func _tracker_disconnected(tracker: LiveLinkFaceTracker):
	for i in range(tracker_list.item_count):
		if tracker_list.get_item_metadata(i) == tracker:
			tracker_list.remove_item(i)

func _on_tracker_list_item_selected(index: int) -> void:
	var tracker: Tracker = tracker_list.get_item_metadata(index)
	tracker_settings.set_tracker(tracker)
