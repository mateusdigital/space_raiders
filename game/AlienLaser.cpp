//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : AlienLaser.cp                                                 //
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
#include "AlienLaser.h"
// SpaceRaiders
#include "Engine.h"
#include "GameScene.h"


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kVelocity = Vec2(0, 17);


//----------------------------------------------------------------------------//
// Helper Types                                                               //
//----------------------------------------------------------------------------//
struct AlienLaserSprite
    : Sprite_t
{
    AlienLaserSprite() :
        Sprite_t( "|",  { FG_RED })
    {
        // Empty...
    }
};


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
AlienLaser::AlienLaser(
    Engine     *pEngineRef,
    GameScene  *pGameSceneRef,
    const Vec2  &position) noexcept :
    // Base class
    GameObject(
        pEngineRef,
        pGameSceneRef,
        position,
        AlienLaserSprite(),
        ObjectType::AlienLaser)
{
    // Empty...
}

//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
void AlienLaser::Update() noexcept
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
    if(new_position.y >= m_pEngineRef->Bounds().y)
        SetActive(false);
}

void AlienLaser::Render() noexcept
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
