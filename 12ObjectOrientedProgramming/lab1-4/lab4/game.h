#ifndef GAME_H
#define GAME_H

class Game
{
public:
    typedef struct {
        int x;
        int y;
    } cell;
    Game();
    int rows;
    int cols;
    cell randomCell();
};

#endif // GAME_H
