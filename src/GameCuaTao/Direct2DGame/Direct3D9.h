#pragma once

#include <d3d9.h>
#include <d3dx9math.h>

using IDevice_ = IDirect3D9*;

using IRenderDevice_ = IDirect3DDevice9*;
using ISurface_ = IDirect3DSurface9*;
using ISpriteHandler_ = ID3DXSprite*;

using ITexture_ = IDirect3DTexture9*;
using IFont_ = ID3DXFont*;

using ImageInfo = D3DXIMAGE_INFO;

// Math
using Matrix = D3DXMATRIX;

// Type
using DeviceType = D3DDEVTYPE;
using SurfaceFormat = D3DFORMAT;
using SwapEffect = D3DSWAPEFFECT;
using PresentationParameters = D3DPRESENT_PARAMETERS;