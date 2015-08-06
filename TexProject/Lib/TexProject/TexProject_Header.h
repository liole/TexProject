/*
Це базовий хедер проекту, в якому будуть оголошені всі
базові типи, простори імен(namespace) і заголовки загальнодоступних
класів і структур. Його мають підключати в першу чергу усі без вийнятку
модулі проекту, щоб забезпечити 100% доступ до усіх структур і данних.
*/
#pragma once

/*
Константи, що відповідатимуть за платформу.
Якщо оголошений __TEXPROJECT_WIN__ - це збірка під Windows
__TEXPROJECT_LIN__ і __TEXPROJECT_MAC__ будуть використовуватись
для позначення збірок під Linux і MacOS відповідно.
Бажано одночасно визначати лише один з них.
*/
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
#define __TEXPROJECT_DIRECT3D__				1


#define __TEXPROJECT_RTGSCRIPT__			0


/*
Замість використаня константи _DEBUG в перевідках дебаг режиму -
будемо використовувати власну константу __TEXPROJECT_DEBUG__
*/
#ifdef _DEBUG
#define __TEXPROJECT_DEBUG__				1
#endif


/*
В таких блоках будемо писати платформо-залежний код.
*/
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


/*
Підключаємо платформо-незалежні бібліотеки.
Поки що не вирішене питання про спільну папку для всіх бібліотек,
тому ще невідомо де і як будуть зберігатись потрібні нам бібіліотеки
і як єдиним чином всіх їх підключати.
*/
#include <string>
#include <HalfFloat/half.hpp>


namespace TexProject
{
	/*
	Це буде неймспейс нашого проекту.
	Всі функції, неймспейси, класи, структури і т.д., які стосуються
	нашого проекту визначати лише в ньому. Вийнятками можуть бути
	маленькі локальні функції, які не використовуються за межами
	окремого моделя.
	*/
#if __TEXPROJECT_WIN__

	/*
	Типи void, bool і char поки не перевизначаємо.
	char використовувати лише для представлення символів. Для
	представлення чисел в межах одного байту, масок і т.д. використовувати
	перевизначені типи int8/uint8.
	*/

	/*
	Базові типи для представлення цілих чисел
	*/
	// Integer
	/*8-бітне ціле зі знаком*/
	typedef signed __int8					int8;
	/*8-бітне ціле без знаку*/
	typedef unsigned __int8					uint8;
	/*16-бітне ціле зі знаком*/
	typedef signed __int16					int16;
	/*16-бітне ціле без знаку*/
	typedef unsigned __int16				uint16;
	/*32-бітне ціле зі знаком*/
	typedef signed __int32					int32;
	/*32-бітне ціле без знаку*/
	typedef unsigned __int32				uint32;
	/*64-бітне ціле зі знаком*/
	typedef signed __int64					int64;
	/*64-бітне ціле без знаку*/
	typedef unsigned __int64				uint64;

	/*
	Базові типи для представлення арифметики з плаваючою комою
	*/
	// Float
	/*16-бітне число з плаваючою комою*/
	typedef half_float::half				float16;
	/*32-бітне число з плаваючою комою*/
	typedef float							float32;
	/*64-бітне число з плаваючою комою*/
	typedef double							float64;

	/*
	Базові типи для роботи з рядками
	*/
	// String
	/*Рядок char-символів*/
	typedef std::string						string;

	/*
	Решту потрібних типів слід підключати окремо у кожному окремому модулі,
	де вони необхідні.
	*/

#else
#if __TEXPROJECT_LIN__
	// Linux variant
#else
#if __TEXPROJECT_MAC__
	// MacOS variant
#endif
#endif
#endif

	/*
	Типи для представлення 2, 3 і 4-компонентних векторів і матриць,
	кватерніонів
	*/
	// Math
	/*2-компонентний вектор float32*/
	struct									vec2;
	/*2-компонентний вектор int32*/
	struct									ivec2;
	/*2-компонентний вектор uint32*/
	struct									uvec2;
	/*3-компонентний вектор float32*/
	struct									vec3;
	/*3-компонентний вектор int32*/
	struct									ivec3;
	/*3-компонентний вектор uint32*/
	struct									uvec3;
	/*4-компонентний вектор float32*/
	struct									vec4;
	/*4-компонентний вектор int32*/
	struct									ivec4;
	/*4-компонентний вектор uint32*/
	struct									uvec4;
	/*Матриця 2х2 float32*/
	struct									mat2;
	/*Матриця 3х3 float32*/
	struct									mat3;
	/*Матриця 4х4 float32*/
	struct									mat4;
	/*Кватерніон float32*/
	struct									quat;


	// Main
	/*Базовий клас для винятків*/
	struct Exception;
	/*Помилка, що закриває програму*/
	struct ErrorException;


	/*
	Всеможливі допоміжні типи
	*/
	// Helpers
	namespace Helper
	{
		/*Структурні елементи*/
		namespace Structure
		{
			/*
			Тип-контейнер, що містить вказівники на усі екземпляри класу.
			Порядок елементів в контейнері може змінюватись.
			*/
			template<typename T,bool autoAdd = false,bool autoRemove = true>
			struct IndirectClassArray;
		}
	}

	/*
	Типи для роботи з вікнами.
	*/
	// Windows
	/*Базовий простір імен для роботи з вікнами*/
	namespace Window
	{
		struct Basic;
		struct Main;
		struct Render;


		namespace RenderContext
		{

			/*Базовий контекст виводу*/
			struct Basic;

#ifdef __TEXPROJECT_WIN__
			/*Контекст Windows*/
			struct Default;
#endif

#ifdef __TEXPROJECT_OPENGL__
			/*Контекст OpenGL*/
			struct OpenGL;
#endif

#ifdef __TEXPROJECT_DIRECT3D__
			/*Контекст Direct3D*/
			struct Direct3D;
#endif
		
		};


		/*Ініціалізація*/
		void								Init();
		/*Деініціалізація*/
		void								Free();
		/*Функція обробки усіх вікон.*/
		bool								Process();
	}


#if __TEXPROJECT_WIN__
	/*stuff fow windows*/
	namespace Windows
	{
		/*Windows textures(Bitmaps)*/
		struct Texture;
	}
#endif


#if __TEXPROJECT_OPENGL__
	/*Структури і методи бібліотеки OpenGL*/
	// OpenGL
	/*Головний неймспейс OpenGL*/
	namespace OpenGL
	{
		// Shader
		/*Клас шейдера*/
		struct Shader;

		namespace Buffer
		{
			//enum struct Type;

			namespace Attribute
			{
				//enum struct DataType;
				struct Params;
			}

			struct Data;
			struct Index;
			struct Array;
			struct Uniform;
			struct Transform;

			struct Frame;
		}

		struct Texture;
	}
#endif


#ifdef __TEXPROJECT_DIRECT3D__
	/*Головний неймспейс Direct3D*/
	namespace Direct3D
	{
		namespace Buffer
		{
			struct Data;
			struct Index;
		}

		struct Shader;
	}
#endif


#if __TEXPROJECT_DEVIL__
	/*Структури і методи бібліотеки DevIL*/
	//DevIL
	/*Головний неймспейс DevIL*/
	namespace DevIL
	{
	}
#endif


	// Textures
	/*Неймспейс текстур*/
	namespace Texture
	{
		struct D1;
		struct D2;
		struct D3;
		struct Cube;
	}


	//
	class	Lexer;
	class	Parser;
	struct	Checker;
	struct	Translator;
	struct	Script;
}


















