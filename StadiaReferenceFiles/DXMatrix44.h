#pragma once
#include <DirectXMath.h>
namespace GPU {
    // 4x4 matrix
    class DXMatrix44 {
    public:
        DirectX::XMMATRIX get() const;
        void __vectorcall set(DirectX::XMMATRIX);
        void transpose();
    private:
        // the size of this class in memory is important to maintain
        // XMFLOAT4X4 is used instead of XMMATRIX to avoid byte-alignment problems in x86
        DirectX::XMFLOAT4X4 matrix;
    };
    DXMatrix44 operator*(const DXMatrix44 &a, const DXMatrix44 &b);
    DXMatrix44 operator*(const DXMatrix44 &a, const DirectX::XMMATRIX &b);
}
