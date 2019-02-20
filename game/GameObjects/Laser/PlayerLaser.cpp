//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : PlayerLaser.cpp                                               //
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
#include "GameObjects/Laser/PlayerLaser.h"
// SpaceRaiders
#include "Game/Engine.h"
#include "Scenes/GameScene/GameScene.h"


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kVelocity = Vec2(0, -20);


//----------------------------------------------------------------------------//
// Helper Types                                                               //
//----------------------------------------------------------------------------//
struct PlayerLaserSprite
    : Sprite_t
{
    PlayerLaserSprite() :
        Sprite_t( L"|",  { FG_GREEN })
    {
        // Empty...
    }
};


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
PlayerLaser::PlayerLaser(
    Engine     *pEngineRef,
    GameScene  *pGameSceneRef,
    const Vec2 &position) noexcept :
    // Base class.
    GameObject(
        pEngineRef,
        pGameSceneRef,
        position,
        PlayerLaserSprite(),
        ObjectType::AlienLaser
    )
{
    // Empty...
}


//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
void PlayerLaser::Update() noexcept
{
    // Nothing to do...
    if(!IsActive())
        return;

    //--------------------------------------------------------------------------
    // Movement.
    auto new_position = Position() + (kVelocity * m_pEngineRef->DeltaTime());
    Position(new_position);

    //--------------------------------------------------------------------------
    // Bounds Checking.
    if(new_position.y < 0)
        SetActive(false);
}

void PlayerLaser::Render() noexcept
{
    // Nothing to do...
    if(!IsActive())
        return;

    const auto &pos    = Position();
    const auto &size   = Size    ();
    const auto &sprite = Sprite  ();

    for(int i = 0; i < size; ++i)
    {
        m_pEngineRef->Draw(
            int(pos.x) + i,
            int(pos.y),
            sprite.glyphs[i],
            sprite.colors[i]
        );
    }
}
