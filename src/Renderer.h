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
 * Renderer declarations
 */

#ifndef PONG_RENDERER
#define PONG_RENDERER


/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "Texture.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>
#include <STDTypes.h>


/***********************************************************************************************************************
Macro definitions
***********************************************************************************************************************/
#define RENDERER_MAX_COMMANDS 1024

/***********************************************************************************************************************
Type definitions
***********************************************************************************************************************/
typedef enum
{
    Renderer_Result_None = 0,
    Renderer_Result_Success,
    Renderer_Result_Error
} RendererResultType;

typedef enum
{
    RendererCommandType_None = 0,
    RendererCommandType_BindShader,
    RendererCommandType_BindTexture,
    RendererCommandType_Clear,
    RendererCommandType_DrawQuad,
    RendererCommandType_DrawTexture,
    RendererCommandType_DrawCircle,
    RendererCommandType_DrawText
} RendererCommandType;

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t width;
    uint32_t height;
    uint32_t r;
    uint32_t g;
    uint32_t b;
    uint32_t a;
} RendererCommandDrawQuad;

typedef struct {
    uint32_t r;
    uint32_t g;
    uint32_t b;
    uint32_t a;
} RendererCommandClear;

typedef enum
{
    TextAlign_TopLeft = 0,
    TextAlign_TopCenter,
    TextAlign_TopRight,
    TextAlign_Left,
    TextAlign_Center,
    TextAlign_Right,
    TextAlign_BottomLeft,
    TextAlign_BottomCenter,
    TextAlign_BottomRight,
} RendererTextAlignAttribute;

typedef struct {
    char* text;
    void* font;
    int32_t x;
    int32_t y;
    uint32_t r;
    uint32_t g;
    uint32_t b;
    uint32_t a;
    RendererTextAlignAttribute align;
} RendererCommandDrawText;

typedef struct {
    uint32_t x;
    uint32_t y;
    Texture* texture;
} RendererCommandDrawTexture;

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t radius;
    uint32_t r;
    uint32_t g;
    uint32_t b;
    uint32_t a;
} RendererCommandDrawCircle;

typedef struct {

    void* data;
    void* next;
    RendererCommandType type;
} RendererCommandNode;

typedef void RendererCommand;

typedef struct {
    RendererCommandNode* head;
    RendererCommandNode* current;
} RendererCommandStack;

typedef struct {
    RendererCommandStack command_stack;
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Surface* surface;
    uint32_t width;
    uint32_t height;
} RendererDataType;

/***********************************************************************************************************************
Functions declarations
************************************************************************************************************************/
extern RendererResultType RendererInit( uint32_t width, uint32_t height );

extern void RendererDestroy( void );
extern void RendererPresent( void );
extern void RendererCmdDrawQuad( RendererCommandDrawQuad* quad );
extern void RendererCmdDrawTexture( RendererCommandDrawTexture* texture );
extern void RendererCmdDrawCircle( RendererCommandDrawCircle* circle );
extern void RendererCmdDrawText( RendererCommandDrawText* text );
extern void RendererCmdClear( RendererCommandClear* clear );
extern void RendererCmdFlush( void );
extern RendererDataType* RendererGet( void );
#endif