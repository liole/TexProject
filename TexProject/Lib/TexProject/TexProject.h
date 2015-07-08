/*
Це "корінний" хедер, який і буде підключати можливий кінцевий
користувач-програміст (тобто, хтось з нас). Він має містити у
собі лише підключення основних хедерів, які необхідні для
нормальної роботи.
*/
#pragma once

/*
Першим підключається базовий хедер.
*/
#include <TexProject/TexProject_Header.h>

/*
Далі підключаємо усі необхідні модулі нашого проекту
*/
#include <TexProject/TexProject_Main.h>
#include <TexProject/TexProject_Math.h>
#include <TexProject/TexProject_Helpers.h>
#include <TexProject/TexProject_Windows.h>
#include <TexProject/TexProject_Interface.h>
#include <TexProject/TexProject_OpenGL.h>
#include <TexProject/TexProject_Direct3D.h>
#include <TexProject/TexProject_Shaders.h>
#include <TexProject/TexProject_Buffers.h>
#include <TexProject/TexProject_Textures.h>
#include <TexProject/TexProject_Geometry.h>
#include <TexProject/TexProject_Tools.h>
















