#include "app.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//	What functions needed?
//
//	* Wrap:
//	 - SDL_Init
//	 - SDL_CreateWindow
//	 - SDL_GL_CreateContext
//	 - glewInit

struct AppContext_s
{
    SDL_Window *w;
    SDL_Renderer *r;
    SDL_GLContext *glContext;
    int ww, wh;
    int mx, my;
};

NODISCARD
AppContext newAppContext()
{
    AppContext context = calloc(1,sizeof(struct AppContext_s));
    return context;
}

NODISCARD
AppContext initApplication(Uint32 SDL_initFlags,
                Uint32 SDL_winFlags,
                Uint32 SDL_rendFlags,
                const char * winTitle,
                Uint32 win_x, Uint32 win_y,
                Uint32 win_w, Uint32 win_h)
{
    AppContext context = newAppContext();
    if(!context)
    {
        setError(ERR_CODE,ERR_NOMEM);
        return NULL;
    }

    if(SDL_Init(SDL_initFlags) != EXIT_SUCCESS)
    {
        setError(ERR_MESG,"SDL Initialization error: %s",SDL_GetError());
        return NULL;
    }

    (context->w) = SDL_CreateWindow(winTitle, win_x, win_y, win_w, win_h, SDL_winFlags);
    if(!(context->w))
    {
        setError(ERR_MESG,"SDL Window creation failure: %s",SDL_GetError());
        SDL_Quit();
        return NULL;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    (context->glContext) = SDL_GL_CreateContext(context->w);
    if(!(context->glContext))
    {
        setError(ERR_MESG,"SDL GL Context creation failure: %s",SDL_GetError());
        SDL_DestroyWindow(context->w);
        SDL_Quit();
        return NULL;
    }

    GLenum glewError = glewInit();
    if(glewError != GLEW_OK)
    {
        setError(ERR_MESG,"Glew initialization failure: %s",glewGetErrorString(glewError));
        SDL_GL_DeleteContext(context->glContext);
        SDL_DestroyWindow(context->w);
        SDL_Quit();
        return NULL;
    }
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback,0);

    if(SDL_rendFlags != NO_SDL_RENDERER)
    {
        (context->r) = SDL_CreateRenderer(context->w, (-1), SDL_rendFlags);
        if(!(context->r))
        {
            setError(ERR_MESG,"SDL Renderer creation failure: %s",SDL_GetError());
            SDL_GL_DeleteContext(context->glContext);
            SDL_DestroyWindow(context->w);
            SDL_Quit();
            return NULL;
        }
    }
    else
    {
        (context->r) = NULL;
    }

    stbi_set_flip_vertically_on_load(true);

    return context;
}

void closeApplication(AppContext context)
{
    if(context->glContext)
    {
        SDL_GL_DeleteContext(context->glContext);
    }
    if(context->r)
    {
        SDL_DestroyRenderer(context->r);
    }
    if(context->w)
    {
        SDL_DestroyWindow(context->w);
    }
    SDL_Quit();
}

float getAspectRatio(AppContext context)
{
    return context->ww/(float)context->wh;
}

int getWindowCenterX(AppContext context)
{
    return context->ww/2.0;
}

int getWindowCenterY(AppContext context)
{
    return context->wh/2.0;
}