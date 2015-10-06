#pragma once

#pragma region Defines

#define __TEXPROJECT_PLATFORM_NONE__		0
#define __TEXPROJECT_PLATFORM_WIN__			1
#define __TEXPROJECT_PLATFORM_LIN__			2
#define __TEXPROJECT_PLATFORM_MAC__			3


#define __TEXPROJECT_PLATFORM__				__TEXPROJECT_PLATFORM_WIN__


#define __TEXPROJECT_ARCHITECTURE_UNKNOWN__	0
#define __TEXPROJECT_ARCHITECTURE_X64__		1
#define __TEXPROJECT_ARCHITECTURE_X86__		2


#define __TEXPROJECT_ARCHITECTURE__			__TEXPROJECT_ARCHITECTURE_X86__


#define __TEXPROJECT_WIN__					(__TEXPROJECT_PLATFORM__ == __TEXPROJECT_PLATFORM_WIN__)
#define __TEXPROJECT_LIN__					(__TEXPROJECT_PLATFORM__ == __TEXPROJECT_PLATFORM_LIN__)
#define __TEXPROJECT_MAC__					(__TEXPROJECT_PLATFORM__ == __TEXPROJECT_PLATFORM_MAC__)


#define __TEXPROJECT_MEMORY_LEAK__			0
#define __TEXPROJECT_OPENGL__				1
#define __TEXPROJECT_DEVIL__				1
#define __TEXPROJECT_DIRECT3D__				0


#define __TEXPROJECT_RTGSCRIPT__			0


#ifdef _DEBUG
#define __TEXPROJECT_DEBUG__				1
#endif


#if __TEXPROJECT_WIN__

#include <Windows.h>

#else
#if __TEXPROJECT_LIN__
// Linux variant
#else
#if __TEXPROJECT_MAC__
// MacOS variant
#endif
#endif
#endif



#if __TEXPROJECT_DEBUG__ && __TEXPROJECT_MEMORY_LEAK__
#include <VLD/include/vld.h>

#if __TEXPROJECT_ARCHITECTURE__ == __TEXPROJECT_ARCHITECTURE_X86__
#pragma comment(lib, "/Win32/vld.lib") 
#else
#pragma comment(lib, "/Win64/vld.lib") 
#endif

#endif

#pragma endregion

#include <string>
#include <HalfFloat/half.hpp>

#pragma region Test
#pragma endregion

namespace TexProject
{
#pragma region Scalar
#if __TEXPROJECT_WIN__
#pragma region Interger
	typedef signed __int8					int8;		// 8-бітне ціле зі знаком
	typedef unsigned __int8					uint8;		// 8-бітне ціле без знаку
	typedef signed __int16					int16;		// 16-бітне ціле зі знаком
	typedef unsigned __int16				uint16;		// 16-бітне ціле без знаку
	typedef signed __int32					int32;		// 32-бітне ціле зі знаком
	typedef unsigned __int32				uint32;		// 32-бітне ціле без знаку
	typedef signed __int64					int64;		// 64-бітне ціле зі знаком
	typedef unsigned __int64				uint64;		// 64-бітне ціле без знаку
#pragma endregion
#pragma region Float
	typedef half_float::half				float16;	// 16-бітне число з плаваючою комою
	typedef float							float32;	// 32-бітне число з плаваючою комою
	typedef double							float64;	// 64-бітне число з плаваючою комою
#pragma endregion
#pragma region String
	typedef std::string						string;
#pragma endregion
#else
#if __TEXPROJECT_LIN__
	// Linux variant
#else
#if __TEXPROJECT_MAC__
	// MacOS variant
#endif
#endif
#endif
#pragma endregion
#pragma region Vector/Matrix
	struct									vec2;	// 2-компонентний вектор float32
	struct									ivec2;	// 2-компонентний вектор int32
	struct									uvec2;	// 2-компонентний вектор uint32
	struct									vec3;	// 3-компонентний вектор float32
	struct									ivec3;	// 3-компонентний вектор int32
	struct									uvec3;	// 3-компонентний вектор uint32
	struct									vec4;	// 4-компонентний вектор float32
	struct									ivec4;	// 4-компонентний вектор int32
	struct									uvec4;	// 4-компонентний вектор uint32
	struct									mat2;	// Матриця 2х2 float32
	struct									mat3;	// Матриця 3х3 float32
	struct									mat4;	// Матриця 4х4 float32
	struct									quat;	// Кватерніон float32
#pragma endregion
#pragma region Main
	struct Exception;
#pragma endregion
#pragma region DevIL
	namespace DevIL
	{
	}
#pragma endregion
#pragma region WinAPI
	namespace WinAPI
	{
		class RenderContext;
		class GraphicUserInterface;
		typedef GraphicUserInterface							GUI;
		class Texture;
	}
#pragma endregion
#pragma region OpenGL
	namespace OpenGL
	{
		class RenderContext;
		class ContextBind;
		namespace Buffer
		{
			class Attribute;
			class Data;
			class Index;
			class Frame;
		}
		class Shader;
		class Mesh;
		class Texture;
	}
#pragma endregion
#pragma region Graphic User Interface
	class GraphicUserInterface;
	typedef GraphicUserInterface								GUI;
	namespace GraphicUserInterfaces
	{
#if __TEXPROJECT_WIN__
		typedef WinAPI::GraphicUserInterface					Default;
#endif
	}
#pragma endregion
#pragma region Windows
	class RenderContext;
	namespace RenderContexts
	{
#if __TEXPROJECT_WIN__
		typedef WinAPI::RenderContext							Default;
#endif
	}
	class Window;
#pragma endregion
#pragma region Textures
	namespace Texture
	{
		struct D1;
		struct D2;
		struct D3;
		struct Cube;
	}
#pragma endregion
#pragma region RTGScript
	class	Lexer;
	struct	Parser;
	struct	Checker;
	struct	Translator;
	struct	Script;
#pragma endregion
}


















