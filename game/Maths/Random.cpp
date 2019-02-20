//~---------------------------------------------------------------------------//
//                     _______  _______  _______  _     _                     //
//                    |   _   ||       ||       || | _ | |                    //
//                    |  |_|  ||       ||   _   || || || |                    //
//                    |       ||       ||  | |  ||       |                    //
//                    |       ||      _||  |_|  ||       |                    //
//                    |   _   ||     |_ |       ||   _   |                    //
//                    |__| |__||_______||_______||__| |__|                    //
//                             www.amazingcow.com                             //
//  File      : Random.cpp                                                    //
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
#include "Maths/Random.h"
// std
#include <time.h>
#include <random>


//----------------------------------------------------------------------------//
// Enums / Constants / Typedefs                                               //
//----------------------------------------------------------------------------//
typedef std::uniform_int_distribution <int>   intRand;
typedef std::uniform_real_distribution<float> floatRand;


//----------------------------------------------------------------------------//
// Variables                                                                  //
//----------------------------------------------------------------------------//
namespace
{
    std::default_random_engine rGen;
    bool                       m_initialized;
}


//------------------------------------------------------------------------//
// Init / Shutdown                                                        //
//------------------------------------------------------------------------//
void Random::Init(int randomSeed) noexcept
{
    if(randomSeed == -1)
        randomSeed = time(nullptr);

    rGen.seed(randomSeed);
    m_initialized = true;
}

bool Random::IsInitialized() noexcept
{
    return m_initialized;
}


//------------------------------------------------------------------------//
// Random Methods                                                         //
//------------------------------------------------------------------------//
float Random::Float(float min, float max) noexcept
{
    floatRand rnd(min, max);
    return rnd(rGen);
}

int Random::Int(int min, int max) noexcept
{
    intRand rnd(min, max);
    return rnd(rGen);
}
