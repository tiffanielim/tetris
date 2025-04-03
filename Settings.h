//
// Created by Tiffanie Lim on 6/5/24.
//

///defines global constants used throughout the Tetris game

#ifndef CS3A_TETRIS_SETTINGS_H
#define CS3A_TETRIS_SETTINGS_H
namespace te
{
    const int BG_MARGIN = 20; //padding around game area

    //dimensions of the Tetris grid
    const int FIELD_WIDTH = 10;
    const int FIELD_HEIGHT = 20;

    const float NORMAL_SPEED = 0.2f; //time (in seconds) between automatic block drops
    const int SPEED_UP_DIVIDER = 4; //increase speed when down key or s key is held
    const int QUEUE_SIZE = 10; //number of upcoming blocks shown in the preview queue
}
#endif //CS3A_TETRIS_SETTINGS_H
