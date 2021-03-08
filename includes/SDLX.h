#ifndef SDLX_H
#define SDLX_H

# include "SDL2/SDL.h"
# include "SDL2/SDL_image.h"

# include "SDLX_config.h"
# include "SDLX_structs.h"

void			SDLX_start(SDLX_Display *dest);

SDLX_Display	*SDLX_GetDisplay(void);

void			SDLX_close(void);

#endif