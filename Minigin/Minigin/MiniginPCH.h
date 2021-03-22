#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>


// External Includes
//#define WIN32_LEAN_AND_MEAN
#include <chrono>
#include <thread>
#include <SDL.h>
#include <windows.h>


#include "Locator.h"

// ---------------------
// Disable warning
// ---------------------
// GLM
#pragma warning(disable : 4201)

// ---------------------
// MACROs
// ---------------------
#pragma region MACROs
/* ***************** */
/* DELETING POINTERS */
/* ***************** */
#define DELETE_POINTER( x ) \
if (x != NULL)			   \
{						   \
    delete x;			   \
    x = nullptr;		   \
}
#define DELETE_POINTERS( x, size ) 	\
for (size_t i{}; i < size; ++i)		\
{									\
	DELETEPOINTER(x[i]);			\
}									\
x.clear();
#pragma endregion