#ifndef SDLX_CONFIG_H
# define SDLX_CONFIG_H

#ifdef EMCC
	# define DISPLAY_SCALE (3)
#else
	# define DISPLAY_SCALE (3)
#endif

# define WIN_TITLE	"Blaster"
# define WIN_WIDTH	(10 * 16 * DISPLAY_SCALE)
# define WIN_HEIGHT	(10 * 16 * DISPLAY_SCALE)
# define WIN_POS_X	(100)
# define WIN_POS_Y	(100)

# endif
