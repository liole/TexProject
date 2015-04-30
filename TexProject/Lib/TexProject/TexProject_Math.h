/*
Модуль з математикою
*/
#pragma once
#include <TexProject/TexProject_Header.h>


#include <math.h>


namespace TexProject
{
	/*
	Константи, які можуть використовуватись в обчисленнях
	*/

	const float32 _0f							= 0.0f;
	const float32 _1f							= 1.0f;
	const float32 _dev2f						= 0.5f;
	const float32 _PIf							= 3.1415926535897932384626433832795f;
	const float32 _2PIf							= 6.283185307179586476925286766559f;
	const float32 _180PIf						= 565.48667764616278292327580899031f;
	const float32 _devPIf						= 0.31830988618379067153776752674503f;
	const float32 _dev2PIf						= 0.15915494309189533576888376337251f;
	const float32 _2devPIf						= 0.63661977236758134307553505349006f;
	const float32 _PIdev2f						= 1.5707963267948966192313216916398f;
	const float32 _PIdev180f					= 0.01745329251994329576923690768489f;
	const float32 _180devPIf					= 57.295779513082320876798154814105f;
	const float32 _dev180PIf					= 0.00176838825657661484187648625969f;

	struct vec2
	{
		float32								x, y;

		inline								vec2();
		inline								vec2(const vec2&) = default;
		explicit inline						vec2(const float32 a_);
		inline								vec2(float32 x_, float32 y_);
		explicit inline						vec2(ivec2 a_);
		explicit inline						vec2(uvec2 a_);

		inline vec2&						operator = (const vec2&) = default;
		inline vec2&						operator = (const float32& a);

		inline vec2&						operator += (const vec2& a);
		inline vec2&						operator -= (const vec2& a);
		inline vec2&						operator *= (const vec2& a);
		inline vec2&						operator /= (const vec2& a);

		inline vec2							operator + (const vec2& a) const;
		inline vec2							operator - (const vec2& a) const;
		inline vec2							operator * (const vec2& a) const;
		inline vec2							operator / (const vec2& a) const;

		friend inline vec2					operator + (const vec2& a,const float32& b);
		friend inline vec2					operator - (const vec2& a,const float32& b);
		friend inline vec2					operator * (const vec2& a,const float32& b);
		friend inline vec2					operator / (const vec2& a,const float32& b);

		friend inline vec2					operator + (const float32& a,const vec2& b);
		friend inline vec2					operator - (const float32& a,const vec2& b);
		friend inline vec2					operator * (const float32& a,const vec2& b);
		friend inline vec2					operator / (const float32& a,const vec2& b);

		inline float32						length() const;
		inline void							sqr();
		inline void							normalize();
	};
	struct ivec2
	{
		int32								x, y;

		inline								ivec2();
		explicit inline						ivec2(int32 a_);
		inline								ivec2(int32 x_, int32 y_);
		explicit inline						ivec2(vec2);
		explicit inline						ivec2(uvec2);
		inline								ivec2(const ivec2&) = default;
		inline								~ivec2() = default;

		inline ivec2&						operator = (const int32& source);
		inline ivec2&						operator = (const vec2& source);
		inline ivec2&						operator = (const uvec2& source);

		inline ivec2						operator + (const ivec2& a) const;
		inline ivec2						operator - (const ivec2& a) const;
		inline ivec2						operator * (const ivec2& a) const;
		inline ivec2						operator / (const ivec2& a) const;

		friend inline ivec2					operator + (const ivec2& a,const int32& b);
		friend inline ivec2					operator - (const ivec2& a,const int32& b);
		friend inline ivec2					operator * (const ivec2& a,const int32& b);
		friend inline ivec2					operator / (const ivec2& a,const int32& b);

		friend inline ivec2					operator + (const ivec2& a,const uvec2& b);
		friend inline ivec2					operator - (const ivec2& a,const uvec2& b);
		friend inline ivec2					operator * (const ivec2& a,const uvec2& b);
		friend inline ivec2					operator / (const ivec2& a,const uvec2& b);

		friend inline ivec2					operator + (const int32& a,const ivec2& b);
		friend inline ivec2					operator - (const int32& a,const ivec2& b);
		friend inline ivec2					operator * (const int32& a,const ivec2& b);
		friend inline ivec2					operator / (const int32& a,const ivec2& b);

		friend inline ivec2					operator + (const uvec2& a,const ivec2& b);
		friend inline ivec2					operator - (const uvec2& a,const ivec2& b);
		friend inline ivec2					operator * (const uvec2& a,const ivec2& b);
		friend inline ivec2					operator / (const uvec2& a,const ivec2& b);

	};
	struct uvec2
	{
		uint32								x, y;

		inline								uvec2();
		explicit inline						uvec2(uint32 a_);
		inline								uvec2(uint32 x_, uint32 y_);

		inline uvec2&						operator = (const uint32& source);
		inline uvec2&						operator = (const vec2& source);
		inline uvec2&						operator = (const ivec2& source);

		inline uvec2						operator + (const uvec2& a) const;
		inline ivec2						operator - (const uvec2& a) const;
		inline ivec2						operator * (const uvec2& a) const;
		inline ivec2						operator / (const uvec2& a) const;

		inline uvec2						operator + (const uint32& a) const;
		inline ivec2						operator - (const uint32& a) const;
		inline ivec2						operator * (const uint32& a) const;
		inline ivec2						operator / (const uint32& a) const;

	};
	struct vec3
	{
		float32			x, y, z;

		inline			vec3();
		inline			vec3(float32 a_);
		inline			vec3(float32 x_, float32 y_, float32 z_);
		inline			vec3(vec2 xy_,float32 z_);
		inline			vec3(float32 x_,vec2 yz_);

		inline vec2		xy() const;
		inline vec2		xz() const;
	};
	struct ivec3
	{
		float32			x, y, z;
	};
	struct uvec3
	{
		uint32			x, y, z;

		inline			uvec3();
		inline explicit	uvec3(uint32 a_);
		inline			uvec3(uint32 x_,uint32 y_,uint32 z_);
		inline			uvec3(const uvec3&) = default;

		inline uvec3&	operator = (const uvec3&) = default;
	};
	struct vec4
	{
		float32			x, y, z, w;

		inline			vec4() = default;
		inline			vec4(const vec4&) = default;
		inline			vec4(float32 x_,float32 y_,float32 z_,float32 w_);

		inline vec4&	operator = (const vec4&) = default;
	};
	struct ivec4
	{
		int32			x, y, z, w;
	};
	struct uvec4
	{
		uint32			x, y, z, w;
	};
	struct mat2
	{
		float32			val[4];
	};
	struct mat3
	{
		float32			val[9];
	};
	struct mat4
	{
		float32			val[16];
	};
	struct quat
	{
		float32			x, y, z, w;
	};

	/*Конвертує радіани в градуси*/
	inline float32		degrees(float32 in);
	/*Конвертує градуси в радіани*/
	inline float32		radians(float32 in);

	/*Синус від значення в градусах*/
	inline float32		sinDg(float32 in);
	/*Косинус від значення в градусах*/
	inline float32		cosDg(float32 in);
	/*Тангенс від значення в градусах*/
	inline float32		tanDg(float32 in);
	/*Асинус в градусах*/
	inline float32		asinDg(float32 in);
	/*Акосинус в градусах*/
	inline float32		acosDg(float32 in);
	/*Атангенс в градусах*/
	inline float32		atanDg(float32 in);


	/*Скалярний добуток vec2*/
	inline float32		dot(const vec2& a, const vec2& b);
	/*Скалярний добуток vec3*/
	inline float32		dot(const vec3& a, const vec3& b);
	/*Скалярний добуток vec4*/
	inline float32		dot(const vec4& a, const vec4& b);

	/*Скалярний квадрат vec2*/
	inline float32		sqr(const vec2& a);

	/*Довжина vec2*/
	inline float32		length(const vec2& a);
	inline float32		length(const vec3& a);
	inline float32		length(const vec4& a);

	/*Нормалізований Vec2*/
	inline vec2			normalize(const vec2& a);

	/*Відстань між двома vec2*/
	inline float32		dist(const vec2& a,const vec2& b);

	/*Векторний добуток vec3*/
	inline vec3			cross(const vec3& a,const vec3& b);

	inline float32		getAng(const vec2& a,const vec2& b);

}


// vec2
TexProject::vec2::vec2()
{
}
TexProject::vec2::vec2(const float32 a_):
	x(a_), y(a_)
{
}
TexProject::vec2::vec2(float32 x_,float32 y_):
	x(x_),y(y_)
{
}
TexProject::vec2::vec2(ivec2 a_):
	x(float32(a_.x)),y(float32(a_.y))
{
}
TexProject::vec2::vec2(uvec2 a_):
	x(float32(a_.x)),y(float32(a_.y))
{
}


TexProject::vec2&							TexProject::vec2::operator = (const float32& a)
{
	x = a;
	y = a;
}

TexProject::vec2&							TexProject::vec2::operator += (const vec2& a)
{
	x += a.x;
	y += a.y;
	return *this;
}
TexProject::vec2&							TexProject::vec2::operator -= (const vec2& a)
{
	x -= a.x;
	y -= a.y;
	return *this;
}
TexProject::vec2&							TexProject::vec2::operator *= (const vec2& a)
{
	x *= a.x;
	y *= a.y;
	return *this;
}
TexProject::vec2&							TexProject::vec2::operator /= (const vec2& a)
{
	x /= a.x;
	y /= a.y;
	return *this;
}


TexProject::vec2							TexProject::vec2::operator + (const vec2& a) const
{
	return vec2	(
					x + a.x,
					y + a.y
				);
}
TexProject::vec2							TexProject::vec2::operator - (const vec2& a) const
{
	return vec2	(
					x - a.x,
					y - a.y
				);
}
TexProject::vec2							TexProject::vec2::operator * (const vec2& a) const
{
	return vec2	(
					x * a.x,
					y * a.y
				);
}
TexProject::vec2							TexProject::vec2::operator / (const vec2& a) const
{
	return vec2	(
					x / a.x,
					y / a.y
				);
}

TexProject::vec2							TexProject::operator + (const vec2& a,const float32& b)
{
	return vec2	(
					a.x + b,
					a.y + b
				);
}
TexProject::vec2							TexProject::operator - (const vec2& a,const float32& b)
{
	return vec2	(
					a.x - b,
					a.y - b
				);
}
TexProject::vec2							TexProject::operator * (const vec2& a,const float32& b)
{
	return vec2	(
					a.x * b,
					a.y * b
				);
}
TexProject::vec2							TexProject::operator / (const vec2& a,const float32& b)
{
	static float32 t;
	t = 1.0f/b;
	return vec2	(
					a.x * t,
					a.y * t
				);
}

TexProject::vec2							TexProject::operator + (const float32& a,const vec2& b)
{
	return vec2	(
					a + b.x,
					a + b.y
				);
}
TexProject::vec2							TexProject::operator - (const float32& a,const vec2& b)
{
	return vec2	(
					a - b.x,
					a - b.y
				);
}
TexProject::vec2							TexProject::operator * (const float32& a,const vec2& b)
{
	return vec2	(
					a * b.x,
					a * b.y
				);
}
TexProject::vec2							TexProject::operator / (const float32& a,const vec2& b)
{
	return vec2	(
					a / b.x,
					a / b.y
				);
}


// ivec2
TexProject::ivec2::ivec2()
{
}
TexProject::ivec2::ivec2(int32 a_):
	x(a_), y(a_)
{
}
TexProject::ivec2::ivec2(int32 x_, int32 y_):
	x(x_), y(y_)
{
}

TexProject::ivec2&							TexProject::ivec2::operator = (const int32& source)
{
	x = source;
	y = source;
	return *this;
}
TexProject::ivec2&							TexProject::ivec2::operator = (const vec2& source)
{
	x = int32(source.x);
	y = int32(source.y);
	return *this;
}
TexProject::ivec2&							TexProject::ivec2::operator = (const uvec2& source)
{
	x = int32(source.x);
	y = int32(source.y);
	return *this;
}

TexProject::ivec2							TexProject::ivec2::operator + (const ivec2& a) const
{
	return ivec2(
					x + a.x,
					y + a.y
				);
}
TexProject::ivec2							TexProject::ivec2::operator - (const ivec2& a) const
{
	return ivec2(
					x - a.x,
					y - a.y
				);
}
TexProject::ivec2							TexProject::ivec2::operator * (const ivec2& a) const
{
	return ivec2(
					x * a.x,
					y * a.y
				);
}
TexProject::ivec2							TexProject::ivec2::operator / (const ivec2& a) const
{
	return ivec2(
					x / a.x,
					y / a.y
				);
}

TexProject::ivec2					TexProject::operator + (const ivec2& a,const int32& b)
{
	return ivec2(
					a.x + b,
					a.y + b
				);
}
TexProject::ivec2					TexProject::operator - (const ivec2& a,const int32& b)
{
	return ivec2(
					a.x - b,
					a.y - b
				);
}
TexProject::ivec2					TexProject::operator * (const ivec2& a,const int32& b)
{
	return ivec2(
					a.x * b,
					a.y * b
				);
}
TexProject::ivec2					TexProject::operator / (const ivec2& a,const int32& b)
{
	return ivec2(
					a.x / b,
					a.y / b
				);
}

TexProject::ivec2					TexProject::operator + (const ivec2& a,const uvec2& b)
{
	return ivec2(
					a.x + int32(b.x),
					a.y + int32(b.y)
				);
}
TexProject::ivec2					TexProject::operator - (const ivec2& a,const uvec2& b)
{
	return ivec2(
					a.x - int32(b.x),
					a.y - int32(b.y)
				);
}
TexProject::ivec2					TexProject::operator * (const ivec2& a,const uvec2& b)
{
	return ivec2(
					a.x * int32(b.x),
					a.y * int32(b.y)
				);
}
TexProject::ivec2					TexProject::operator / (const ivec2& a,const uvec2& b)
{
	return ivec2(
					a.x / int32(b.x),
					a.y / int32(b.y)
				);
}

TexProject::ivec2					TexProject::operator + (const uvec2& a,const ivec2& b)
{
	return ivec2(
					int32(a.x) + b.x,
					int32(a.y) + b.y
				);
}
TexProject::ivec2					TexProject::operator - (const uvec2& a,const ivec2& b)
{
	return ivec2(
					int32(a.x) - b.x,
					int32(a.y) - b.y
				);
}
TexProject::ivec2					TexProject::operator * (const uvec2& a,const ivec2& b)
{
	return ivec2(
					int32(a.x) * b.x,
					int32(a.y) * b.y
				);
}
TexProject::ivec2					TexProject::operator / (const uvec2& a,const ivec2& b)
{
	return ivec2(
					int32(a.x) / b.x,
					int32(a.y) / b.y
				);
}

TexProject::ivec2					TexProject::operator + (const int32& a,const ivec2& b)
{
	return ivec2(
					a + b.x,
					a + b.y
				);
}
TexProject::ivec2					TexProject::operator - (const int32& a,const ivec2& b)
{
	return ivec2(
					a - b.x,
					a - b.y
				);
}
TexProject::ivec2					TexProject::operator * (const int32& a,const ivec2& b)
{
	return ivec2(
					a * b.x,
					a * b.y
				);
}
TexProject::ivec2					TexProject::operator / (const int32& a,const ivec2& b)
{
	return ivec2(
					a / b.x,
					a / b.y
				);
}


// uvec2
TexProject::uvec2::uvec2()
{
}
TexProject::uvec2::uvec2(uint32 a_):
x(a_),y(a_)
{
}
TexProject::uvec2::uvec2(uint32 x_, uint32 y_):
x(x_),y(y_)
{
}

TexProject::uvec2&							TexProject::uvec2::operator = (const uint32& source)
{
	x = source;
	y = source;
	return *this;
}
TexProject::uvec2&							TexProject::uvec2::operator = (const vec2& source)
{
	x = uint32(source.x);
	y = uint32(source.y);
	return *this;
}
TexProject::uvec2&							TexProject::uvec2::operator = (const ivec2& source)
{
	x = uint32(source.x);
	y = uint32(source.y);
	return *this;
}

TexProject::uvec2							TexProject::uvec2::operator + (const uvec2& a) const
{
	return uvec2(
					x + a.x,
					y + a.y
				);
}
TexProject::ivec2							TexProject::uvec2::operator - (const uvec2& a) const
{
	return ivec2(
					x - a.x,
					y - a.y
				);
}
TexProject::ivec2							TexProject::uvec2::operator * (const uvec2& a) const
{
	return ivec2(
					x * a.x,
					y * a.y
				);
}
TexProject::ivec2							TexProject::uvec2::operator / (const uvec2& a) const
{
	return ivec2(
					x / a.x,
					y / a.y
				);
}

TexProject::uvec2							TexProject::uvec2::operator + (const uint32& a) const
{
	return uvec2(
					x + a,
					y + a
				);
}
TexProject::ivec2							TexProject::uvec2::operator - (const uint32& a) const
{
	return ivec2(
					x - a,
					y - a
				);
}
TexProject::ivec2							TexProject::uvec2::operator * (const uint32& a) const
{
	return ivec2(
					x * a,
					y * a
				);
}
TexProject::ivec2							TexProject::uvec2::operator / (const uint32& a) const
{
	return ivec2(
					x / a,
					y / a
				);
}


// vec3
TexProject::vec3::vec3()
{
}
TexProject::vec3::vec3(float32 a_):
	x(a_), y(a_), z(a_)
{
}
TexProject::vec3::vec3(float32 x_, float32 y_, float32 z_):
	x(x_), y(y_), z(z_)
{
}


// uvec3
TexProject::uvec3::uvec3()
{
}
TexProject::uvec3::uvec3(uint32 a_):
	x(a_), y(a_), z(a_)
{
}
TexProject::uvec3::uvec3(uint32 x_,uint32 y_,uint32 z_):
	x(x_),y(y_),z(z_)
{
}


// vec4
TexProject::vec4::vec4(float32 x_,float32 y_,float32 z_,float32 w_):
	x(x_), y(y_), z(z_), w(w_)
{
}


inline TexProject::float32					TexProject::degrees(float32 in)
{
	return in * _180devPIf;
}
inline TexProject::float32					TexProject::radians(float32 in)
{
	return in * _PIdev180f;
}

inline TexProject::float32					TexProject::sinDg(float32 in)
{
	return sin(radians(in));
}
inline TexProject::float32					TexProject::cosDg(float32 in)
{
	return cos(radians(in));
}
inline TexProject::float32					TexProject::tanDg(float32 in)
{
	return tan(radians(in));
}
inline TexProject::float32					TexProject::asinDg(float32 in)
{
	return degrees(asin(in));
}
inline TexProject::float32					TexProject::acosDg(float32 in)
{
	return degrees(acos(in));
}
inline TexProject::float32					TexProject::atanDg(float32 in)
{
	return degrees(atan(in));
}


inline TexProject::float32					TexProject::dot(const vec2& a, const vec2& b)
{
	return a.x*b.x + a.y*b.y;
}
inline TexProject::float32					TexProject::dot(const vec3& a, const vec3& b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}
inline TexProject::float32					TexProject::dot(const vec4& a, const vec4& b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z + a.w*b.w;
}

inline TexProject::float32					TexProject::sqr(const vec2& a)
{
	//return dot(a,a); bad!
	return a.x*a.x + a.y*a.y;
}

inline TexProject::float32					TexProject::length(const vec2& a)
{
	return sqrt(sqr(a));
}

inline TexProject::vec2						TexProject::normalize(const vec2& a)
{
	return a/length(a);
}

inline TexProject::float32					TexProject::dist(const vec2& a,const vec2& b)
{
	return length(a-b);
}

inline TexProject::vec3						TexProject::cross(const vec3& a, const vec3& b)
{
	return vec3	(
					a.y*b.z - a.z*b.y,
					a.z*b.x - a.x*b.z,
					a.x*b.y - a.y*b.x					
				);
}

inline TexProject::float32					TexProject::getAng(const vec2& a,const vec2& b)
{
	return acosDg(dot(a,b) / (length(a)*length(b)));
}













