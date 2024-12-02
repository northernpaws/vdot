extends Button

@onready var tooltip: Control = %MenuTooltip
@onready var timer: Timer = $TooltipTimer

@export var label: String

var tooltip_visable: bool = false

# Called when the node enters the scene tree for the first time.
func _ready() -> void:
	connect('mouse_entered', _mouse_entered)
	connect('mouse_exited', _mouse_exited)
	
	timer.timeout.connect(_show_tooltip)

# Called every frame. 'delta' is the elapsed time since the previous frame.
func _process(delta: float) -> void:
	if tooltip_visable:
		var x = global_position.x + size.x
		var y = global_position.y
		tooltip.set_position(Vector2(x, y))

func _show_tooltip():
	timer.stop()
	tooltip_visable = true
	tooltip.show()

func _mouse_entered():
	timer.start(0.5)
	
func _mouse_exited():
	timer.stop()
	tooltip_visable = false
	tooltip.hide()
