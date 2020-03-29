//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Engine.cpp                                                    //
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
#include "Engine.h"
// SpaceRaiders
#include "Input.h"
#include "Random.h"


// std::atomic<bool> olcConsoleGameEngine::m_bAtomActive(false);
// std::condition_variable olcConsoleGameEngine::m_cvGameFinished;
// std::mutex olcConsoleGameEngine::m_muxGame;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
Engine::Engine()
{
    m_sAppName = "SpaceRaiders";
}


//----------------------------------------------------------------------------//
// Scene Management                                                           //
//----------------------------------------------------------------------------//
void Engine::SetScene(const Scene::SPtr& pScene) noexcept
{
    // COREASSERT_ASSERT(pScene != nullptr, "pScene cannot be nullptr");
    if (m_pScene) m_pScene->OnExit();

    m_pScene = pScene;
    m_pScene->OnEnter();
}


//----------------------------------------------------------------------------//
// Engine Overrides                                                           //
//----------------------------------------------------------------------------//
bool Engine::OnUserCreate()
{
    m_bounds = Vec2(ScreenWidth(), ScreenHeight());
    return true;
}

bool Engine::OnUserUpdate(float delta)
{
    m_deltaTime = delta;

    // Update Input.
    m_pInput->Update(
        m_keys[VK_LEFT].bHeld,
        m_keys[VK_RIGHT].bHeld,
        m_keys[VK_SPACE].bHeld,
        m_keys[VK_ESCAPE].bHeld
    );

    // Update state.
    m_pScene->Update();

    // Render state.
    Fill(0, 0, ScreenWidth(), ScreenHeight(), PIXEL_SOLID, m_clearColor);
    m_pScene->Render();

    return true;
}
