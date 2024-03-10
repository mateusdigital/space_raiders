//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : MenuScene.cpp                                                 //
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
#include "MenuScene.h"
// SpaceRaiders
#include "Engine.h"
#include "Input.h"
#include "Random.h"
#include "GameScene.h"
#include "ScoreHelper.h"


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kOffset_Logo_Y       = 5;
constexpr auto kDuration_TimeToDemo = 10.0f;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
MenuScene::MenuScene(Engine *pEngineRef) :
    // Base class.
    Scene(pEngineRef)
{
    // Setup the clear color.
    m_pEngineRef->ClearColor(FG_BLACK);

    //--------------------------------------------------------------------------
    // Init the logo.
    m_logo.push_back(LR"(   _____                         ____        _     __              )");
    m_logo.push_back(LR"(  / ___/____  ____ _________    / __ \____ _(_)___/ /__  __________)");
    m_logo.push_back(LR"(  \__ \/ __ \/ __ `/ ___/ _ \  / /_/ / __ `/ / __  / _ \/ ___/ ___/)");
    m_logo.push_back(LR"( ___/ / /_/ / /_/ / /__/  __/ / _, _/ /_/ / / /_/ /  __/ /  (__  ) )");
    m_logo.push_back(LR"(/____/ .___/\__,_/\___/\___/ /_/ |_|\__,_/_/\__,_/\___/_/  /____/  )");
    m_logo.push_back(LR"(     /_/                                                           )");

    auto logo_h = int(m_logo   .size());
    auto logo_w = int(m_logo[0].size());

    //--------------------------------------------------------------------------
    // Init the animation speeds.
    for(int i = 0; i < logo_h; ++i)
    {
        m_speeds.push_back(i % 2 == 0 ? 40 : -40);
    }

    //--------------------------------------------------------------------------
    // Init the positions.
    auto bounds = m_pEngineRef->Bounds();
    m_targetPos = (bounds.x * 0.5f) - (logo_w * 0.5f);

    for(int i = 0; i < logo_h; ++i)
    {
        auto left_to_right = (m_speeds[i] > 0);
        auto position = (left_to_right)
            ? -logo_w +10    //Put everything < 0
            : bounds.x -10;  //Put everything > bounds.x


        m_positions.push_back(position);
    }

    //--------------------------------------------------------------------------
    // Init HiScore
    m_hiScoreMsg = L"[HI-SCORE: ";
    m_hiScoreMsg += std::to_wstring(ScoreHelper::LoadScore());
    m_hiScoreMsg += L"]";


    //--------------------------------------------------------------------------
    // Init demo mode timer.
    m_timeToDemo = kDuration_TimeToDemo;

    //--------------------------------------------------------------------------
    // Setup the input.
    m_pKeyboardInput = std::make_shared<KeyboardInput>();
    m_pEngineRef->SetInput(m_pKeyboardInput.get());

}


//----------------------------------------------------------------------------//
// Lifecycle                                                                  //
//----------------------------------------------------------------------------//
void MenuScene::OnEnter() noexcept
{
    // Empty...
}

void MenuScene::OnExit() noexcept
{
    // Empty...
}


//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void MenuScene::Update() noexcept
{
    auto delta_time = m_pEngineRef->DeltaTime();

    //--------------------------------------------------------------------------
    // Update the Logo positions.
    for(int i = 0; i < m_logo.size(); ++i)
    {
        auto pos = m_positions[i];
        if(int(pos) == int(m_targetPos))
            continue;

        m_positions[i] = pos + (m_speeds[i] * delta_time);
    }

    //--------------------------------------------------------------------------
    // Update demo timer.
    m_timeToDemo -= m_pEngineRef->DeltaTime();

    //--------------------------------------------------------------------------
    // Go to Game scene.
    if(m_pEngineRef->GetInput()->Fire() || m_timeToDemo <= 0)
        GoToGame(m_timeToDemo <= 0);
}

void MenuScene::Render() noexcept
{
    auto bounds_h = m_pEngineRef->Bounds().y;
    auto bounds_w = m_pEngineRef->Bounds().x;

    //--------------------------------------------------------------------------
    // Draw the logo.
    auto logo_color = Random::Int(FG_BLACK+1, FG_WHITE);
    auto logo_w     = int(m_logo[0].size());
    auto logo_h     = int(m_logo   .size());

    for(int i = 0; i < logo_h; ++i)
    {
        for(int j = 0; j < logo_w; ++j)
        {
            auto pos = m_positions[i] + j;
            if(pos < 0 || pos >= bounds_w)
                continue;

            m_pEngineRef->Draw(
                pos,
                i + kOffset_Logo_Y,
                m_logo[i][j],
                logo_color
            );
        }
    }

    //--------------------------------------------------------------------------
    // Draw Score.
    auto score_offset = kOffset_Logo_Y + logo_h + 4;

    m_pEngineRef->DrawString(
        bounds_w * 0.5f - m_hiScoreMsg.size() * 0.5f,
        score_offset,
        m_hiScoreMsg,
        FG_CYAN
   );


    //--------------------------------------------------------------------------
    // Draw Instructions.
    auto left_msg   = std::wstring(L" [<-]   To move LEFT."   );
    auto right_msg  = std::wstring(L" [->]   To move RIGHT."  );
    auto fire_msg   = std::wstring(L"[SPACE] To SHOT a laser.");
    auto msg_offset = kOffset_Logo_Y + logo_h + 6;

    // Left.
    m_pEngineRef->DrawString(
        bounds_w * 0.5f - left_msg.size( ) * 0.5f,
        msg_offset,
        left_msg,
        FG_YELLOW
    );

    // Right.
    m_pEngineRef->DrawString(
        bounds_w * 0.5f - right_msg.size( ) * 0.5f,
        msg_offset + 1,
        right_msg,
        FG_YELLOW
    );

    // Fire.
    m_pEngineRef->DrawString(
        bounds_w * 0.5f - fire_msg.size( ) * 0.5f,
        msg_offset + 2,
        fire_msg,
        FG_YELLOW
    );

    //--------------------------------------------------------------------------
    // Draw Copyright
    auto copyright = std::wstring(L"Amazing Cow Labs - 2017, 2020, 2024");
    m_pEngineRef->DrawString(
        bounds_w * 0.5f - copyright.size() * 0.5f,
        bounds_h - 2,
        copyright,
        FG_RED
    );
}


void MenuScene::GoToGame(bool demo)
{
    m_pEngineRef->SetScene(
        std::make_shared<GameScene>(
            m_pEngineRef,
            0,    // Level,
            demo
        )
    );
}
