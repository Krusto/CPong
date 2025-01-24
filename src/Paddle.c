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
 * Paddle implementation
 */


/***********************************************************************************************************************
Includes
***********************************************************************************************************************/

#include "Paddle.h"
#include "Renderer.h"

/***********************************************************************************************************************
Type Declarations
***********************************************************************************************************************/

/***********************************************************************************************************************
Function Prototypes
***********************************************************************************************************************/

/***********************************************************************************************************************
Function Definitions
***********************************************************************************************************************/
void Paddle_Init( Paddle* paddle, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint32_t r, uint32_t g, uint32_t b )
{
    paddle->x = x;
    paddle->y = y;
    paddle->w = w;
    paddle->h = h;
    paddle->r = r;
    paddle->g = g;
    paddle->b = b;
}

void Paddle_Update( Paddle* paddle, int32_t dx, int32_t dy )
{
    paddle->x += dx;
    paddle->y += dy;
}

void Paddle_Render( Paddle* paddle )
{
    RendererCommandDrawQuad quad = { paddle->x, paddle->y, paddle->w, paddle->h, paddle->r, paddle->g, paddle->b, 255 };
    RendererCmdDrawQuad( &quad );
}
