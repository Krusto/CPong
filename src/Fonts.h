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
 * Fonts declarations
 */

#ifndef PONG_Fonts
#define PONG_Fonts

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "STDTypes.h"

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Type definitions
***********************************************************************************************************************/
typedef enum
{
    FONT_RESULT_NONE = 0,
    FONT_RESULT_SUCCESS,
    FONT_RESULT_NOT_FOUND,
    FONT_RESULT_ERROR
} FontResultType;

typedef struct {
    const char* name;
    uint32_t size;
    void* data;
} Font;

typedef enum
{
    FONT_NORMAL = 0,
    FONT_BOLD,
    FONT_ITALIC,
    FONT_BOLD_ITALIC
} FontType;

/***********************************************************************************************************************
Functions declarations
************************************************************************************************************************/

extern void FontsInit( void );
extern FontResultType FontsGetFont( const char* name, uint32_t size, Font* font );
extern FontResultType FontsGetFontByType( const char* name, uint32_t size, FontType type, Font* font );
extern FontResultType FreeFont( Font* font );
extern void FontsQuit( void );

#endif