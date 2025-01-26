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
 * Renderer Implementation
 */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "Renderer.h"
#include "Memory.h"

/***********************************************************************************************************************
Static variables
***********************************************************************************************************************/
RendererDataType* g_renderer;

/***********************************************************************************************************************
Static function Prototypes
***********************************************************************************************************************/
static void RendererPushCommand( RendererCommandType type, void* data, uint32_t size );
static void HandleNode( RendererCommandNode* node );

/***********************************************************************************************************************
Implementation
***********************************************************************************************************************/

RendererResultType RendererInit( uint32_t width, uint32_t height )
{
    g_renderer = Pong_MALLOC( sizeof( RendererDataType ) );
    g_renderer->width = width;
    g_renderer->height = height;
    g_renderer->command_stack.head = NULL;

    g_renderer->window = SDL_CreateWindow( "Pong", width, height, 0 );
    if ( g_renderer->window == NULL ) { return Renderer_Result_Error; }

    g_renderer->renderer = SDL_CreateRenderer( g_renderer->window, NULL );
    if ( g_renderer->renderer == NULL ) { return Renderer_Result_Error; }
    SDL_SetRenderVSync( g_renderer->renderer, 1 );

    g_renderer->surface = SDL_GetWindowSurface( g_renderer->window );
    if ( g_renderer->surface == NULL ) { return Renderer_Result_Error; }

    return Renderer_Result_Success;
}

void RendererDestroy( void )
{
    if ( g_renderer == NULL ) { return; }

    SDL_DestroyRenderer( g_renderer->renderer );
    SDL_DestroyWindow( g_renderer->window );
    SDL_Quit();
    Pong_FREE( g_renderer );
}

void RendererPresent( void ) { SDL_RenderPresent( g_renderer->renderer ); }

void RendererCmdDrawQuad( RendererCommandDrawQuad* quad )
{
    RendererPushCommand( RendererCommandType_DrawQuad, quad, sizeof( RendererCommandDrawQuad ) );
}

void RendererCmdDrawCircle( RendererCommandDrawCircle* circle )
{
    RendererPushCommand( RendererCommandType_DrawCircle, circle, sizeof( RendererCommandDrawCircle ) );
}

void RendererCmdClear( RendererCommandClear* clear )
{
    RendererPushCommand( RendererCommandType_Clear, clear, sizeof( RendererCommandClear ) );
}

void RendererCmdDrawText( RendererCommandDrawText* text )
{

    RendererPushCommand( RendererCommandType_DrawText, text, sizeof( RendererCommandDrawText ) );
}

inline static void RendererPushCommand( RendererCommandType type, void* data, uint32_t size )
{

    RendererCommandNode* node = Pong_MALLOC( sizeof( RendererCommandNode ) );
    node->type = type;
    node->next = NULL;
    node->data = Pong_MALLOC( size );
    Pong_MEMCPY( node->data, data, size );

    if ( g_renderer->command_stack.head == NULL )
    {
        g_renderer->command_stack.head = node;
        g_renderer->command_stack.current = node;
    }
    else { g_renderer->command_stack.current->next = node; }
    g_renderer->command_stack.current = node;
}

inline static void HandleNode( RendererCommandNode* node )
{
    switch ( node->type )
    {
        case RendererCommandType_Clear: {
            RendererCommandClear* clear = ( RendererCommandClear* ) node->data;
            SDL_SetRenderDrawColor( g_renderer->renderer, clear->r, clear->g, clear->b, clear->a );
            SDL_RenderClear( g_renderer->renderer );
            break;
        }
        case RendererCommandType_DrawQuad: {
            RendererCommandDrawQuad* quad = ( RendererCommandDrawQuad* ) node->data;
            SDL_FRect rect;
            rect.x = quad->x;
            rect.y = quad->y;
            rect.w = quad->width;
            rect.h = quad->height;
            SDL_SetRenderDrawColor( g_renderer->renderer, quad->r, quad->g, quad->b, quad->a );
            SDL_RenderFillRect( g_renderer->renderer, &rect );
            break;
        }
        case RendererCommandType_DrawCircle: {
            RendererCommandDrawCircle* circle = ( RendererCommandDrawCircle* ) node->data;
            SDL_FRect rect;
            rect.x = circle->x;
            rect.y = circle->y;
            rect.w = circle->radius;
            rect.h = circle->radius;
            SDL_SetRenderDrawColor( g_renderer->renderer, circle->r, circle->g, circle->b, circle->a );
            SDL_RenderFillRect( g_renderer->renderer, &rect );
            break;
        }
        case RendererCommandType_DrawText: {
            RendererCommandDrawText* text = ( RendererCommandDrawText* ) node->data;
            SDL_SetRenderDrawColor( g_renderer->renderer, text->r, text->g, text->b, text->a );
            SDL_RenderDebugText( g_renderer->renderer, text->x, text->y, text->text );
            break;
        }
        default:
            break;
    }
}

void RendererCmdFlush( void )
{

    for ( uint32_t iter = 0; g_renderer->command_stack.head != NULL && iter < RENDERER_MAX_COMMANDS; iter += 1 )
    {
        RendererCommandNode* node = g_renderer->command_stack.head;
        HandleNode( node );

        g_renderer->command_stack.head = g_renderer->command_stack.head->next;
        Pong_FREE( node->data );
        Pong_FREE( node );
    }
}

RendererDataType* RendererGet( void ) { return g_renderer; }
