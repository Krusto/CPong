#include "Player.h"

/***********************************************************************************************************************
Static Constants
***********************************************************************************************************************/
/***********************************************************************************************************************
Static Functions
***********************************************************************************************************************/
static void Player_FixBoundry( Player* player, int32_t x, int32_t y, int32_t width, int32_t height );

/***********************************************************************************************************************
Function Implementations
***********************************************************************************************************************/
void Player_Init( Player* player, int32_t x, int32_t y, uint32_t id )
{
    Paddle_Init( &player->paddle, x, y, PLAYER_CONSTANTS.PLAYER_WIDTH, PLAYER_CONSTANTS.PLAYER_HEIGHT,
                 PLAYER_CONSTANTS.PLAYER_COLOR_R, PLAYER_CONSTANTS.PLAYER_COLOR_G, PLAYER_CONSTANTS.PLAYER_COLOR_B );
    player->position.x = x;
    player->position.y = y;
    player->id = id;
    player->score = 0;
}

void Player_Update( Player* player, Event* ev, Time* deltaTime )
{
    if ( ev->type == EVENT_KEY )
    {
        if ( ev->keyEvent.type == KEY_PRESSED )
        {
            if ( player->id == 1 )
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
            else if ( player->id == 0 )
            {

                switch ( ev->keyEvent.key )
                {
                    case KEY_W:
                        player->velocity = -1;
                        break;
                    case KEY_S:
                        player->velocity = 1;
                        break;
                    default:
                        break;
                }
            }
        }
        else if ( ev->keyEvent.type == KEY_RELEASED ) { player->velocity = 0; }
    }
    double value = player->velocity * PLAYER_CONSTANTS.PLAYER_SPEED * deltaTime->value * 0.01;
    player->position.y += value;
    Player_FixBoundry( player, 0, 0, 1280, 720 );
    player->paddle.y = player->position.y;
}

void Player_Render( Player* player ) { Paddle_Render( &player->paddle ); }

inline static void Player_FixBoundry( Player* player, int32_t x, int32_t y, int32_t width, int32_t height )
{
    if ( player->position.y < 0 ) { player->position.y = 0; }
    else if ( player->position.y > height - PLAYER_CONSTANTS.PLAYER_HEIGHT )
    {
        player->position.y = height - PLAYER_CONSTANTS.PLAYER_HEIGHT;
    }
    else if ( player->position.x < 0 ) { player->position.x = 0; }
    else if ( player->position.x > width - PLAYER_CONSTANTS.PLAYER_WIDTH )
    {
        player->position.x = width - PLAYER_CONSTANTS.PLAYER_WIDTH;
    }
}