#include "game.h"

void resize_game(Game* game, int width, int height)
{
    game->width = width;
    game->height = height;
    game->left_pad.size = 200;
    game->right_pad.size = 200;
    restart_game(game);
}

void restart_game(Game* game)
{
    game->score[0] = 0;
    game->score[1] = 0;

    new_round(game);
}

void new_round(Game* game)
{
    float center_x;
    float center_y;

    center_x = game->width / 2;
    center_y = game->height / 2;

    move_pad(&(game->left_pad), center_y - game->left_pad.size/2, game->height);
    move_pad(&(game->right_pad), center_y - game->right_pad.size/2, game->height);
    start_ball(&(game->ball), center_x, center_y);

    // I have no idea how to display strings on screen, I tried & failed.
    printf("Score: %d - %d\n", game->score[0], game->score[1]);
}


void update_game(Game* game, double time)
{
    #define BALL_YCOLLIDE_WITH_LPADLE game->left_pad.position  < game->ball.y && game->left_pad.position + game->left_pad.size > game->ball.y
    #define BALL_YCOLLIDE_WITH_RPADLE game->right_pad.position < game->ball.y && game->right_pad.position + game->right_pad.size > game->ball.y
    #define BALL_XCOLLIDE_WITH_LPADLE game->ball.x - game->ball.radius < PAD_WIDTH && game->ball.x + game->ball.radius > 0
    #define BALL_XCOLLIDE_WITH_RPADLE game->ball.x + game->ball.radius > game->width - PAD_WIDTH && game->ball.x - game->ball.radius < game->width

    update_ball(&(game->ball), time);
    if (BALL_XCOLLIDE_WITH_LPADLE && BALL_YCOLLIDE_WITH_LPADLE) {
        game->ball.x = game->ball.radius + 50;
        game->ball.speed_x *= -1.1;
    }
    if (BALL_XCOLLIDE_WITH_RPADLE && BALL_YCOLLIDE_WITH_RPADLE) {
        game->ball.x = game->width - game->ball.radius - 50;
        game->ball.speed_x *= -1.1;
    }
    if (game->ball.y - game->ball.radius < 0) {
        game->ball.y = game->ball.radius;
        game->ball.speed_y *= -1;
    }
    if (game->ball.y + game->ball.radius > game->height) {
        game->ball.y = game->height - game->ball.radius;
        game->ball.speed_y *= -1;
    }
    if (game->ball.x + game->ball.radius < 0) {
        game->score[1]++;
        new_round(game);
    }
    if (game->ball.x - game->ball.radius > game->width) {
        game->score[0]++;
        new_round(game);
    }
}

void move_left_pad(Game* game, float position)
{
    move_pad(&(game->left_pad), position, game->height);
}

void move_right_pad(Game* game, float position)
{
    move_pad(&(game->right_pad), position, game->height);
}

