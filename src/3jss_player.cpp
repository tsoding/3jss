#include "./3jss_player.hpp"

void Player::render()
{
    fill_rect(
        game->renderer,
        game->camera.to_screen(rect_of_tile(tile)),
        PLAYER_COLOR);
}
