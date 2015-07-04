#include "TexProject_Direct3D.h"
using namespace TexProject;


void TexProject::Direct3D::test()
{
	IDirect3DDevice9* d3ddev = nullptr;

	IDirect3D9* d3d = Direct3DCreate9(D3D_SDK_VERSION);
	if(!d3d) Error("Cant create direct device.");

	D3DPRESENT_PARAMETERS d3dpp;

	ZeroMemory(&d3dpp,sizeof(d3dpp));
	d3dpp.Windowed = false;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = NULL;	//hWnd;

	d3d->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		NULL,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,	// D3DCREATE_HARDWARE_VERTEXPROCESSING
		&d3dpp,
		&d3ddev
	);
}































