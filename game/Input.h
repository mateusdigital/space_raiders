//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Input.h                                                       //
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
#include "Random.h"

//----------------------------------------------------------------------------//
// Input                                                                      //
//----------------------------------------------------------------------------//
 struct Input
{
    virtual void Update(bool left, bool right, bool fire, bool exit) noexcept = 0;

    virtual bool Left () noexcept = 0;
    virtual bool Right() noexcept = 0;
    virtual bool Fire () noexcept = 0;
    virtual bool Exit () noexcept = 0;
};


//----------------------------------------------------------------------------//
// Keyboard Input                                                             //
//----------------------------------------------------------------------------//
struct KeyboardInput
    : public Input
{
public:
    inline void Update(bool left, bool right, bool fire, bool exit) noexcept override
    {
        m_left  = left;
        m_right = right;
        m_fire  = fire;
        m_exit  = exit;
    }

public:
    inline bool Left () noexcept override { return m_left;  }
    inline bool Right() noexcept override { return m_right; }
    inline bool Fire () noexcept override { return m_fire;  }
    inline bool Exit () noexcept override { return m_exit;  }

private:
    bool m_left;
    bool m_right;
    bool m_fire;
    bool m_exit;
};


//----------------------------------------------------------------------------//
// Random Input                                                               //
//----------------------------------------------------------------------------//
struct RandomInput
    : public Input
{
public:
    inline void Update(bool, bool, bool, bool exit) noexcept override
    {
        m_left  = Random::Float(0, 1) < 0.3f;
        m_right = Random::Float(0, 1) < 0.3f;
        m_fire  = Random::Float(0, 1) < 0.5f;

        m_exit = exit;
    }

public:
    inline bool Left () noexcept override { return m_left;  }
    inline bool Right() noexcept override { return m_right; }
    inline bool Fire () noexcept override { return m_fire;  }
    inline bool Exit () noexcept override { return m_exit;  }


private:
    bool m_left;
    bool m_right;
    bool m_fire;
    bool m_exit;
};
