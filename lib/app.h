#ifndef APP_H
#define APP_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "debug.h"

typedef struct AppContext_s * AppContext;

#define NO_SDL_RENDERER (-1)

NODISCARD
/**
 * Initualizes SDL and creates an SDL window with GL context.
 * Additionally initializes glew!
 *
 * @param SDL_initFlags Flags to send to `SDL_Init()`
 * @param SDL_winFlags Flags to send to `SDL_CreateWindow()`
 * @param SDL_rendFlags Flags to send to `SDL_CreateRenderer()`, or NO_SDL_RENDERER if no renderer is desired.
 * @param winTitle Title to give the initial window
 * @param win_x initial x position of the window
 * @param win_y initial y position of the window
 * @param win_w initial width of the window
 * @param win_h initial height of the window
 *
 * @return `EXIT_SUCCESS` (`0`) if everything initialized as expected. Otherwise, you will have to check the error with `getError()`
 */
AppContext initApplication(Uint32 SDL_initFlags,
                Uint32 SDL_winFlags,
                Uint32 SDL_rendFlags,
                const char * winTitle,
                Uint32 win_x, Uint32 win_y,
                Uint32 win_w, Uint32 win_h);

void closeApplication(AppContext);

float getAspectRatio(AppContext);
int getWindowCenterX(AppContext);
int getWindowCenterY(AppContext);

#endif