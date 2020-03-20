//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : GameScene.h                                                   //
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
#include <memory>
#include <string>
#include <vector>
// SpaceRaiders
#include "Vec2.h"
#include "Scene.h"
#include "Input.h"

#include "Alien.h"
#include "Background.h"
#include "GameObject.h"
#include "Explosion.h"
#include "AlienLaser.h"
#include "PlayerLaser.h"
#include "Player.h"


class GameScene :
    public Scene
{
    //------------------------------------------------------------------------//
    // Enums / Constants / Typdefs                                            //
    //------------------------------------------------------------------------//
private:
    typedef std::vector<Alien::SPtr> AliensList;
    typedef std::vector<AlienLaser::SPtr> AlienLasersList;
    typedef std::vector<PlayerLaser::SPtr> PlayerLasersList;
    typedef std::vector<Explosion::SPtr> ExplosionsList;


    //------------------------------------------------------------------------//
    // CTOR / DTOR                                                            //
    //------------------------------------------------------------------------//
public:
    GameScene(
        Engine* pEngineRef,
        int     level,
        bool    demoMode) noexcept;


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
    // Collisions                                                             //
    //------------------------------------------------------------------------//
private:
    void CheckCollisions() noexcept;
    void PlayerHit(GameObject* pObjRef) noexcept;


    //------------------------------------------------------------------------//
    // Player                                                                 //
    //------------------------------------------------------------------------//
public:
    const PlayerShip::SPtr& GetPlayer() const noexcept { return m_pPlayer; }
    void SetPlayer(const PlayerShip::SPtr& p) noexcept { m_pPlayer = p; }


    //------------------------------------------------------------------------//
    // Lasers                                                                 //
    //------------------------------------------------------------------------//
public:
    void SpawnLaser(const Vec2& pos, GameObject::ObjectType type);

    //--------------------------------------------------------------------------
    // Helpers
private:
    void SpawnAlienLaser(const Vec2& pos);
    void SpawnPlayerLaser(const Vec2& pos);


    //------------------------------------------------------------------------//
    // Explosion                                                              //
    //------------------------------------------------------------------------//
private:
    void GenerateExplosion(
        GameObject* pObj1,
        GameObject* pObj2) noexcept;


    //------------------------------------------------------------------------//
    // Score                                                                  //
    //------------------------------------------------------------------------//
private:
    void UpdateScore(int score);

    //------------------------------------------------------------------------//
    // Helpers                                                                //
    //------------------------------------------------------------------------//
private:
    void ResetLevel() noexcept;
    void ResetPlayer() noexcept;
    void ResetAliens() noexcept;
    void ResetLasers() noexcept;

    void GoToMenu() noexcept;


    //------------------------------------------------------------------------//
    // iVars                                                                  //
    //------------------------------------------------------------------------//
private:
    Background m_background;

    //--------------------------------------------------------------------------
    // Player.
    PlayerShip::SPtr m_pPlayer = nullptr;
    PlayerLasersList m_playerLasers;
    int              m_maxPlayerLasersCount = 0;

    //--------------------------------------------------------------------------
    // Aliens.
    AliensList       m_aliens;
    AlienLasersList  m_alienLasers;
    int              m_maxAliensCount = 0;
    int              m_maxAliensLasersCount = 0;
    int              m_aliveAliensCount = 0;;

    //--------------------------------------------------------------------------
    // Explosions.
    ExplosionsList m_explosions;

    //--------------------------------------------------------------------------
    // House Keeping.
    int                          m_level;
    bool                         m_demoMode;

    std::shared_ptr<RandomInput  > m_pDemoInput;
    std::shared_ptr<KeyboardInput> m_pKeyboardInput;

    //--------------------------------------------------------------------------
    // Score / Lives.
    int m_score = 0;
    int m_hiScore = 0;
    int m_lives = 3;

    bool m_gameOver;
};
