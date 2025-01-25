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
static int Ball_CheckCollisionPlayer( Ball* ball, Point2i playerPosition );

static void Ball_FixBoundry( Ball* Ball, Point2i player1Pos, Point2i player2Pos, int32_t x, int32_t y, int32_t width,
                             int32_t height );

/***********************************************************************************************************************
Function Implementations
***********************************************************************************************************************/
void Ball_Init( Ball* Ball, int32_t x, int32_t y, double velocityX, double velocityY )
{
    Ball->position.x = x;
    Ball->position.y = y;
    Ball->velocityX = velocityX;
    Ball->velocityY = velocityY;
}

void Ball_Update( Ball* ball, Point2i player1Pos, Point2i player2Pos, Event* ev, Time* deltaTime )
{
    double valueX = ball->velocityX * Ball_CONSTANTS.Ball_SPEED * deltaTime->value * 0.01;
    double valueY = ball->velocityY * Ball_CONSTANTS.Ball_SPEED * deltaTime->value * 0.01;
    ball->position.x += valueX;
    ball->position.y += valueY;
    Ball_FixBoundry( ball, player1Pos, player2Pos, 0, 0, 1280, 720 );
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

inline static void Ball_FixBoundry( Ball* ball, Point2i player1Pos, Point2i player2Pos, int32_t x, int32_t y,
                                    int32_t width, int32_t height )
{
    if ( ball->position.y < 0 ) { ball->velocityY = -ball->velocityY; }
    else if ( ball->position.y > height - Ball_CONSTANTS.Ball_RADIUS ) { ball->velocityY = -ball->velocityY; }
    else if ( ball->position.x < 0 )
    {
        ball->position.x = width / 2 - Ball_CONSTANTS.Ball_RADIUS;
        ball->velocityX = -ball->velocityX;
    }
    else if ( ball->position.x > width - Ball_CONSTANTS.Ball_RADIUS )
    {
        ball->position.x = width / 2 - Ball_CONSTANTS.Ball_RADIUS;
        ball->velocityX = -ball->velocityX;
    }

    if ( Ball_CheckCollisionPlayer( ball, player1Pos ) == 1 )
    {
        ball->velocityX = -ball->velocityX;
        ball->velocityY = -ball->velocityY;
    }
    else if ( Ball_CheckCollisionPlayer( ball, player2Pos ) == 1 )
    {
        ball->velocityX = -ball->velocityX;
        ball->velocityY = -ball->velocityY;
    }
}

int Ball_CheckCollisionPlayer( Ball* ball, Point2i playerPosition )
{
    int ballLEFT = ball->position.x;
    int ballTOP = ball->position.y;
    int ballRIGHT = ball->position.x + Ball_CONSTANTS.Ball_RADIUS;
    int ballBOTTOM = ball->position.y + Ball_CONSTANTS.Ball_RADIUS;
    int playerLEFT = playerPosition.x;
    int playerTOP = playerPosition.y;
    int playerRIGHT = playerPosition.x + PLAYER_CONSTANTS.PLAYER_WIDTH;
    int playerBOTTOM = playerPosition.y + PLAYER_CONSTANTS.PLAYER_HEIGHT;
    if ( ballLEFT < playerRIGHT && ballRIGHT > playerLEFT && ballTOP < playerBOTTOM && ballBOTTOM > playerTOP )
    {
        return 1;
    }
    return 0;
}