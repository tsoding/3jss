#include "./3jss_chunk.hpp"

void Chunk::generate_walls(Rng *rng)
{
    rng->seed_with(coord.x * 12389023 + coord.y);

    for (size_t y = 0; y < CHUNK_SIZE; ++y) {
        for (size_t x = 0; x < CHUNK_SIZE; ++x) {
            walls[y][x] = rng->random() % 2;
        }
    }
}

bool Chunk::wall_at(Tile_Coord tile) const
{
    assert(0 <= tile.x && tile.x < (int) CHUNK_SIZE);
    assert(0 <= tile.y && tile.y < (int) CHUNK_SIZE);
    return walls[tile.y][tile.x];
}
