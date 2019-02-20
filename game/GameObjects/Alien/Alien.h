//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Alien.h                                                       //
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
#include "GameObjects/Base/GameObject.h"


class Alien
    : public GameObject
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    DEFINE_SMART_PTRS_OF(Alien);

    enum class State { Normal, Better };


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    explicit Alien(
        Engine     *pEngineRef,
        GameScene  *pGameSceneRef,
        const Vec2 &position) noexcept;


    //------------------------------------------------------------------------//
    // State                                                                  //
    //------------------------------------------------------------------------//
public:
    inline bool IsBetter() const noexcept { return m_state == State::Better; }


    //------------------------------------------------------------------------//
    // Public Methods                                                         //
    //------------------------------------------------------------------------//
public:
    void Update() noexcept override;
    void Render() noexcept override;

    bool DecreaseHealth() noexcept override;


    //------------------------------------------------------------------------//
    // Private Methods                                                        //
    //------------------------------------------------------------------------//
private:
    void Transform() noexcept;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    State m_state = State::Normal;

    float m_health        = 1.0f;
    float m_energy        = 0.0f;
    float m_neededEnergy  = 0.0f;
    int   m_direction     =    1;
    float m_shootCooldown =    0;
};
