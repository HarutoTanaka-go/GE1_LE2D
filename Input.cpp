#include <Windows.h>
#include "Input.h"
#include "cassert"
#include <wrl.h>
using namespace Microsoft::WRL;
////DirectINPUT
//#define DIRECTINPUT_VERSION 0x0800
//#include <dinput.h>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")


void Input::Initialise(HINSTANCE hinstance, HWND hwnd)
{


	HRESULT result;

	//DirectInput 初期化
	/*IDirectInput8* directInput = nullptr;*/
	result = DirectInput8Create(
		hinstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&directInput,
		nullptr
	);
	assert(SUCCEEDED(result));

	//キーボード用デバイスの初期化
	result = directInput->CreateDevice(
		GUID_SysKeyboard,
		&keyboard,
		NULL
	);
	assert(SUCCEEDED(result));

	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));

	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));

}

void Input::Update()
{



	memcpy(keyPre, key, sizeof(key));

	keyboard->Acquire();

	
	keyboard->GetDeviceState(sizeof(key), key);


}

bool Input::PushKey(BYTE keyNumber)
{


	if (key[keyNumber]) {
		return true;
	}

	return false;
}

bool Input::TriggerKey(BYTE keyNumber)
{
	if (key[keyNumber]) {
		return true;
	}

	return false;
}
