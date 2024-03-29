//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Macros.h                                                      //
//  Project   : SpaceRaiders                                                  //
//  Date      : Dec 18, 2017                                                  //
//  License   : GPLv3                                                         //
//  Author    : n2omatt <n2omatt@amazingcow.com>                              //
//  Copyright : AmazingCow - 2017                                             //
//                                                                            //
//  Description :                                                             //
//                                                                            //
//---------------------------------------------------------------------------~//

#pragma once

// std
#include <memory>

//----------------------------------------------------------------------------//
// std::shared_ptr                                                            //
//----------------------------------------------------------------------------//
#define DEFINE_SHARED_PTR_OF(_type_) \
    typedef std::shared_ptr<_type_> SPtr;

//----------------------------------------------------------------------------//
// std::unique_ptr                                                            //
//----------------------------------------------------------------------------//
#define DEFINE_UNIQUE_PTR_OF(_type_) \
    typedef std::unique_ptr<_type_> UPtr;

//----------------------------------------------------------------------------//
// Both                                                                       //
//----------------------------------------------------------------------------//
#define DEFINE_SMART_PTRS_OF(_type_) \
    DEFINE_UNIQUE_PTR_OF(_type_)     \
    DEFINE_SHARED_PTR_OF(_type_)

