//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Background.cpp                                                //
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
#include "GameObjects/Background/Background.h"
// SpaceRaiders
#include "Game/Engine.h"

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kCount_Stars_Max = 20;

constexpr auto kTime_Stars_Min =  5;
constexpr auto kTime_Stars_Max = 25;


//----------------------------------------------------------------------------//
// CTOR                                                                       //
//----------------------------------------------------------------------------//
Background::Background(Engine *pEngineRef) noexcept :
    m_pEngineRef(pEngineRef)
{
    m_stars.resize(kCount_Stars_Max);
    for(int i =0 ; i < kCount_Stars_Max; ++i)
        ConfigureStar(m_stars[i]);
}


//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
void Background::Render() noexcept
{
    for(auto &star : m_stars)
    {
        star.time -= m_pEngineRef->DeltaTime();
        if(star.time <= 0)
        {
            ConfigureStar(star);
            continue;
        }

        if(!star.visible)
            continue;

        m_pEngineRef->Draw(star.pos.x, star.pos.y, L'.', star.color);
    }
}

//----------------------------------------------------------------------------//
// Private Methods                                                            //
//----------------------------------------------------------------------------//
void Background::ConfigureStar(Background::Star &star) noexcept
{
    auto bounds = m_pEngineRef->Bounds();

    star.pos     = Vec2(Random::Int(0, bounds.x), Random::Int(0, bounds.y));
    star.time    = Random::Int(kTime_Stars_Min, kTime_Stars_Max);
    star.color   = Random::Int(FG_BLACK + 1, FG_WHITE);
    star.visible = Random::Int(0, 1) % 2 == 0;
}
