#ifndef THREEJSS_PLAYER_HPP_
#define THREEJSS_PLAYER_HPP_

#include "./3jss_tile.hpp"

struct Sliding_Animation
{
    Tile_Coord target;
    float a;
};

struct Player
{
    enum class State {
        Idle = 0,
        Sliding
    };

    Tile_Coord tile;
    State state;

    Sliding_Animation sliding;

    Raw_Coord raw_center();
    void render();
    void update(Seconds dt);
    void step_to(Tile_Direction dir);
};

#endif  // THREEJSS_PLAYER_HPP_
