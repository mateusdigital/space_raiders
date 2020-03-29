//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : SplashScene.cpp                                               //
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
#include "SplashScene.h"
// SpaceRaiders
#include "Engine.h"
#include "Random.h"
#include "MenuScene.h"

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kCOW_X = 19;
constexpr auto kCOW_Y = 11;
constexpr auto kDuration_Scene = 1.5;


//----------------------------------------------------------------------------//
// Variables                                                                  //
//----------------------------------------------------------------------------//
namespace {
     _char_t kCOW[kCOW_Y][kCOW_X] = {
         {"     .      .     "},
         {"     ........     "},
         {"   ..        ..   "},
         {"  ...  .  .  ...  "},
         {"  . .        . .  "},
         {"   ............   "},
         {" .              . "},
         {".     .    .     ."},
         {".     .    .     ."},
         {" .              . "},
         {"   ............   "}
     };
}


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
SplashScene::SplashScene(Engine *pEngineRef) :
    // Base class.
    Scene(pEngineRef),
    // Members.
    m_time(kDuration_Scene)
{
    // Setup the clear color.
    m_pEngineRef->ClearColor(FG_BLACK);
}

//----------------------------------------------------------------------------//
// Lifecycle                                                                  //
//----------------------------------------------------------------------------//
void SplashScene::OnEnter() noexcept
{
    // Empty...
}

void SplashScene::OnExit() noexcept
{
    // Empty...
}



//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void SplashScene::Update() noexcept
{
    //--------------------------------------------------------------------------
    // We're not done yet...
    m_time -= m_pEngineRef->DeltaTime();
    if(m_time > 0)
        return;

    //--------------------------------------------------------------------------
    // Go to Menu.
    m_pEngineRef->SetScene(std::make_shared<MenuScene>(m_pEngineRef));
}

void SplashScene::Render() noexcept
{
    auto half_bounds = m_pEngineRef->Bounds() * 0.5f;
    auto half_cow_x  = kCOW_X * 0.5f;
    auto half_cow_y  = kCOW_Y * 0.5f;

    //--------------------------------------------------------------------------
    // Draw the COW.
    for(int i = 0; i < kCOW_Y; ++i)
    {
        for(int j = 0; j < kCOW_X; ++j)
        {
            if(kCOW[i][j] != L'.')
                continue;

            m_pEngineRef->Draw(
                j + half_bounds.x - half_cow_x,
                i + half_bounds.y - half_cow_y,
                PIXEL_HALF,
                Random::Int(FG_BLACK+1, FG_WHITE)
            );
        }
    }

    //--------------------------------------------------------------------------
    // Draw the mesages.
    m_pEngineRef->DrawString(30, 22, "** Amazing Cow! **", FG_WHITE);
    m_pEngineRef->DrawString(30, 23, " [A n2omatt Game]",  FG_WHITE);
}
