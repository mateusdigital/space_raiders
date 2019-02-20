#pragma once
//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Random.h                                                      //
//  Project   : SpaceRaiders                                                  //
//  Date      : Dec 18, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

// "class-like" namespace
namespace Random
{
    //------------------------------------------------------------------------//
    // Init / Shutdown                                                        //
    //------------------------------------------------------------------------//
    void Init(int randomSeed) noexcept;
    bool IsInitialized() noexcept;


    //------------------------------------------------------------------------//
    // Random Methods                                                         //
    //------------------------------------------------------------------------//
    float Float(float min, float max) noexcept;
    int   Int  (int   min, int   max) noexcept;
};
