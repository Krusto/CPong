#ifndef Ball_HEADER
#define Ball_HEADER

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
 * Ball management
 */


/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "Events.h"
#include "Math.h"
#include "STDTypes.h"
#include "Timestep.h"

/***********************************************************************************************************************
Macro Definitions
***********************************************************************************************************************/


/***********************************************************************************************************************
Type Declarations
***********************************************************************************************************************/
typedef struct {
    uint32_t Ball_SPEED;
    uint32_t Ball_RADIUS;
    uint32_t Ball_COLOR_R;
    uint32_t Ball_COLOR_G;
    uint32_t Ball_COLOR_B;
} BallConstantsType;

typedef struct {
    Point2i position;
    double velocityX;
    double velocityY;
} Ball;

/***********************************************************************************************************************
Function Prototypes
***********************************************************************************************************************/

extern void Ball_Init( Ball* ball, int32_t x, int32_t y, double velocityX, double velocityY );
extern void Ball_Update( Ball* ball, Point2i player1Pos, Point2i player2Pos, Event* ev, Time* deltaTime );
extern void Ball_Render( Ball* ball );

#endif// Ball_HEADER