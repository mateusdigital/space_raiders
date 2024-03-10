//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Engine.h                                                      //
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

// olcConsoleGameEngine
#include "olc.h"
// SpaceRaiders
#include "Input.h"
#include "Vec2.h"
#include "Scene.h"
#include "Macros.h"


class Engine :
    public olcConsoleGameEngine
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    Engine();

    //------------------------------------------------------------------------//
    // Scene Management                                                       //
    //------------------------------------------------------------------------//
public:
    void SetScene(const Scene::SPtr& pScene) noexcept;


    //------------------------------------------------------------------------//
    // Clear Color                                                            //
    //------------------------------------------------------------------------//
public:
    inline int  ClearColor() const noexcept { return m_clearColor; }
    inline void ClearColor(int c)  noexcept { m_clearColor = c; }


    //------------------------------------------------------------------------//
    // Delta Time                                                             //
    //------------------------------------------------------------------------//
public:
    inline float DeltaTime() const noexcept {
        if (m_deltaTime > 1.0f / 60.0f)
            return 1.0f / 60.0f;
        return m_deltaTime;
    }


    //------------------------------------------------------------------------//
    // Bounds                                                                 //
    //------------------------------------------------------------------------//
public:
    inline const Vec2& Bounds() const noexcept { return m_bounds; }


    //------------------------------------------------------------------------//
    // Input                                                                  //
    //------------------------------------------------------------------------//
public:
    inline Input* GetInput() const noexcept
    {
        return m_pInput;
    }

    inline void SetInput(Input* pInput) noexcept
    {
        m_pInput = pInput;
    }


    //------------------------------------------------------------------------//
    // Engine Overrides                                                       //
    //------------------------------------------------------------------------//
protected:
    bool OnUserCreate()            override;
    bool OnUserUpdate(float delta) override;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    Vec2  m_bounds;

    float m_deltaTime = 0.0f;
    int   m_clearColor = FG_BLACK;

    Scene::SPtr m_pScene = nullptr;
    Input* m_pInput = nullptr;
};
