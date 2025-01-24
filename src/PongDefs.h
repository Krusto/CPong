#ifndef PONG_DEFS
#define PONG_DEFS
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
 * Pong Type Definitions
 */


/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "Memory.h"
#include "Paddle.h"
#include "Player.h"
#include "STDTypes.h"
#include "Timestep.h"


#include <vector.h>


#ifndef NON_STD_MATH
#include <math.h>
#endif

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Type definitions
***********************************************************************************************************************/
typedef enum
{
    Pong_Result_None = 0,
    Pong_Result_Success,
    Pong_Result_Error
} PongResultType;

typedef enum
{
    Pong_State_None = 0,
    Pong_State_Init,
    Pong_State_Running,
    Pong_State_Exit,
    Pong_State_Error
} PongStateType;

typedef struct PongInternalDataType {
    PongStateType state;
    Time delta_time;
    double fps;

    Player player;

} PongInternalDataType;

typedef PongInternalDataType Pong;

#endif//PONG_DEFS