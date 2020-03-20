//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : MenuScene.h                                                   //
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
#include <string>
#include <vector>
// SpaceRaiders
#include "Scene.h"
#include "Vec2.h"
#include "Input.h"

class MenuScene :
    public Scene
{
    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    MenuScene(Engine* pEngineRef);


    //------------------------------------------------------------------------//
    // Lifecycle                                                              //
    //------------------------------------------------------------------------//
public:
    void OnEnter() noexcept override;
    void OnExit() noexcept override;


    //------------------------------------------------------------------------//
    // Update / Render                                                        //
    //------------------------------------------------------------------------//
public:
    void Update() noexcept override;
    void Render() noexcept override;


    //------------------------------------------------------------------------//
    // Helper Methods                                                         //
    //------------------------------------------------------------------------//
private:
    void GoToGame(bool demo);


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    int m_targetPos;

    std::vector<std::wstring> m_logo;
    std::vector<float       > m_speeds;
    std::vector<float       > m_positions;

    std::wstring m_hiScoreMsg;

    float m_timeToDemo;

    std::shared_ptr<KeyboardInput> m_pKeyboardInput;
};
