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
#define __TEXPROJECT_WIN__					1
//#define __TEXPROJECT_LIN__
//#define __TEXPROJECT_MAC__


/*
Замість використаня константи _DEBUG в перевідках дебаг режиму -
будемо використовувати власну константу __TEXPROJECT_DEBUG__
*/
#ifdef _DEBUG
#define __TEXPROJECT_DEBUG__
#endif


/*
В таких блоках будемо писати платформо-залежний код.
*/
#ifdef __TEXPROJECT_WIN__

#include <Windows.h>

#else
#ifdef __TEXPROJECT_LIN__
// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
// MacOS variant
#endif
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
#ifdef __TEXPROJECT_WIN__

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
#ifdef __TEXPROJECT_LIN__
	// Linux variant
#else
#ifdef __TEXPROJECT_MAC__
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

		/*Ініціалізація*/
		void								Init();
		/*Деініціалізація*/
		void								Free();
		/*Функція обробки усіх вікон.*/
		void								Process();
	}

}


















