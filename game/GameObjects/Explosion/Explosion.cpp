//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Explosion.cpp                                                 //
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
#include "GameObjects/Explosion/Explosion.h"
// SpaceRaiders
#include "Game/Engine.h"
#include "Maths/Random.h"
#include "Scenes/GameScene/GameScene.h"


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
static constexpr auto kTime_MaxExplosion = 0.5f;


//----------------------------------------------------------------------------//
// Helper Types                                                               //
//----------------------------------------------------------------------------//
struct DummySprite
    : Sprite_t
{
    DummySprite() :
        Sprite_t( L"*",  { FG_RED })
    {
        // Empty...
    }
};


//------------------------------------------------------------------------//
// CTOR / DTOR                                                            //
//------------------------------------------------------------------------//
Explosion::Explosion(
    Engine     *pEngineRef,
    GameScene  *pGameSceneRef,
    const Vec2 &position,
    int         size) noexcept :
    // Base class.
    GameObject(
        pEngineRef,
        pGameSceneRef,
        position,
        DummySprite(),
        ObjectType::Explosion
    ),
    // Members
    m_size(size)
{
    //Empty...
}

//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
void Explosion::Update() noexcept
{
    if(!IsActive())
        return;

    m_timer += m_pEngineRef->DeltaTime();
    if(m_timer >= kTime_MaxExplosion)
        SetActive(false);
}

void Explosion::Render() noexcept
{
    if(!IsActive())
        return;

    //--------------------------------------------------------------------------
    // Displacement of the explosion.
    //   This makes the explosion bigger during the time.
    auto d  = m_size * (0.5f + m_timer);
    auto d2 = d*2;

    const auto &pos = Position();
    for(int i = 0; i < m_size; ++i)
    {
        auto c = (Random::Int(0, 1)) ? L'*' : L'.';

        m_pEngineRef->Draw(
            int(pos.x) + Random::Int(-d2 , d2),
            int(pos.y) + Random::Int(-d, d),
            c,
            Random::Int(FG_BLACK+1, FG_WHITE)
        );
    }
}
