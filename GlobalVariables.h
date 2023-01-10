#pragma once
#include "AppSettings.h"
#include "AccountService.h"
#include "Cashmachine.h"

extern AppGlobalSettings appConf;
extern AccountService accService;
extern Cashmachine cashmachine;
extern enum AppControllerEnum appController;

enum AppControllerEnum {
	OPERATION_WINDOW = 0,
	DEPOSIT_WINDOW = 1,
	WITHDRAW_WINDOW = 2
};
