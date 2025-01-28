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

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "Fonts.h"
#include "Renderer.h"
#include <SDL3/SDL.h>

/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/

/***********************************************************************************************************************
Functions declarations
************************************************************************************************************************/

void FontsInit( void ) { TTF_Init(); }

FontResultType FontsGetFont( const char* name, uint32_t size, Font* font )
{
    TTF_Font* font_ptr = TTF_OpenFont( name, size );
    if ( font_ptr == NULL ) { return FONT_RESULT_NOT_FOUND; }

    font->name = name;
    font->size = size;
    font->data = font_ptr;
    return FONT_RESULT_SUCCESS;
}

FontResultType FontsGetFontByType( const char* name, uint32_t size, FontType type, Font* font )
{
    return FontResultType();
}

FontResultType FreeFont( Font* font ) { return FontResultType(); }

void FontsQuit( void ) {}
