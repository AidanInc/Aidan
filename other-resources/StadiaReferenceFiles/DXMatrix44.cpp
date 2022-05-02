#include "DXMatrix44.h"
using namespace GPU;

void __vectorcall DXMatrix44::set(DirectX::XMMATRIX a) {
    DirectX::XMStoreFloat4x4(&matrix, a);
}

DirectX::XMMATRIX DXMatrix44::get() const {
    return DirectX::XMLoadFloat4x4(&matrix);
}

void DXMatrix44::transpose() {
    set( DirectX::XMMatrixTranspose(get()) );
}

DXMatrix44 GPU::operator*(const DXMatrix44 &a, const DXMatrix44 &b) {
    DXMatrix44 r;
    r.set(a.get() * b.get());
    return r;
}

DXMatrix44 GPU::operator*(const DXMatrix44 &a, const DirectX::XMMATRIX &b) {
    DXMatrix44 r;
    r.set(a.get() * b);
    return r;
}