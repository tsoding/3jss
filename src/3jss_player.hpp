#ifndef THREEJSS_PLAYER_HPP_
#define THREEJSS_PLAYER_HPP_

#include "./3jss_tile.hpp"

struct Player
{
    Tile_Coord tile;

    void render();
};

#endif  // THREEJSS_PLAYER_HPP_
