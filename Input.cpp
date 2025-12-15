#include "Input.h"
#include <cassert>

#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxguid.lib")



void Input::Initialize(WinApp* winApp)
{
    //借りてきたWinAppのインスタンスを記録
    this->winApp_ = winApp;

    HRESULT result;

    // DirectInputのインスタンス生成
    result = DirectInput8Create(winApp->GetHInstance(), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&directInput, nullptr);
    assert(SUCCEEDED(result));

    // キーボードデバイス生成
    result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
    assert(SUCCEEDED(result));

    // 入力データ形式のセット
    result = keyboard->SetDataFormat(&c_dfDIKeyboard);
    assert(SUCCEEDED(result));

    // 協調レベルのセット
    result = keyboard->SetCooperativeLevel(winApp->GetHwnd(), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
    assert(SUCCEEDED(result));
}

void Input::Update()
{

    memcpy(prekey, key, sizeof(char) * 256);

    //キーボード情報の取得開始
    keyboard->Acquire();

    keyboard->GetDeviceState(sizeof(key), key);

}

bool Input::PushKey(BYTE keyNumber) const
{
    //指定キーを押していればtrueを返す
    if (key[keyNumber])
    {
        return true;
    }
    //そうでなければfalseを返す
    return false;
}

bool Input::TriggerKey(BYTE keyNumber) const
{
    //指定キーを押していればtrueを返す
    if (key[keyNumber] && !prekey[keyNumber])
    {
        return true;
    }
    return false;
}