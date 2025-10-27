#pragma once
//DirectINPUT
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <wrl.h>
class Input
{
public:

	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;

public:

	void Initialise(HINSTANCE hinstance,HWND hwnd);

	void Update();

	bool PushKey(BYTE keyNumber);
	bool TriggerKey(BYTE keyNumber);

private:
	ComPtr<IDirectInput8> directInput;
	ComPtr<IDirectInputDevice8> keyboard;
	BYTE key[256] = {};
	BYTE keyPre[256] = {};

};

