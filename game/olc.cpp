#include "olc_sdl.h"

// Define our static variables
std::atomic<bool> olcConsoleGameEngine::m_bAtomActive(false);
std::condition_variable olcConsoleGameEngine::m_cvGameFinished;
std::mutex olcConsoleGameEngine::m_muxGame;


int len = 0, done = 0, bits = 0, which = 0,
sample_size = 0, position = 0, rate = 0;
Sint16 *stream[2];
