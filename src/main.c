#include "main.h"
#include "app.h"
#include "cgfx.h"

int main(int argc, char * argv[])
{
    printf("Hello, world!\n");
    AppContext appContext =
        initApplication(SDL_INIT_EVERYTHING,
                        SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_RENDERER_ACCELERATED,
                        NO_SDL_RENDERER,
                        "BCRES Tester",
                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                        800, 640);
    if(!appContext)
    {
        fprintf(stderr,"Failed to open application: %s\n",getError());
        return EXIT_FAILURE;
    }

    char filename[] = "models/cracker.bcres";
    CGFX cgfx = CGFX_ReadFile(filename);
    if(!cgfx)
    {
        fprintf(stderr,"Failed to read file \"%s\": %s\n",filename,getError());
        return EXIT_FAILURE;
    }
    printf("%s\n",CGFX_GetMetadata(cgfx));

    closeApplication(appContext);
    return EXIT_SUCCESS;
}