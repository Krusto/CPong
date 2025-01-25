#ifndef Player_HEADER
#define Player_HEADER

/**
 * @file
 * @author Krusto Stoyanov ( k.stoianov2@gmail.com )
 * @brief 
 * @version 1.0
 * @date 
 * 
 * @section LICENSE
 * MIT License
 * 
 * Copyright (c) 2025 Krusto
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 * @section DESCRIPTION
 * 
 * Player management
 */


/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "Events.h"
#include "Math.h"
#include "Paddle.h"
#include "STDTypes.h"
#include "Timestep.h"

/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/


/***********************************************************************************************************************
Type Declarations
***********************************************************************************************************************/
typedef struct {
    uint32_t PLAYER_SPEED;
    uint32_t PLAYER_WIDTH;
    uint32_t PLAYER_HEIGHT;
    uint32_t PLAYER_COLOR_R;
    uint32_t PLAYER_COLOR_G;
    uint32_t PLAYER_COLOR_B;
} PlayerConstantsType;

typedef struct {
    Paddle paddle;
    Point2i position;
    double velocity;
    uint32_t id;
    uint32_t score;
} Player;

/***********************************************************************************************************************
Function Prototypes
***********************************************************************************************************************/

extern void Player_Init( Player* player, int32_t x, int32_t y, uint32_t id );
extern void Player_Update( Player* player, Event* ev, Time* deltaTime );
extern void Player_Render( Player* player );


/***********************************************************************************************************************
Global Const Variables
***********************************************************************************************************************/

static const PlayerConstantsType PLAYER_CONSTANTS = { 90, 20, 100, 255, 255, 255 };


#endif// Player_HEADER