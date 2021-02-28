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


// ---------------------
// Disable warning
// ---------------------
// GLM
#pragma warning(disable : 4201)

// ---------------------
// Mem leak details
// ---------------------
#pragma region Memory Leaks
// When debugging changes all calls to "new" to be calls to "DEBUG_NEW" allowing for memory leaks to
// give you the file name and line number where it occurred.
// Reference: https://rhyous.wordpress.com/2009/10/13/how-to-find-the-file-and-line-number-of-memory-leaks-using-c-with-wxwidgets-in-visual-studio-2008/
#ifdef _DEBUG
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK ,__FILE__, __LINE__)
#define new DEBUG_NEW
#else
#define DEBUG_NEW new
#endif
#pragma endregion

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