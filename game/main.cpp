//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : main.cpp                                                      //
//  Project   : SpaceRaiders                                                  //
//  Date      : Dec 18, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// SpaceRaiders
#include "Game/Engine.h"
#include "Input/Input.h"
#include "Maths/Random.h"
#include "Scenes/SplashScene/SplashScene.h"

//----------------------------------------------------------------------------//
// Entry point                                                                //
//----------------------------------------------------------------------------//
int main()
{
    //--------------------------------------------------------------------------
    // Init random number generator.
    auto random_seed = -1;
    Random::Init(random_seed);

    //--------------------------------------------------------------------------
    // Init the input.
    KeyboardInput input;

    //--------------------------------------------------------------------------
    // Init the game.
    Engine game;
    game.ConstructConsole(80, 30, 16, 16);

    auto p_game_ref  = &game;
    auto p_input_ref = &input;
    auto p_scene     = std ::make_shared  <SplashScene>(p_game_ref);

    game.SetInput(p_input_ref);
    game.SetScene(p_scene);
    game.Start();
}
