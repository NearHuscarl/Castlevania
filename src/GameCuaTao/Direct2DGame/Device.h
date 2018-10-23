#pragma once

#include <d3dx9.h>

using IDevice = IDirect3D9*;

using IRenderDevice_ = IDirect3DDevice9*;
using ISurface_ = IDirect3DSurface9*;
using ISpriteHandler_ = ID3DXSprite*;

using ITexture_ = IDirect3DTexture9*;
using IFont_ = ID3DXFont*;

using ImageInfo = D3DXIMAGE_INFO;
using PresentationParameters = D3DPRESENT_PARAMETERS;