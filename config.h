#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#define WINDOW_TITLE "Tetris beta"

#define DT_USLEEP  30000

#define MATRIX_X (20+1)
#define MATRIX_Y (10+2)

#define SCORE_DISPLAY_Y (MATRIX_Y*(TILE_S+2))
#define SCORE_DISPLAY_X (2*TILE_S)

#define FONT_SIZE 22
#define FONT_FILE "tetris.ttf"
#define FONT_COLOR (SDL_Color){128,128,128}

#define TILESET_FILE "texture.bmp"
#define TILE_S 30

#define AUDIO_FILE "tetris.ogg"
#define AUDIO_RATE 22050
#define AUDIO_FORMAT AUDIO_S16SYS
/* mono */
#define AUDIO_CHANNELS 1
#define AUDIO_BUFFERS 4096

#define SCORE_FILENAME "scores.dat"
#define NB_HIGHSCORE 4
#define SCORE_PIECE 10
#define SCORE_DROP  1
#define SCORE_LINE  100
#define SCORE_BONUS 100


#endif // CONFIG_H_INCLUDED
