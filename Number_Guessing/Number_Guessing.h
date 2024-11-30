
// Number_Guessing.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CNumberGuessingApp:
// See Number_Guessing.cpp for the implementation of this class
//

class CNumberGuessingApp : public CWinApp
{
public:
	CNumberGuessingApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CNumberGuessingApp theApp;
