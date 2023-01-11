#pragma once
#include "AppSettings.h"
#include "AccountService.h"
#include "Cashmachine.h"

extern AppGlobalSettings appSett;
extern AccountService accService;
extern Cashmachine cashmachine;
extern enum AppControllerEnum appController;

enum AppControllerEnum {
	OPERATION_WINDOW ,
	DEPOSITE_WINDOW,
	WITHDRAWAL_WINDOW,
	//HISTORY_WINDOW
};
