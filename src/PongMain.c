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

PongStateType gPongStateTransitionTable[] = {
        /*Pong_State_None                    -->*/ Pong_State_Init,
        /*Pong_State_Init                    -->*/ Pong_State_Paused,
        /*Pong_State_Paused                  -->*/ Pong_State_Paused,
        /*Pong_State_Running                 -->*/ Pong_State_Running,
        /*Pong_State_Exit                    -->*/ Pong_State_Exit,
        /*Pong_State_Error                   -->*/ Pong_State_Error,
};

Pong gPong = {};

/***********************************************************************************************************************
Static function Prototypes
***********************************************************************************************************************/

void AppInit( Pong* pong );
PongResultType AppUpdate( Pong* pong );
void AppUpdateState( Pong* pong );
RendererResultType PongStateInit( Pong* pong );
void PongStatePause( Pong* pong );
void PongStateUpdate( Pong* pong );

/***********************************************************************************************************************
Implementation
***********************************************************************************************************************/

PongResultType CreatePong( void )
{
    gPong.delta_time.unit = TIME_MS;
    gPong.passed_time.unit = TIME_MS;
    gPong.fading_speed = 0.002;
    AppInit( &gPong );

    Timer timer;

    while ( gPong.state != Pong_State_Exit )
    {
        Timer_Start( &timer );
        AppUpdate( &gPong );
        Timer_End( &timer );
        gPong.delta_time.value = timer.t_ms;
        gPong.fps = 1000.0 / gPong.delta_time.value;
        gPong.passed_time.value += gPong.fading_speed * gPong.delta_time.value;
    }

    return Pong_Result_Success;
}

void DestroyPong( void ) { RendererDestroy(); }

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
        case Pong_State_Paused:
            PongStatePause( pong );
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

void AppUpdateState( Pong* pong ) { pong->state = gPongStateTransitionTable[ pong->state ]; }

RendererResultType PongStateInit( Pong* pong )
{
    RendererResultType result = RendererInit( 1280, 720 );
    if ( result == Renderer_Result_Success )
    {
        FontResultType result2 = FontAtlasLoadFont( "joystixmonospace.ttf", 24, FONT_NORMAL, &pong->fonts );
        if ( result2 != FONT_RESULT_SUCCESS ) { return Renderer_Result_Error; }
        Player_Init( &pong->player1, 0, 360, 0 );
        Player_Init( &pong->player2, 1280 - 20, 360, 1 );
        Ball_Init( &pong->ball, 640, 360, -1, 0.2 );
    }
    return result;
}

void ShowDebugInfo( Pong* pong )
{
    RendererCommandDrawText text = { NULL, NULL, 0, 0, 255, 255, 255, 255, TextAlign_BottomLeft };
    text.font = FontAtlasGetFont( &pong->fonts, "joystixmonospace.ttf", FONT_NORMAL );
    int length = snprintf( NULL, 0, "X: %d Y: %d FPS: %lf DT: %lfms", pong->player1.position.x,
                           pong->player1.position.y, pong->fps, pong->delta_time.value );
    text.text = Pong_MALLOC( length + 1 );
    snprintf( text.text, length + 1, "X: %d Y: %d FPS: %lf DT: %lfms", pong->player1.position.x,
              pong->player1.position.y, pong->fps, pong->delta_time.value );
    RendererCmdDrawText( &text );

    RendererCmdFlush();

    Pong_FREE( text.text );
}

void RenderScore( Pong* pong )
{
    RendererCommandDrawText text = { NULL, NULL, 0, 0, 255, 255, 255, 255, TextAlign_TopCenter };
    text.font = FontAtlasGetFont( &pong->fonts, "joystixmonospace.ttf", FONT_NORMAL );
    int length = snprintf( NULL, 0, "%d - %d", pong->player1.score, pong->player2.score );
    text.text = Pong_MALLOC( length + 1 );
    snprintf( text.text, length + 1, "%d - %d", pong->player1.score, pong->player2.score );
    RendererCmdDrawText( &text );
    RendererCmdFlush();
    Pong_FREE( text.text );
}

void RenderStart( Pong* pong )
{
    if ( pong->passed_time.value > 1.0 )
    {
        pong->passed_time.value = 1.0;
        pong->fading_speed = -pong->fading_speed;
    }
    else if ( pong->passed_time.value < 0.0 )
    {
        pong->passed_time.value = 0;
        pong->fading_speed = -pong->fading_speed;
    }
    float alpha = sin( pong->passed_time.value + 0.1 );
    RendererCommandDrawText text = { NULL, NULL, 0, -30, 255, 255, 255, alpha * 255, TextAlign_Center };
    text.font = FontAtlasGetFont( &pong->fonts, "joystixmonospace.ttf", FONT_NORMAL );
    int length = snprintf( NULL, 0, "Press any key to start..." );
    text.text = Pong_MALLOC( length + 1 );
    snprintf( text.text, length + 1, "Press any key to start..." );
    RendererCmdDrawText( &text );
    RendererCmdFlush();
    Pong_FREE( text.text );
}

void PongStatePause( Pong* pong )
{
    Event event;
    event.type = EVENT_NONE;
    if ( PollEvents( &event ) && event.type == EVENT_QUIT ) { pong->state = Pong_State_Exit; }
    if ( event.type == EVENT_KEY )
    {
        if ( event.keyEvent.type == KEY_PRESSED && event.keyEvent.key != KEY_ESCAPE )
        {
            pong->state = Pong_State_Running;
        }
    }
    RendererCommandClear clear = { 0, 0, 0, 255 };
    RendererCmdClear( &clear );

    Player_Render( &pong->player1 );
    Player_Render( &pong->player2 );
    Ball_Render( &pong->ball );
    RenderStart( pong );
    RendererCmdFlush();

#ifdef _DEBUG
    ShowDebugInfo( pong );
#endif
    RendererPresent();
}

void PongStateUpdate( Pong* pong )
{
    Event event;
    event.type = EVENT_NONE;
    if ( PollEvents( &event ) && event.type == EVENT_QUIT ) { pong->state = Pong_State_Exit; }

    Player_Update( &pong->player1, &event, &pong->delta_time );
    Player_Update( &pong->player2, &event, &pong->delta_time );
    Ball_Update( &pong->ball, &pong->player1, &pong->player2, &event, &pong->delta_time );

    RendererCommandClear clear = { 0, 0, 0, 255 };
    RendererCmdClear( &clear );

    Player_Render( &pong->player1 );
    Player_Render( &pong->player2 );
    Ball_Render( &pong->ball );

    RenderScore( pong );
    RendererCmdFlush();

#ifdef _DEBUG
    ShowDebugInfo( pong );
#endif
    RendererPresent();
}