#pragma once
#include <d3d11.h>
#include <string>
#include <vector>
#include <wrl.h>
#include "CoreException.h"

#ifndef NDEBUG
#include "DxgiInfoManager.h"
#endif

class Graphics
{
public:
    class HrException : public CoreException
    {
    public:
        HrException( int line,const char* file,HRESULT hr,std::vector<std::string> infoMsgs = {} ) noexcept;
        const char* what() const noexcept override;
        const char* GetType() const noexcept override;
        HRESULT GetErrorCode() const noexcept;
        std::string GetErrorString() const noexcept;
        std::string GetErrorInfo() const noexcept;
    private:
        HRESULT hr;
        std::string info;
    };
    
    class InfoException : public CoreException
    {
    public:
        InfoException( int line,const char* file,std::vector<std::string> infoMsgs ) noexcept;
        const char* what() const noexcept override;
        const char* GetType() const noexcept override;
        std::string GetErrorInfo() const noexcept;
    private:
        std::string info;
    };
    
    class DeviceRemovedException : public HrException
    {
        using HrException::HrException;
    public:
        const char* GetType() const noexcept override;
    private:
        std::string reason;
    };
    
public:
    Graphics(HWND hwnd);
    Graphics(const Graphics&) = delete;
    Graphics& operator=(const Graphics&) = delete;
    ~Graphics() = default;
    void EndFrame();
    void ClearBuffer(float red, float green, float blue) noexcept;
private:
#ifndef NDEBUG
    DxgiInfoManager infoManager;
#endif
    Microsoft::WRL::ComPtr<ID3D11Device> pDevice = nullptr;
    Microsoft::WRL::ComPtr<IDXGISwapChain> pSwap = nullptr;
    Microsoft::WRL::ComPtr<ID3D11DeviceContext> pContext = nullptr;
    Microsoft::WRL::ComPtr<ID3D11RenderTargetView> pTarget = nullptr;
};
