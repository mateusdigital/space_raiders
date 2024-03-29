//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Scene.h                                                       //
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
// SpaceRaiders
#include "Macros.h"

//------------------------------------------------------------------------------
// Forward Declarations.
class Engine;

class Scene
{
    //------------------------------------------------------------------------//
    // Enuns / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    DEFINE_SMART_PTRS_OF(Scene);


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    Scene(Engine *pEngineRef) :
        m_pEngineRef(pEngineRef)
    {
        // Empty...
    }

    virtual ~Scene() = default;


    //------------------------------------------------------------------------//
    // Lifecycle                                                              //
    //------------------------------------------------------------------------//
public:
    virtual void OnEnter() noexcept = 0;
    virtual void OnExit () noexcept = 0;


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    virtual void Update() noexcept = 0;
    virtual void Render() noexcept = 0;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
protected:
   Engine* m_pEngineRef = nullptr;
};
