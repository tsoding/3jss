int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;
    game = new Game{};

    sec(SDL_Init(SDL_INIT_VIDEO));

    game->window =
        sec(SDL_CreateWindow(
                "3jss",
                0, 0,
                SCREEN_WIDTH, SCREEN_HEIGHT,
                SDL_WINDOW_RESIZABLE));

    game->renderer =
        sec(SDL_CreateRenderer(
                game->window, -1,
                SDL_RENDERER_ACCELERATED));

    sec(SDL_RenderSetLogicalSize(game->renderer,
                SCREEN_WIDTH,
                SCREEN_HEIGHT));

    while (!game->quit) {
        SDL_Event event = {};
        while (SDL_PollEvent(&event)) {
            game->handle_event(&event);
        }

        game->update(UPDATE_DELTA_TIME_SECS);
        game->render();

        SDL_Delay(UPDATE_DELTA_TIME_MS);
    }

    SDL_Quit();

    return 0;
}
