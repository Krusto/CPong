#include "Ball.h"
#include "Player.h"
#include "Renderer.h"
/***********************************************************************************************************************
Static Constants
***********************************************************************************************************************/
const BallConstantsType Ball_CONSTANTS = { 40, 20, 255, 255, 255 };
/***********************************************************************************************************************
Static Functions
***********************************************************************************************************************/
static int Ball_CheckCollisionPlayer( Ball* ball, Player* player );

static void Ball_FixBoundry( Ball* Ball, Player* player1, Player* player2, int32_t x, int32_t y, int32_t width,
                             int32_t height );

/***********************************************************************************************************************
Function Implementations
***********************************************************************************************************************/
void Ball_Init( Ball* ball, int32_t x, int32_t y, double velocityX, double velocityY )
{
    ball->position.x = x;
    ball->position.y = y;

    ball->velocityX = velocityX;
    ball->velocityY = velocityY;
    ball->acceleration = 0;
}

void Ball_Update( Ball* ball, Player* player1, Player* player2, Event* ev, Time* deltaTime )
{
    double valueX = ball->velocityX * Ball_CONSTANTS.Ball_SPEED * deltaTime->value * 0.01;
    double valueY = ball->velocityY * Ball_CONSTANTS.Ball_SPEED / 2 * deltaTime->value * 0.01;

    ball->position.x += valueX;
    ball->position.y += valueY;

    Ball_FixBoundry( ball, player1, player2, 0, 0, 1280, 720 );
}

void Ball_Render( Ball* ball )
{
    RendererCommandDrawCircle circle;
    circle.x = ball->position.x;
    circle.y = ball->position.y;
    circle.radius = Ball_CONSTANTS.Ball_RADIUS;
    circle.r = Ball_CONSTANTS.Ball_COLOR_R;
    circle.g = Ball_CONSTANTS.Ball_COLOR_G;
    circle.b = Ball_CONSTANTS.Ball_COLOR_B;
    RendererCmdDrawCircle( &circle );
}

inline static void Ball_FixBoundry( Ball* ball, Player* player1, Player* player2, int32_t x, int32_t y, int32_t width,
                                    int32_t height )
{
    if ( ball->position.y < 0 ) { ball->velocityY = 1.1; }
    else if ( ball->position.y > height - Ball_CONSTANTS.Ball_RADIUS ) { ball->velocityY = -1.1; }
    if ( ball->position.x < 0 )
    {
        ball->position.x = width / 2 - Ball_CONSTANTS.Ball_RADIUS;
        ball->velocityX = 1.1;
        player2->score += 1;
    }
    else if ( ball->position.x > width )
    {
        ball->position.x = width / 2 - Ball_CONSTANTS.Ball_RADIUS;
        ball->velocityX = -1.1;
        player1->score += 1;
    }

    if ( Ball_CheckCollisionPlayer( ball, player1 ) == 1 ) {}
    else if ( Ball_CheckCollisionPlayer( ball, player2 ) == 1 ) {}
}

int Ball_CheckCollisionPlayer( Ball* ball, Player* player )
{
    int ballLEFT = ball->position.x;
    int ballTOP = ball->position.y;
    int ballRIGHT = ball->position.x + Ball_CONSTANTS.Ball_RADIUS;
    int ballBOTTOM = ball->position.y + Ball_CONSTANTS.Ball_RADIUS;
    int playerLEFT = player->position.x;
    int playerTOP = player->position.y;
    int playerRIGHT = player->position.x + PLAYER_CONSTANTS.PLAYER_WIDTH;
    int playerBOTTOM = player->position.y + PLAYER_CONSTANTS.PLAYER_HEIGHT;
    if ( ballLEFT < playerRIGHT && ballRIGHT > playerLEFT && ballTOP < playerBOTTOM && ballBOTTOM > playerTOP )
    {
        double hitPosition = ( ball->position.y - player->position.y ) / ( double ) PLAYER_CONSTANTS.PLAYER_HEIGHT;

        if ( hitPosition > 0.5 ) { ball->velocityY *= 1.1; }
        else { ball->velocityY *= -1.1; }

        ball->velocityX *= -1.1;
    }
    return 0;
}