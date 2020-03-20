//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Alien.cpp                                                     //
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
#include "Alien.h"
// SpaceRaiders
#include "Engine.h"
#include "Sprite.h"
#include "Random.h"
#include "GameScene.h"


//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kVelocity_Base   = Vec2(5, 0);
constexpr auto kVelocity_Normal = kVelocity_Base;
constexpr auto kVelocity_Better = kVelocity_Base * 2;

constexpr auto kThreshold_Better_Min =  5.0f;
constexpr auto kThreshold_Better_Max = 50.0f;

constexpr auto kIncrement_Better_Min =  1.0f;
constexpr auto kIncrement_Better_Max =  5.0f;

constexpr auto kChange_Shoot_Normal = 0.3f;
constexpr auto kChange_Shoot_Better = 0.5f;

constexpr auto kCooldown_Better = 2.0f;
constexpr auto kCooldown_Normal = kCooldown_Better * 1.5f;


//----------------------------------------------------------------------------//
// Helper Types                                                               //
//----------------------------------------------------------------------------//
struct AlienSprite
    : Sprite_t
{
    AlienSprite() :
        Sprite_t(
            L"<=|A|=>",
            {FG_YELLOW, FG_YELLOW, FG_RED, FG_YELLOW, FG_RED, FG_YELLOW, FG_YELLOW}
        )
    {
        // Empty...
    }
};

struct BetterAlienSprite
    : Sprite_t
{
    BetterAlienSprite() :
        Sprite_t(
            L"<|B|>",
            {FG_RED, FG_YELLOW, FG_RED, FG_YELLOW, FG_RED}
        )
    {
        // Empty...
    }
};


//----------------------------------------------------------------------------//
// CTOR                                                                       //
//----------------------------------------------------------------------------//
Alien::Alien(
    Engine     *pEngineRef,
    GameScene  *pGameSceneRef,
    const Vec2 &position) noexcept :
    // Base class.
    GameObject(
        pEngineRef,
        pGameSceneRef,
        position,
        AlienSprite(),
        ObjectType::AlienShip)
{
    Velocity(kVelocity_Normal);

    m_neededEnergy = Random::Float(
        kThreshold_Better_Min,
        kThreshold_Better_Max
    );

    m_shootCooldown = Random::Float(0.5f, kCooldown_Normal);
}


//----------------------------------------------------------------------------//
// Public Methods                                                             //
//----------------------------------------------------------------------------//
void Alien::Update() noexcept
{
    // Nothing to do...
    if(!IsActive())
        return;

    auto pos = Position() + (m_direction * Velocity() * m_pEngineRef->DeltaTime());
    const auto& world_bounds = m_pEngineRef->Bounds();

    //--------------------------------------------------------------------------
    // Horizontal Border check.
    auto reach_bounds = false;
    if(pos.x < 0)
    {
        pos.x        = 0;
        reach_bounds = true;
    }
    else if(pos.x >= world_bounds.x - Size())
    {
        pos.x        = world_bounds.x - Size() - 1;
        reach_bounds = true;
    }

    if(reach_bounds)
    {
        m_direction *= -1;
        pos.y       += 1;
    }

    Position(pos);

    //--------------------------------------------------------------------------
    // Transform into better Alien.
    if(m_state != State::Better)
    {
        m_energy += Random::Float(
            kIncrement_Better_Min,
            kIncrement_Better_Max
        ) * m_pEngineRef->DeltaTime();

       if(m_energy >= m_neededEnergy)
            Transform();
    }

    //--------------------------------------------------------------------------
    // Shoot.
    m_shootCooldown -= m_pEngineRef->DeltaTime();
    if(m_shootCooldown > 0)
        return;

    // Assume that we're better alien already.
    auto shoot_change  = kChange_Shoot_Better;
    auto next_cooldown = kCooldown_Better;
    if(m_state == State::Normal)
    {
        shoot_change  = kChange_Shoot_Better;
        next_cooldown = kCooldown_Normal;
    }
    next_cooldown = Random::Float(next_cooldown, next_cooldown * 2);

    // Shoot.
    for(int i = 0; i < 3; ++i)
    {
        if(Random::Float(0, 1) > shoot_change)
            return;
    }

    m_pGameSceneRef->SpawnLaser(Middle() + Vec2::Down(), ObjectType::AlienLaser);
    m_shootCooldown = next_cooldown;
}

void Alien::Render() noexcept
{
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

bool Alien::DecreaseHealth() noexcept
{
    m_health -= 1.f;
    return m_health <= 0;
}


//----------------------------------------------------------------------------//
// Private Methods                                                            //
//----------------------------------------------------------------------------//
void Alien::Transform() noexcept
{
    // COREASSERT_ASSERT(m_state == State::Normal, "Alien is already better.");

    m_state   = State::Better;
    m_health *= 2; //Better Aliens have twice as much health.

    Sprite  (BetterAlienSprite());
    Velocity(   kVelocity_Better);
}
