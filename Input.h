#pragma once
//DirectINPUT
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <wrl.h>
#include "WinApp.h"
class Input
{
public:

	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:

	void Initialise(WinApp* winApp);

	void Update();

	bool PushKey(BYTE keyNumber);
	bool TriggerKey(BYTE keyNumber);

private:
	ComPtr<IDirectInput8> directInput;
	ComPtr<IDirectInputDevice8> keyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};
	WinApp* winApp_ = nullptr;

};

