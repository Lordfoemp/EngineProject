#pragma once

#include <stdio.h>
#include <iostream> // std::cout
#include <sstream> // stringstream
#include <memory> // smart pointers
#include <vector>
#include <chrono>
#include <thread>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// Engine includes
#include "Locator.h"
//#include "Components.h"

// ---------------------
// Disable warning
// ---------------------
// GLM
#pragma warning(disable : 4201)
#pragma warning(disable : 4702)



// ---------------------
// MACROs
// ---------------------
#pragma region MACROs
/* ***************** */
/* DELETING POINTERS */
/* ***************** */
#define DELETE_POINTER( x ) \
if (x != NULL)			    \
{						    \
    delete x;			    \
    x = NULL;		        \
}
#define DELETE_POINTERS( x, size ) 	\
for (size_t i{}; i < size; ++i)		\
{									\
	DELETEPOINTER(x[i]);			\
}									\
x.clear();
#pragma endregion