#ifndef THREEJSS_PLAYER_HPP_
#define THREEJSS_PLAYER_HPP_

#include "./3jss_tile.hpp"

template <typename T, size_t Capacity>
struct Ring_Buffer
{
    T elements[Capacity];
    size_t begin;
    size_t size;

    bool empty() const
    {
        return size == 0;
    }

    void nq(T element)
    {
        elements[(begin + size) % Capacity] = element;

        if (size < Capacity) {
            size += 1;
        } else {
            begin = (begin + 1) % Capacity;
        }
    }

    T dq()
    {
        assert(size > 0);
        T result = elements[begin];
        begin = (begin + 1) % Capacity;
        size -= 1;
        return result;
    }
};

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

    Ring_Buffer<Tile_Direction, PLAYER_STEP_BUFFER_SIZE> step_buffer;

    Raw_Coord raw_center();
    void render();
    void update(Seconds dt);
    void step_to(Tile_Direction dir);
};

#endif  // THREEJSS_PLAYER_HPP_
