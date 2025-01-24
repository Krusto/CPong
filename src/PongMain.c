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
 * Pong Implementation
 */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "Events.h"
#include "Pong.h"
#include "PongDefs.h"
#include "Renderer.h"
#include "vector.h"

#include <stdio.h>
/***********************************************************************************************************************
Static variables
***********************************************************************************************************************/

PongStateType sPongStateTransitionTable[] = {
        /*Pong_State_None                    -->*/ Pong_State_Init,
        /*Pong_State_Init                    -->*/ Pong_State_Running,
        /*Pong_State_Running                 -->*/ Pong_State_Running,
        /*Pong_State_Exit                    -->*/ Pong_State_Exit,
        /*Pong_State_Error                   -->*/ Pong_State_Error,
};

Pong* gPong = NULL;

/***********************************************************************************************************************
Static function Prototypes
***********************************************************************************************************************/

void AppInit( Pong* pong );
PongResultType AppUpdate( Pong* pong );
void AppUpdateState( Pong* pong );
RendererResultType PongStateInit( Pong* pong );
void PongStateUpdate( Pong* pong );

/***********************************************************************************************************************
Implementation
***********************************************************************************************************************/

PongResultType CreatePong( void )
{
    gPong = Pong_MALLOC( sizeof( Pong ) );
    gPong->delta_time.unit = TIME_MS;
    AppInit( gPong );

    Timer timer;

    while ( gPong->state != Pong_State_Exit )
    {
        Timer_Start( &timer );
        AppUpdate( gPong );
        Timer_End( &timer );
        gPong->delta_time.value = timer.t_ms;
        gPong->fps = 1000.0 / gPong->delta_time.value;
    }

    return Pong_Result_Success;
}

void DestroyPong( void )
{
    if ( gPong )
    {
        RendererDestroy();
        Pong_FREE( gPong );
    }
}

PongStateType PongGetState( Pong* pong ) { return pong->state; }

void AppInit( Pong* pong )
{
    pong->state = Pong_State_None;

    AppUpdateState( pong );
}

PongResultType AppUpdate( Pong* pong )
{
    PongResultType result = Pong_Result_Success;
    switch ( pong->state )
    {
        case Pong_State_Init:
            if ( PongStateInit( pong ) != Renderer_Result_Success ) { return Pong_Result_Error; }
            else { AppUpdateState( pong ); }
            break;
        case Pong_State_Running:
            PongStateUpdate( pong );
            break;
        default:
            AppUpdateState( pong );
            break;
    }
    return result;
}

void AppUpdateState( Pong* pong ) { pong->state = sPongStateTransitionTable[ pong->state ]; }

RendererResultType PongStateInit( Pong* pong )
{
    RendererResultType result = RendererInit( 1280, 720 );
    if ( result == Renderer_Result_Success ) { Player_Init( &pong->player, 0, 360 ); }
    return result;
}

void ShowDebugInfo( Pong* pong )
{
    RendererCommandDrawText text = { NULL, 0, 0, 255, 255, 255, 255 };

    int length = snprintf( NULL, 0, "X: %d\nY: %d\nFPS: %lf\nDT: %lfms", pong->player.x, pong->player.y, pong->fps,
                           pong->delta_time.value );
    text.text = Pong_MALLOC( length + 1 );
    snprintf( text.text, length + 1, "X: %d\nY: %d\nFPS: %lf\nDT: %lfms", pong->player.x, pong->player.y, pong->fps,
              pong->delta_time.value );
    RendererCmdDrawText( &text );

    RendererCmdFlush();

    Pong_FREE( text.text );
}

void PongStateUpdate( Pong* pong )
{
    Event event;
    event.type = EVENT_NONE;
    if ( PollEvents( &event ) && event.type == EVENT_QUIT ) { pong->state = Pong_State_Exit; }

    Player_Update( &pong->player, &event, &pong->delta_time );

    RendererCommandClear clear = { 0, 0, 0, 255 };
    RendererCmdClear( &clear );

    Player_Render( &pong->player );

    RendererCmdFlush();

    ShowDebugInfo( pong );

    RendererPresent();
}