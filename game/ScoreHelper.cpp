//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : ScoreHelper.h                                                 //
//  Project   : SpaceRaiders                                                  //
//  Date      : Dec 18, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// Header
#include "ScoreHelper.h"
// std
#include <stdio.h>


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kPath_Storage = "./HiSCORE.txt";


void ScoreHelper::SaveScore(int score) noexcept
{
    //--------------------------------------------------------------------------
    // Try to open the file, if it doesn't exists just returns.
    auto p_file = fopen(kPath_Storage, "w");
    if (!p_file) // Error occurred - Ignore it.
        return;

    fprintf(p_file, "%d", score);
    fclose(p_file);
}

int ScoreHelper::LoadScore() noexcept
{
    //--------------------------------------------------------------------------
    // Try to open the file, if it doesn't exists just returns.
    auto p_file = fopen(kPath_Storage, "r");
    if (!p_file) // No high scores.
        return 0;

    //--------------------------------------------------------------------------
    // File exists, so we have a high score - Read it.
    int value;

    fscanf(p_file, "%d", &value);
    fclose(p_file);
    p_file = nullptr;

    return value;
}

