#ifndef __MY_GLOBALS_H__
#define __MY_GLOBALS_H__

/* These values depends on the map. currently I am using a 20.000 x 20.000 map. */
#define X_AXIS_LIMIT 10000
#define Y_AXIS_LIMIT 10000

#define WINDOW_SCALE_DIVIDER 40
/* Divide by 40 to get a window size of 500, which fits well in my screen.
 * Maybe in the future we can make this more dynamic, according to the map and
 * to the screen size. */
#define WINDOW_SIZE_X (X_AXIS_LIMIT * 2) / WINDOW_SCALE_DIVIDER
#define WINDOW_SIZE_Y (Y_AXIS_LIMIT * 2) / WINDOW_SCALE_DIVIDER

/* Maximum range of a sonar in milimiters */
#define SONAR_MAX_RANGE 5000

#endif
