//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : GameScene.cpp                                                 //
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
#include "GameScene.h"
// std
#include <algorithm>
// SpaceRaiders
#include "Engine.h"
#include "Input.h"
#include "Random.h"
#include "MenuScene.h"
#include "ScoreHelper.h"

#undef max

//----------------------------------------------------------------------------//
// Constants                                                                  //
//----------------------------------------------------------------------------//
constexpr auto kScore_Laser = 5;
constexpr auto kScore_Alien = 10;
constexpr auto kScore_BetterAlien = 20;

constexpr auto kCount_Aliens = 10;


//----------------------------------------------------------------------------//
// CTOR / DTOR                                                                //
//----------------------------------------------------------------------------//
GameScene::GameScene(
    Engine* pEngineRef,
    int     level,
    bool    demoMode) noexcept :
    // Base class
    Scene(pEngineRef),
    // Members
    m_background(pEngineRef),
    m_level(level),
    m_demoMode(demoMode)
{
    m_hiScore = ScoreHelper::LoadScore();
    ResetLevel();

    if (m_demoMode)
    {
        m_pDemoInput = std::make_shared<RandomInput>();
        m_pEngineRef->SetInput(m_pDemoInput.get());
    }
    else
    {
        m_pKeyboardInput = std::make_shared<KeyboardInput>();
        m_pEngineRef->SetInput(m_pKeyboardInput.get());
    }
}


//----------------------------------------------------------------------------//
// Lifecycle                                                                  //
//----------------------------------------------------------------------------//
void GameScene::OnEnter() noexcept
{
    // Empty...
}

void GameScene::OnExit() noexcept
{
    // Empty...
}

//----------------------------------------------------------------------------//
// Update / Render                                                            //
//----------------------------------------------------------------------------//
void GameScene::Update() noexcept
{
    //--------------------------------------------------------------------------
    // Explosions.
    bool all_explosions_done = true;
    for (const auto& p_obj : m_explosions)
    {
        p_obj->Update();
        if (p_obj->IsActive())
            all_explosions_done = false;
    }

    //--------------------------------------------------------------------------
    // Game over - Let the explosions complete the animation.
    if (m_gameOver)
    {
        if (all_explosions_done)
            GoToMenu();

        return;
    }

    //--------------------------------------------------------------------------
    // Player.
    m_pPlayer->Update();

    //--------------------------------------------------------------------------
    // Player Lasers.
    for (const auto& p_obj : m_playerLasers)
        p_obj->Update();

    //--------------------------------------------------------------------------
    // Aliens.
    for (const auto& p_obj : m_aliens)
        p_obj->Update();

    //--------------------------------------------------------------------------
    // Alien Lasers.
    for (const auto& p_obj : m_alienLasers)
        p_obj->Update();

    //--------------------------------------------------------------------------
    // Collisions.
    CheckCollisions();

    //--------------------------------------------------------------------------
    // Level Clear.
    if (m_aliveAliensCount <= 0)
    {
        ++m_level;

        ResetAliens();
        ResetLasers();
    }


    //--------------------------------------------------------------------------
    // Exit
    if (m_pEngineRef->GetInput()->Exit())
        GoToMenu();
}

void GameScene::Render() noexcept
{
    m_background.Render();

    //--------------------------------------------------------------------------
    // Player.
    m_pPlayer->Render();

    //--------------------------------------------------------------------------
    // Player Lasers.
    for (const auto& p_obj : m_playerLasers)
        p_obj->Render();

    //--------------------------------------------------------------------------
    // Aliens.
    for (const auto& p_obj : m_aliens)
        p_obj->Render();

    //--------------------------------------------------------------------------
    // Alien Lasers.
    for (const auto& p_obj : m_alienLasers)
        p_obj->Render();

    //--------------------------------------------------------------------------
    // Explosions.
    for (const auto& p_obj : m_explosions)
        p_obj->Render();


    const auto& bounds = m_pEngineRef->Bounds();
    //--------------------------------------------------------------------------
    // Score / Lives.
    auto status_msg = std::string("LEVEL: ") + std::to_string(m_level + 1)
        + std::string(" | SCORE: ") + std::to_string(m_score)
        + std::string(" | HI-SCORE: ") + std::to_string(m_hiScore)
        + std::string(" | LIVES: ") + std::to_string(m_lives);

    m_pEngineRef->DrawString(
        bounds.x * 0.5f - status_msg.size() * 0.5f,
        bounds.y - 1,
        status_msg,
        FG_WHITE
    );


    //--------------------------------------------------------------------------
    // Let explicit that we're on demo mode.
    if (m_demoMode)
    {

        auto msg = std::string("--> [ D E M O ] <--");
        m_pEngineRef->DrawString(
            bounds.x * 0.5f - msg.size() * 0.5f,
            bounds.y * 0.5f,
            msg,
            FG_WHITE | BG_RED
        );
    }
}


//----------------------------------------------------------------------------//
// Collisions                                                                 //
//----------------------------------------------------------------------------//
void GameScene::CheckCollisions() noexcept
{
    //--------------------------------------------------------------------------
    // Player Lasers.
    for (auto& p_laser : m_playerLasers)
    {
        if (!p_laser->IsActive())
            continue;

        //----------------------------------------------------------------------
        // Against Alien Lasers.
        for (auto& p_alien_laser : m_alienLasers)
        {
            if (!p_alien_laser->IsActive())
                continue;

            if (p_laser->CollidesWith(p_alien_laser))
            {
                GenerateExplosion(
                    p_laser.get(),
                    p_alien_laser.get()
                );
                UpdateScore(kScore_Laser);

                break;
            }
        }

        //----------------------------------------------------------------------
        // Against Aliens.
        for (auto& p_alien : m_aliens)
        {
            if (!p_alien->IsActive())
                continue;

            if (p_laser->CollidesWith(p_alien))
            {
                GenerateExplosion(
                    p_laser.get(),
                    p_alien.get()
                );

                // Alien isn't dead yet!
                if (!p_alien->DecreaseHealth())
                {
                    p_alien->SetActive(true);
                    break;
                }

                UpdateScore(
                    (p_alien->IsBetter()) ? kScore_BetterAlien : kScore_Alien
                );

                --m_aliveAliensCount;
                break;
            }
        }
    }

    //--------------------------------------------------------------------------
    // Alien Lasers.
    for (auto& p_laser : m_alienLasers)
    {
        if (!p_laser->IsActive())
            continue;


        if (p_laser->CollidesWith(m_pPlayer))
        {
            PlayerHit(p_laser.get());
            return;
        }
    }

    //--------------------------------------------------------------------------
    // Aliens.
    for (auto& p_alien : m_aliens)
    {
        if (!p_alien->IsActive())
            continue;

        if (p_alien->CollidesWith(m_pPlayer))
        {
            PlayerHit(p_alien.get());
            --m_aliveAliensCount;

            return;
        }
    }
}

void GameScene::PlayerHit(GameObject* pObjRef) noexcept
{
    GenerateExplosion(
        m_pPlayer.get(),
        pObjRef
    );

    // Update the lives.
    --m_lives;
    if (m_lives <= 0)
    {
        m_gameOver = true;
        return;
    }

    // Reset the objects.
    ResetLasers();
    ResetPlayer();
}


//----------------------------------------------------------------------------//
// Lasers                                                                     //
//----------------------------------------------------------------------------//
void GameScene::SpawnLaser(const Vec2& pos, GameObject::ObjectType type)
{
    if (type == GameObject::ObjectType::AlienLaser) SpawnAlienLaser(pos);
    else if (type == GameObject::ObjectType::PlayerLaser) SpawnPlayerLaser(pos);
    // else   COREASSERT_ASSERT(false, "pObj isn't a laser: %d", type);
}

//------------------------------------------------------------------------------
// Helpers
void GameScene::SpawnAlienLaser(const Vec2& pos)
{
    // COREASSERT_ASSERT(
    //     m_alienLasers.size() <= m_maxAliensLasersCount,
    //     "Invalid alien lasers count: (%d)",
    //     m_alienLasers.size()
    // );

    //--------------------------------------------------------------------------
    // Try to find a laser that is inactive.
    auto it = std::find_if(
        std::begin(m_alienLasers),
        std::end(m_alienLasers),
        [](const AlienLaser::SPtr& pObj) {
            return !pObj->IsActive();
        }
    );

    //--------------------------------------------------------------------------
    // Not found, but we didn't hit our limit yet.
    if (it == std::end(m_alienLasers))
    {
        if (m_alienLasers.size() >= m_maxAliensLasersCount)
            return;

        auto p_laser = std::make_shared<AlienLaser>(
            m_pEngineRef,
            this,
            pos
            );
        m_alienLasers.push_back(p_laser);
    }
    //--------------------------------------------------------------------------
    // Found an available laser ;D
    else
    {
        (*it)->SetActive(true);
        (*it)->Position(pos);
    }
}

void GameScene::SpawnPlayerLaser(const Vec2& pos)
{
    // COREASSERT_ASSERT(
    //     m_playerLasers.size() <= m_maxPlayerLasersCount,
    //     "Invalid player lasers count: (%d)",
    //     m_playerLasers.size()
    // );

    //--------------------------------------------------------------------------
    // Try to find a laser that is inactive.
    auto it = std::find_if(
        std::begin(m_playerLasers),
        std::end(m_playerLasers),
        [](const PlayerLaser::SPtr& pObj) {
            return !pObj->IsActive();
        }
    );

    //--------------------------------------------------------------------------
    // Not found, but we didn't hit our limit yet.
    if (it == std::end(m_playerLasers))
    {
        if (m_playerLasers.size() >= m_maxPlayerLasersCount)
            return;

        auto p_laser = std::make_shared<PlayerLaser>(
            m_pEngineRef,
            this,
            pos
            );
        m_playerLasers.push_back(p_laser);
    }
    //--------------------------------------------------------------------------
    // Found an available laser ;D
    else
    {
        (*it)->SetActive(true);
        (*it)->Position(pos);
    }
}


//----------------------------------------------------------------------------//
// Explosions                                                                 //
//----------------------------------------------------------------------------//
void GameScene::GenerateExplosion(
    GameObject* pObj1,
    GameObject* pObj2) noexcept
{
    //--------------------------------------------------------------------------
    // Kill both objects.
    pObj1->SetActive(false);
    pObj2->SetActive(false);

    //--------------------------------------------------------------------------
    // Try to find a explosion that is inactive.
    auto it = std::find_if(
        std::begin(m_explosions),
        std::end(m_explosions),
        [](const Explosion::SPtr& pObj) {
            return !pObj->IsActive();
        }
    );

    //
    auto pos = pObj1->Middle();
    auto size = (pObj1->Size() + pObj2->Size());

    //--------------------------------------------------------------------------
    // Try to find an inactive explosion, if not possible create one.
    if (it != std::end(m_explosions))
    {
        (*it)->Explode(pos, size);
    }
    else
    {
        auto p_explosion = std::make_shared<Explosion>(
            m_pEngineRef,
            this,
            pos,
            size
            );
        m_explosions.push_back(p_explosion);
    }
}


//----------------------------------------------------------------------------//
// Score                                                                      //
//----------------------------------------------------------------------------//
void GameScene::UpdateScore(int score)
{
    m_score += score;
    m_hiScore = std::max(m_score, m_hiScore);

    ScoreHelper::SaveScore(m_hiScore);
}


//----------------------------------------------------------------------------//
// Helpers                                                                    //
//----------------------------------------------------------------------------//
void GameScene::ResetLevel() noexcept
{
    m_gameOver = false;

    ResetPlayer();
    ResetAliens();
    ResetLasers();
}

void GameScene::ResetPlayer() noexcept
{
    auto world_bounds = m_pEngineRef->Bounds();
    auto player_pos = Vec2(world_bounds.x * 0.5f, world_bounds.y - 2);

    //--------------------------------------------------------------------------
    // Player already created.
    if (m_pPlayer)
    {
        m_pPlayer->Position(player_pos);
        m_pPlayer->SetActive(true);

        return;
    }

    //--------------------------------------------------------------------------
    // Create the player for the first time.
    m_maxPlayerLasersCount = 4;
    m_pPlayer = std::make_shared<PlayerShip>(
        m_pEngineRef,
        this,
        player_pos
        );
}

void GameScene::ResetAliens() noexcept
{
    auto world_bounds = m_pEngineRef->Bounds();
    auto player_pos = Vec2(world_bounds.x * 0.5f, world_bounds.y - 2);

    // Erase the previous aliens.
    m_aliens.clear();

    // Calculate the counters.
    m_maxAliensCount = kCount_Aliens + (2 * m_level);
    m_maxAliensLasersCount = (m_maxAliensCount / 2) + m_level;
    m_aliveAliensCount = m_maxAliensCount;

    // Create the aliens.
    for (int i = 0; i < m_maxAliensCount; ++i)
    {
        auto alien_pos = Vec2(
            Random::Float(0, world_bounds.x),
            Random::Float(0, world_bounds.y / 2)
        );

        auto p_alien = std::make_shared<Alien>(
            m_pEngineRef,
            this,
            alien_pos
            );
        m_aliens.push_back(p_alien);
    }

}

void GameScene::ResetLasers() noexcept
{
    // Alien.
    for (const auto& p_laser : m_alienLasers)
        p_laser->SetActive(false);

    // Player.
    for (const auto& p_laser : m_playerLasers)
        p_laser->SetActive(false);
}

void GameScene::GoToMenu() noexcept
{
    auto p_scene = std::make_shared<MenuScene>(m_pEngineRef);
    m_pEngineRef->SetScene(p_scene);
}
