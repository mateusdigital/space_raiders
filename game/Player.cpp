//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Player.cpp                                                    //
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
#include "Player.h"
// SpaceRaiders
#include "Engine.h"
#include "GameScene.h"


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kVelocity               = Vec2(100, 0);
constexpr auto kDuration_ShootCooldown = 0.3f;


//----------------------------------------------------------------------------//
// Helper Types                                                               //
//----------------------------------------------------------------------------//
struct PlayerSprite
    : Sprite_t
{
    PlayerSprite() :
        Sprite_t(
            L"_\\|P|/_",
            { FG_BLUE, FG_BLUE, FG_YELLOW, FG_BLUE, FG_YELLOW, FG_BLUE, FG_BLUE }
        )
    {
        // Empty...
    }
};


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
PlayerShip::PlayerShip(
    Engine     *pEngineRef,
    GameScene  *pGameSceneRef,
    const Vec2 &position) noexcept :
    // Base class.
    GameObject(
        pEngineRef,
        pGameSceneRef,
        position,
        PlayerSprite(),
        ObjectType::Player
    )
{
    // Empty...
}


//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
void PlayerShip::Update() noexcept
{
    // Nothing to do...
    if(!IsActive())
        return;

    //--------------------------------------------------------------------------
    // Movement.
    auto displacement = Vec2::Zero();;

    if     (m_pEngineRef->GetInput()->Left ()) displacement = Vec2::Left ();
    else if(m_pEngineRef->GetInput()->Right()) displacement = Vec2::Right();

    //--------------------------------------------------------------------------
    // Bounds checking.
    auto new_position = Position() + (displacement * kVelocity * m_pEngineRef->DeltaTime());
    auto world_bounds = m_pEngineRef->Bounds();

    if(new_position.x < 0)
        new_position.x = 0;
    else if(new_position.x >= world_bounds.x - Size())
        new_position.x = world_bounds.x - Size() -1 ;

    Position(new_position);

    //--------------------------------------------------------------------------
    // Shoot.
    m_shootCooldown -= m_pEngineRef->DeltaTime();
    if(m_pEngineRef->GetInput()->Fire() && m_shootCooldown <= 0)
    {
        m_shootCooldown = kDuration_ShootCooldown;
        m_pGameSceneRef->SpawnLaser(Middle() + Vec2::Up(), ObjectType::PlayerLaser);
    }
}

void PlayerShip::Render() noexcept
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
