#pragma once

#include <d3dx9.h>

using IDevice = IDirect3D9*;

using IRenderDevice = IDirect3DDevice9*;
using ISurface = IDirect3DSurface9*;
using ISpriteHandler = ID3DXSprite*;

using Texture = IDirect3DTexture9*;
using ImageInfo = D3DXIMAGE_INFO;
using Color = D3DCOLOR;
using PresentationParameters = D3DPRESENT_PARAMETERS;