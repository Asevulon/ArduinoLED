﻿
// ArduinoLED.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CArduinoLEDApp:
// Сведения о реализации этого класса: ArduinoLED.cpp
//

class CArduinoLEDApp : public CWinApp
{
public:
	CArduinoLEDApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CArduinoLEDApp theApp;