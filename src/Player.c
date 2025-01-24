#include "Player.h"

/***********************************************************************************************************************
Static Constants
***********************************************************************************************************************/
const PlayerConstantsType PLAYER_CONSTANTS = { 90, 20, 100, 255, 255, 255 };
/***********************************************************************************************************************
Static Functions
***********************************************************************************************************************/
static void Player_FixBoundry( Player* player, int32_t x, int32_t y, int32_t width, int32_t height );

/***********************************************************************************************************************
Function Implementations
***********************************************************************************************************************/
void Player_Init( Player* player, int32_t x, int32_t y )
{
    Paddle_Init( &player->paddle, x, y, PLAYER_CONSTANTS.PLAYER_WIDTH, PLAYER_CONSTANTS.PLAYER_HEIGHT,
                 PLAYER_CONSTANTS.PLAYER_COLOR_R, PLAYER_CONSTANTS.PLAYER_COLOR_G, PLAYER_CONSTANTS.PLAYER_COLOR_B );
    player->x = x;
    player->y = y;
}

void Player_Update( Player* player, Event* ev, Time* deltaTime )
{
    if ( ev->type == EVENT_KEY )
    {
        if ( ev->keyEvent.type == KEY_PRESSED )
        {

            switch ( ev->keyEvent.key )
            {
                case KEY_UP:
                    player->velocity = -1;
                    break;
                case KEY_DOWN:
                    player->velocity = 1;
                    break;
                default:
                    break;
            }
        }
        else if ( ev->keyEvent.type == KEY_RELEASED ) { player->velocity = 0; }
    }
    double value = player->velocity * PLAYER_CONSTANTS.PLAYER_SPEED * deltaTime->value * 0.01;
    player->y += value;
    Player_FixBoundry( player, 0, 0, 1280, 720 );
    player->paddle.y = player->y;
}

void Player_Render( Player* player ) { Paddle_Render( &player->paddle ); }

inline static void Player_FixBoundry( Player* player, int32_t x, int32_t y, int32_t width, int32_t height )
{
    if ( player->y < 0 ) { player->y = 0; }
    else if ( player->y > height - PLAYER_CONSTANTS.PLAYER_HEIGHT )
    {
        player->y = height - PLAYER_CONSTANTS.PLAYER_HEIGHT;
    }
    else if ( player->x < 0 ) { player->x = 0; }
    else if ( player->x > width - PLAYER_CONSTANTS.PLAYER_WIDTH ) { player->x = width - PLAYER_CONSTANTS.PLAYER_WIDTH; }
}