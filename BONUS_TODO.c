
Improvements to global light:

Morning ? soft orange/pink
Noon ? bright blue
Evening ? purple/red
Night ? dark blue/black

# define MORNING 0xFFB380   // soft orange / soft pink
# define NOON    0xFFFF99   // bright blue / yellow
# define EVENING 0xCC3366   // purple/red
# define NIGHT   0x14183C   // dark blue

Instead of one LERP, have four LERP interpolation between them in a cicle: to test still !!!!!

Morining -> Noon (starting color) -> Evening -> Night -> Morning (...)

We could assume global_light now represents the time of day as a fraction:

0.0 -> Morning
0.25 -> Noon
0.5 -> Evening
0.75 -> Night
1.0 -> Morning (wrap-around)

int lerp_color(int Start_color, int End_color, double progress)
{
	int r;
	int g;
	int b;

	r = ((Start_color >> 16) & 0xFF) * (1 - t) + ((End_color >> 16) & 0xFF) * t;
	g = ((Start_color >> 8) & 0xFF)  * (1 - t) + ((End_color >> 8) & 0xFF)  * t;
	b = (Start_color & 0xFF)         * (1 - t) + (End_color & 0xFF)         * t;
	if (r > 255)
		r = 255;
	if (r < 0)
		r = 0;
	if (g > 255)
		g = 255;
	if (g < 0)
		g = 0;
	if (b > 255)
		b = 255;
	if (b < 0)
		b = 0;
	return (r << 16) | (g << 8) | b;
}

int lerp_day_cycle(double global_light)
{
	global_light = fmod(global_light, 1.0); // wrap around

	if (global_light < 0.25) // Morning -> Noon
		return lerp_color(MORNING, NOON, global_light / 0.25);
	else if (global_light < 0.5) // Noon -> Evening
		return lerp_color(NOON, EVENING, (global_light - 0.25) / 0.25);
	else if (global_light < 0.75) // Evening -> Night
		return lerp_color(EVENING, NIGHT, (global_light - 0.5) / 0.25);
	else // Night -> Morning
		return lerp_color(NIGHT, MORNING, (global_light - 0.75) / 0.25);
}

Concept

These values need to be in same range as global_light (0.2 ? 1.0).

# define DAY_CLUE   "At dawn's first golden ray, the hidden key may stay"
# define NIGHT_CLUE "Where the last light fades, your path awaits"
# define MAZE_CLUE  "In the heart of the maze, where walls conceal, the truth will reveal"

Day clue: Appears in the first room when the player starts.
	- Gives a poetic hint for where the key is.
	- Key only spawns in the easternmost room and only during day.

Night clue: Appears immediately after the player collects the key.
	- Gives a poetic hint for where the invisible door is.
	- Door only spawns in the westernmost room and only at night.

Maze clue: Appears after opening the door.
	- Hints at the ?heart? of the maze: room to - > win/leave the maze
	- Door should blend with wall (invisible): by having the same texture as the wall. Clue references hidden walls.

// helper functions to set DAY/NIGHT transition

bool is_night(double global_light)
{
    return (global_light <= NIGHT_START);
}

bool is_day(double global_light)
{
    return (global_light >= NIGHT_END);
}
------------------------

//struct of key/doors (?)

typedef struct s_item
{
    double  x;        // world x coordinate
    double  y;        // world y coordinate
    bool     found;  // has the player picked it up?
    char    *clue;      // clue text (use the DEFINE in the function)
}           t_item;

// How to detect interaction ?

double dx = player.x - items.x; 
double dy = player.y - items.y;
double distance = sqrt(dx * dx + dy * dy); -> hipotenusa = distancia entre 2 objectos

if (distance < 0.5 && !items.found)
{
    items.found = true;
    show_clue(items.clue); // function to render the clue text (already have for the FPS i think - render fps)
}

or add button to display clue text

// !!!! ADD CROSSHAIR TO BE EASIER TO INTERACT



PSEUDO CODE
// Global state
bool has_key = false; (perhaps best aproach is struct item)
bool door_opened = false;

// Game loop (after rendering each frame)
void update_clues(t_data *data)
{
    if (!has_key)
    {
        // Player sees day clue only during day (?)
        if (data->global_light > 0.5) // adjust threshold as needed
            display_text(DAY_CLUE, BOTTOM_RIGHT);
    }
    else if (has_key && !door_opened)
    {
        // Player sees night clue only at night
        if (data->global_light < 0.5)
            display_text(NIGHT_CLUE, BOTTOM_RIGHT);
    }
    else if (door_opened)
    {
        // Player sees maze clue after opening door
        display_text(MAZE_CLUE, BOTTOM_RIGHT);
    }
}

// Key spawn logic
void spawn_key(t_data *data)
{
    if (data->global_light > 0.5 && player_in_east_room())
        show_key();
}

// Door spawn logic
void spawn_door(t_data *data)
{
    if (data->global_light < 0.5 && player_in_target_room())
        show_invisible_door(); // door uses wall texture
}

// Interaction logic
void player_pickup_key()
{
    has_key = true;
    play_sound(KEY_PICKUP);
}

void player_open_door()
{
    if (door_is_visible() && player_near_door())
    {
        door_opened = true;
        play_sound(DOOR_OPEN);
    }
}


/* How to implement? - Ideas

Day clue ? key spawn */
if (is_day(global_light) && player_in_target_room())
    spawn_key();

/* Key collected ? night clue */

if (key.collected)
    show_clue(NIGHT_CLUE);

/* Night ? door appears */

if (is_night(global_light) && player_in_target_room() && !door_opened && has_key)
    spawn_door();

/* Door oppened - > maze clue */

if (door_opened)
    show_clue(MAZE_CLUE);

/* to end game */

if (player in target room && has_key && door_opened)
{
    change_door_texture_to_door()
    if (player_interacts_with_door())
    {
        end_game();
    }
}