//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : GameObject.h                                                  //
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
#include "Sprite.h"
#include "Vec2.h"
#include "Macros.h"

//------------------------------------------------------------------------------
// Forward Declarations.
class GameScene;
class Engine;

class GameObject
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typedefs                                           //
    //------------------------------------------------------------------------//
public:
    DEFINE_SMART_PTRS_OF(GameObject);

    enum class ObjectType {
        AlienShip,
        AlienLaser,
        Explosion,
        Player,
        PlayerLaser,
    };


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    inline GameObject(
        Engine         *pEngineRef,
        GameScene      *pGameSceneRef,
        const Vec2     &pos,
        const Sprite_t &sprite,
        ObjectType     type) noexcept :
        // Members.
        m_pEngineRef   (   pEngineRef),
        m_pGameSceneRef(pGameSceneRef),
        m_position(   pos),
        m_sprite  (sprite),
        m_type    (  type),
        m_active  (  true)
    {
        // Empty...
    }

    virtual ~GameObject() = default;


    //------------------------------------------------------------------------//
    // Position                                                               //
    //------------------------------------------------------------------------//
public:
    inline const Vec2& Position() const noexcept { return m_position; }
    inline void Position(const Vec2 &v) noexcept { m_position = v;    }


    //------------------------------------------------------------------------//
    // Size                                                                   //
    //------------------------------------------------------------------------//
public:
    inline Vec2 Middle() const noexcept
    {
        const auto &pos = Position();
        return Vec2(pos.x + Size() * 0.5f, pos.y);
    }

    inline int Size() const noexcept { return m_sprite.glyphs.size(); }


    //------------------------------------------------------------------------//
    // Velocity                                                               //
    //------------------------------------------------------------------------//
public:
    inline const Vec2& Velocity() const noexcept { return m_velocity; }
    inline void Velocity(const Vec2 &v) noexcept { m_velocity = v;    }


    //------------------------------------------------------------------------//
    // Sprite                                                                 //
    //------------------------------------------------------------------------//
public:
    inline const Sprite_t& Sprite() const noexcept { return m_sprite; }
    inline void Sprite(const Sprite_t &s) noexcept { m_sprite = s;    }


    //------------------------------------------------------------------------//
    // Type                                                                   //
    //------------------------------------------------------------------------//
public:
    inline const ObjectType Type() const noexcept { return m_type; }


    //------------------------------------------------------------------------//
    // Active                                                                 //
    //------------------------------------------------------------------------//
public:
    inline bool IsActive() const noexcept  { return m_active; }
    inline void SetActive(bool b) noexcept { m_active = b;}


    //------------------------------------------------------------------------//
    // Collision                                                              //
    //------------------------------------------------------------------------//
public:
    inline bool CollidesWith(const GameObject::SPtr &pObj) noexcept
    {
        // COREASSERT_ASSERT( pObj, "pObj cannot be nullptr");
        if(!IsActive() || !pObj->IsActive())
            return false;

        //---------------------------------------------------------------------
        // Query the values.
        const auto &this_pos = Position();
        const auto &that_pos = pObj->Position();

        const auto &this_size = Size();
        const auto &that_size = pObj->Size();

        //---------------------------------------------------------------------
        // Not on same row!
        //   Since all our entities are **exactly** one row tall
        //   this already shows that they're not colliding.
        if(int(this_pos.y) != int(that_pos.y))
            return false;

        //---------------------------------------------------------------------
        // This is on the left.
        if(this_pos.x + this_size < that_pos.x)
            return false;

        //---------------------------------------------------------------------
        // This is on the right.
        if(that_pos.x + that_size < this_pos.x)
            return false;

        return true;
    }


    //------------------------------------------------------------------------//
    // Action Methods                                                         //
    //------------------------------------------------------------------------//
public:
    virtual void Update() noexcept = 0;
    virtual void Render() noexcept = 0;

    virtual bool DecreaseHealth() noexcept { return false; }


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
protected:
    Engine    *m_pEngineRef    = nullptr;
    GameScene *m_pGameSceneRef = nullptr;

private:
    Vec2       m_position;
    Vec2       m_velocity;
    Sprite_t   m_sprite;
    ObjectType m_type;
    bool       m_active;
};
