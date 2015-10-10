/*
Модуль з математикою
*/
#pragma once
#include <TexProject/TexProject_Header.h>


#include <math.h>

#pragma region
#pragma endregion

namespace TexProject
{
	/*
	Константи, які можуть використовуватись в обчисленнях
	*/

	const float32 _0f							= 0.0f;
	const float32 _1f							= 1.0f;
	const float32 _2f							= 2.0f;
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
		float32								x,y;

		inline								vec2();
		inline								vec2(const vec2&) = default;
		explicit inline						vec2(const float32 a_);
		inline								vec2(const float32 x_,const float32 y_);
		explicit inline						vec2(const ivec2& a_);
		explicit inline						vec2(const uvec2& a_);
		inline								~vec2() = default;

		inline vec2&						operator = (const vec2&) = default;
		inline vec2&						operator = (const ivec2& a);
		inline vec2&						operator = (const uvec2& a);
		inline vec2&						operator = (const float32 a);

		inline vec2&						operator += (const vec2& a);
		inline vec2&						operator -= (const vec2& a);
		inline vec2&						operator *= (const vec2& a);
		inline vec2&						operator /= (const vec2& a);



		//
		inline vec2&						operator += (const float32 a);
		inline vec2&						operator -= (const float32 a);
		inline vec2&						operator *= (const float32 a);
		inline vec2&						operator /= (const float32 a);

		inline bool							operator==(const vec2& a) const;
		inline bool							operator!=(const vec2& a) const;

		inline bool							operator==(const float32 a) const;
		inline bool							operator!=(const float32 a) const;

		inline vec2							operator+() const;
		inline vec2							operator-() const;
		//



		inline vec2							operator + (const vec2& a) const;
		inline vec2							operator - (const vec2& a) const;
		inline vec2							operator * (const vec2& a) const;
		inline vec2							operator / (const vec2& a) const;

		friend inline vec2					operator + (const vec2& a,const float32 b);
		friend inline vec2					operator - (const vec2& a,const float32 b);
		friend inline vec2					operator * (const vec2& a,const float32 b);
		friend inline vec2					operator / (const vec2& a,const float32 b);

		friend inline vec2					operator + (const float32 a,const vec2& b);
		friend inline vec2					operator - (const float32 a,const vec2& b);
		friend inline vec2					operator * (const float32 a,const vec2& b);
		friend inline vec2					operator / (const float32 a,const vec2& b);

		inline float32						length() const;
		inline float32						sqr();
		inline void							normalize();
	};
	struct ivec2
	{
		int32								x,y;

		inline								ivec2();
		explicit inline						ivec2(const int32 a_);
		inline								ivec2(const int32 x_,const int32 y_);
		explicit inline						ivec2(const vec2&);
		explicit inline						ivec2(const uvec2&);
		inline								ivec2(const ivec2&) = default;
		inline								~ivec2() = default;

		inline ivec2&						operator = (const ivec2&) = default;
		inline ivec2&						operator = (const int32 source);
		inline ivec2&						operator = (const vec2& source);
		inline ivec2&						operator = (const uvec2& source);

		inline ivec2&						operator += (const ivec2& a);
		inline ivec2&						operator -= (const ivec2& a);
		inline ivec2&						operator *= (const ivec2& a);
		inline ivec2&						operator /= (const ivec2& a);



		//
		inline ivec2&						operator += (const int32 a);
		inline ivec2&						operator -= (const int32 a);
		inline ivec2&						operator *= (const int32 a);
		inline ivec2&						operator /= (const int32 a);

		inline bool							operator==(const ivec2& a) const;
		inline bool							operator!=(const ivec2& a) const;

		inline bool							operator==(const int32 a) const;
		inline bool							operator!=(const int32 a) const;

		inline ivec2						operator+() const;
		inline ivec2						operator-() const;
		//



		inline ivec2						operator + (const ivec2& a) const;
		inline ivec2						operator - (const ivec2& a) const;
		inline ivec2						operator * (const ivec2& a) const;
		inline ivec2						operator / (const ivec2& a) const;

		friend inline ivec2					operator + (const ivec2& a,const int32 b);
		friend inline ivec2					operator - (const ivec2& a,const int32 b);
		friend inline ivec2					operator * (const ivec2& a,const int32 b);
		friend inline ivec2					operator / (const ivec2& a,const int32 b);

		//friend inline ivec2				operator + (const ivec2& a,const uvec2& b);			 
		//friend inline ivec2				operator - (const ivec2& a,const uvec2& b);			 
		//friend inline ivec2				operator * (const ivec2& a,const uvec2& b);			 
		//friend inline ivec2				operator / (const ivec2& a,const uvec2& b);			 

		friend inline ivec2					operator + (const int32 a,const ivec2& b);
		friend inline ivec2					operator - (const int32 a,const ivec2& b);
		friend inline ivec2					operator * (const int32 a,const ivec2& b);
		friend inline ivec2					operator / (const int32 a,const ivec2& b);

		//friend inline ivec2				operator + (const uvec2& a,const ivec2& b);			 
		//friend inline ivec2				operator - (const uvec2& a,const ivec2& b);			 
		//friend inline ivec2				operator * (const uvec2& a,const ivec2& b);			 
		//friend inline ivec2				operator / (const uvec2& a,const ivec2& b);			 
	};
	struct uvec2
	{
		uint32								x,y;

		inline								uvec2();
		inline								uvec2(const uvec2&) = default;
		explicit inline						uvec2(const uint32 a_);
		inline								uvec2(const uint32 x_,const uint32 y_);
		explicit inline						uvec2(const vec2&);
		explicit inline						uvec2(const ivec2&);
		inline								~uvec2() = default;

		inline uvec2&						operator = (const uvec2& source) = default;
		inline uvec2&						operator = (const uint32 source);
		inline uvec2&						operator = (const vec2& source);
		inline uvec2&						operator = (const ivec2& source);

		inline uvec2&						operator += (const uvec2& a);
		inline uvec2&						operator -= (const uvec2& a);
		inline uvec2&						operator *= (const uvec2& a);
		inline uvec2&						operator /= (const uvec2& a);



		//
		inline uvec2&						operator += (const uint32 a);
		inline uvec2&						operator -= (const uint32 a);
		inline uvec2&						operator *= (const uint32 a);
		inline uvec2&						operator /= (const uint32 a);

		inline bool							operator==(const uvec2& a) const;
		inline bool							operator!=(const uvec2& a) const;

		inline bool							operator==(const uint32 a) const;
		inline bool							operator!=(const uint32 a) const;

		inline uvec2						operator+() const;
		inline ivec2						operator-() const;
		//



		inline uvec2						operator + (const uvec2& a) const;
		inline uvec2						operator - (const uvec2& a) const;
		inline uvec2						operator * (const uvec2& a) const;
		inline uvec2						operator / (const uvec2& a) const;

		friend inline uvec2					operator + (const uvec2& a,const uint32 b);
		friend inline uvec2					operator - (const uvec2& a,const uint32 b);
		friend inline uvec2					operator * (const uvec2& a,const uint32 b);
		friend inline uvec2					operator / (const uvec2& a,const uint32 b);

		friend inline uvec2					operator + (const uint32 a,const uvec2& b);
		friend inline uvec2					operator - (const uint32 a,const uvec2& b);
		friend inline uvec2					operator * (const uint32 a,const uvec2& b);
		friend inline uvec2					operator / (const uint32 a,const uvec2& b);

		//inline uvec2						operator + (const uint32& a) const;
		//inline ivec2						operator - (const uint32& a) const;
		//inline ivec2						operator * (const uint32& a) const;
		//inline ivec2						operator / (const uint32& a) const;

	};
	struct vec3
	{
		float32			x,y,z;

		inline								vec3();
		explicit inline						vec3(const float32 a_);
		inline								vec3(const float32 x_,const float32 y_,const float32 z_);
		explicit inline						vec3(const vec2& xy_,const float32 z_);
		explicit inline						vec3(const float32 x_,const vec2& yz_);
		inline								vec3(const vec3& a) = default;
		explicit inline						vec3(const ivec3& a);
		explicit inline						vec3(const uvec3& a);
		inline								~vec3() = default;

		inline vec3&						operator = (const vec3& a) = default;
		inline vec3&						operator = (const float32 source);
		inline vec3&						operator = (const uvec3& source);
		inline vec3&						operator = (const ivec3& source);

		inline vec3							operator + () const;
		inline vec3							operator - () const;

		inline vec3&						operator += (const vec3& a);
		inline vec3&						operator -= (const vec3& a);
		inline vec3&						operator *= (const vec3& a);
		inline vec3&						operator /= (const vec3& a);



		//
		inline vec3&						operator += (const float32 a);
		inline vec3&						operator -= (const float32 a);
		inline vec3&						operator *= (const float32 a);
		inline vec3&						operator /= (const float32 a);

		inline bool							operator==(const vec3& a) const;
		inline bool							operator!=(const vec3& a) const;

		inline bool							operator==(const float32 a) const;
		inline bool							operator!=(const float32 a) const;

		//inline vec3							operator+() const;
		//inline vec3							operator-() const;
		//



		inline vec3							operator + (const vec3& a) const;
		inline vec3							operator - (const vec3& a) const;
		inline vec3							operator * (const vec3& a) const;
		inline vec3							operator / (const vec3& a) const;

		friend inline vec3					operator + (const vec3& a,const float32 b);
		friend inline vec3					operator - (const vec3& a,const float32 b);
		friend inline vec3					operator * (const vec3& a,const float32 b);
		friend inline vec3					operator / (const vec3& a,const float32 b);

		friend inline vec3					operator + (const float32 a,const vec3& b);
		friend inline vec3					operator - (const float32 a,const vec3& b);
		friend inline vec3					operator * (const float32 a,const vec3& b);
		friend inline vec3					operator / (const float32 a,const vec3& b);

		inline vec2							xy() const;
		inline vec2							xz() const;
		inline vec2							yz() const;

		inline float32						length() const;
		inline float32						sqr();
		inline void							normalize();
	};
	struct ivec3
	{
		int32			x,y,z;

		inline								ivec3();
		explicit inline						ivec3(const int32 a_);
		inline								ivec3(const int32 x_,const int32 y_,const int32 z_);
		explicit inline						ivec3(const ivec2& xy_,const int32 z_);
		explicit inline						ivec3(const int32 x_,const ivec2& yz_);
		inline								ivec3(const ivec3& a) = default;
		explicit inline						ivec3(const vec3& a);
		explicit inline						ivec3(const uvec3& a);
		inline								~ivec3() = default;

		inline ivec3&						operator = (const ivec3& a) = default;
		inline ivec3&						operator = (const int32 source);
		inline ivec3&						operator = (const uvec3& source);
		inline ivec3&						operator = (const vec3& source);

		inline ivec3&						operator += (const ivec3& a);
		inline ivec3&						operator -= (const ivec3& a);
		inline ivec3&						operator *= (const ivec3& a);
		inline ivec3&						operator /= (const ivec3& a);



		//
		inline ivec3&						operator += (const int32 a);
		inline ivec3&						operator -= (const int32 a);
		inline ivec3&						operator *= (const int32 a);
		inline ivec3&						operator /= (const int32 a);

		inline bool							operator==(const ivec3& a) const;
		inline bool							operator!=(const ivec3& a) const;

		inline bool							operator==(const int32 a) const;
		inline bool							operator!=(const int32 a) const;

		inline ivec3						operator+() const;
		inline ivec3						operator-() const;
		//



		inline ivec3						operator + (const ivec3& a) const;
		inline ivec3						operator - (const ivec3& a) const;
		inline ivec3						operator * (const ivec3& a) const;
		inline ivec3						operator / (const ivec3& a) const;

		friend inline ivec3					operator + (const ivec3& a,const int32 b);
		friend inline ivec3					operator - (const ivec3& a,const int32 b);
		friend inline ivec3					operator * (const ivec3& a,const int32 b);
		friend inline ivec3					operator / (const ivec3& a,const int32 b);

		friend inline ivec3					operator + (const int32 a,const ivec3& b);
		friend inline ivec3					operator - (const int32 a,const ivec3& b);
		friend inline ivec3					operator * (const int32 a,const ivec3& b);
		friend inline ivec3					operator / (const int32 a,const ivec3& b);

		inline ivec2						xy() const;
		inline ivec2						xz() const;
		inline ivec2						yz() const;
	};
	struct uvec3
	{
		uint32			x,y,z;

		inline								uvec3();
		inline explicit						uvec3(const uint32 a_);
		inline								uvec3(const uint32 x_,const uint32 y_,const uint32 z_);
		explicit inline						uvec3(const uvec2& xy_,const uint32 z_);
		explicit inline						uvec3(const uint32 x_,const uvec2& yz_);
		inline								uvec3(const uvec3&) = default;
		explicit inline						uvec3(const vec3& a);
		explicit inline						uvec3(const ivec3& a);
		inline								~uvec3() = default;

		inline uvec3&						operator = (const uvec3& a) = default;
		inline uvec3&						operator = (const uint32 source);
		inline uvec3&						operator = (const ivec3& source);
		inline uvec3&						operator = (const vec3& source);

		inline uvec3&						operator += (const uvec3& a);
		inline uvec3&						operator -= (const uvec3& a);
		inline uvec3&						operator *= (const uvec3& a);
		inline uvec3&						operator /= (const uvec3& a);



		//
		inline uvec3&						operator += (const uint32 a);
		inline uvec3&						operator -= (const uint32 a);
		inline uvec3&						operator *= (const uint32 a);
		inline uvec3&						operator /= (const uint32 a);

		inline bool							operator==(const uvec3& a) const;
		inline bool							operator!=(const uvec3& a) const;

		inline bool							operator==(const uint32 a) const;
		inline bool							operator!=(const uint32 a) const;

		inline uvec3						operator+() const;
		inline ivec3						operator-() const;
		//



		inline uvec3						operator + (const uvec3& a) const;
		inline uvec3						operator - (const uvec3& a) const;
		inline uvec3						operator * (const uvec3& a) const;
		inline uvec3						operator / (const uvec3& a) const;

		friend inline uvec3					operator + (const uvec3& a,const uint32 b);
		friend inline uvec3					operator - (const uvec3& a,const uint32 b);
		friend inline uvec3					operator * (const uvec3& a,const uint32 b);
		friend inline uvec3					operator / (const uvec3& a,const uint32 b);

		friend inline uvec3					operator + (const uint32 a,const uvec3& b);
		friend inline uvec3					operator - (const uint32 a,const uvec3& b);
		friend inline uvec3					operator * (const uint32 a,const uvec3& b);
		friend inline uvec3					operator / (const uint32 a,const uvec3& b);

		inline uvec2						xy() const;
		inline uvec2						xz() const;
		inline uvec2						yz() const;
	};
	struct vec4
	{
		float32			x,y,z,w;

		inline								vec4() = default;
		inline								vec4(const float32& a_);
		inline								vec4(const vec3& xyz_,const float32 w_);
		inline								vec4(const float32 x_,const vec3& yzw_);
		inline								vec4(const vec2& xy_,const vec2& zw_);
		inline								vec4(const vec2& xy_,const float32 z_,const float32 w_);
		inline								vec4(const float32 x_,const vec2& yz_,const float32 w_);
		inline								vec4(const float32 x_,const float32 y_,const vec2& zw_);
		inline								vec4(const float32 x_,const float32 y_,const float32 z_,const float32 w_);
		inline								vec4(const vec4& a) = default;
		inline								vec4(const ivec4& a);
		inline								vec4(const uvec4& a);
		inline								~vec4() = default;

		inline vec4&						operator = (const vec4& a) = default;
		inline vec4&						operator = (const float32 source);
		inline vec4&						operator = (const ivec4& source);
		inline vec4&						operator = (const uvec4& source);

		inline vec4&						operator += (const vec4& a);
		inline vec4&						operator -= (const vec4& a);
		inline vec4&						operator *= (const vec4& a);
		inline vec4&						operator /= (const vec4& a);



		//
		inline vec4&						operator += (const float32 a);
		inline vec4&						operator -= (const float32 a);
		inline vec4&						operator *= (const float32 a);
		inline vec4&						operator /= (const float32 a);

		inline bool							operator==(const vec4& a) const;
		inline bool							operator!=(const vec4& a) const;

		inline bool							operator==(const float32 a) const;
		inline bool							operator!=(const float32 a) const;

		inline vec4							operator+() const;
		inline vec4							operator-() const;
		//



		inline vec4							operator + (const vec4& a) const;
		inline vec4							operator - (const vec4& a) const;
		inline vec4							operator * (const vec4& a) const;
		inline vec4							operator / (const vec4& a) const;

		friend inline vec4					operator + (const vec4& a,const float32 b);
		friend inline vec4					operator - (const vec4& a,const float32 b);
		friend inline vec4					operator * (const vec4& a,const float32 b);
		friend inline vec4					operator / (const vec4& a,const float32 b);

		friend inline vec4					operator + (const float32 a,const vec4& b);
		friend inline vec4					operator - (const float32 a,const vec4& b);
		friend inline vec4					operator * (const float32 a,const vec4& b);
		friend inline vec4					operator / (const float32 a,const vec4& b);

		inline vec3							xyz() const;
		inline vec3							xyw() const;
		inline vec3							xzw() const;
		inline vec3							yzw() const;

		inline float32						length() const;
		inline float32						sqr();
		inline void							normalize();
	};
	struct ivec4
	{
		int32			x,y,z,w;

		inline								ivec4() = default;
		inline								ivec4(const ivec3& xyz_,const int32 w_);
		inline								ivec4(const int32 x_,const ivec3& yzw_);
		inline								ivec4(const ivec2& xy_,const ivec2& zw_);
		inline								ivec4(const ivec2& xy_,const int32 z_,const int32 w_);
		inline								ivec4(const int32 x_,const ivec2& yz_,const int32 w_);
		inline								ivec4(const int32 x_,const int32 y_,const ivec2& zw_);
		inline								ivec4(const int32 x_,const int32 y_,const int32 z_,const int32 w_);
		inline								ivec4(const ivec4& a) = default;
		inline								ivec4(const vec4& a);
		inline								ivec4(const uvec4& a);
		inline								~ivec4() = default;

		inline ivec4&						operator = (const ivec4& a) = default;
		inline ivec4&						operator = (const int32 source);
		inline ivec4&						operator = (const vec4& source);
		inline ivec4&						operator = (const uvec4& source);

		inline ivec4&						operator += (const ivec4& a);
		inline ivec4&						operator -= (const ivec4& a);
		inline ivec4&						operator *= (const ivec4& a);
		inline ivec4&						operator /= (const ivec4& a);



		//
		inline ivec4&						operator += (const int32 a);
		inline ivec4&						operator -= (const int32 a);
		inline ivec4&						operator *= (const int32 a);
		inline ivec4&						operator /= (const int32 a);

		inline bool							operator==(const ivec4& a) const;
		inline bool							operator!=(const ivec4& a) const;

		inline bool							operator==(const int32 a) const;
		inline bool							operator!=(const int32 a) const;

		inline ivec4						operator+() const;
		inline ivec4						operator-() const;
		//



		inline ivec4						operator + (const ivec4& a) const;
		inline ivec4						operator - (const ivec4& a) const;
		inline ivec4						operator * (const ivec4& a) const;
		inline ivec4						operator / (const ivec4& a) const;

		friend inline ivec4					operator + (const ivec4& a,const int32 b);
		friend inline ivec4					operator - (const ivec4& a,const int32 b);
		friend inline ivec4					operator * (const ivec4& a,const int32 b);
		friend inline ivec4					operator / (const ivec4& a,const int32 b);

		friend inline ivec4					operator + (const int32 a,const ivec4& b);
		friend inline ivec4					operator - (const int32 a,const ivec4& b);
		friend inline ivec4					operator * (const int32 a,const ivec4& b);
		friend inline ivec4					operator / (const int32 a,const ivec4& b);

		inline ivec3						xyz() const;
		inline ivec3						xyw() const;
		inline ivec3						xzw() const;
		inline ivec3						yzw() const;
	};
	struct uvec4
	{
		uint32			x,y,z,w;

		inline								uvec4() = default;
		inline								uvec4(const uvec3& xyz_,const uint32 w_);
		inline								uvec4(const uint32 x_,const uvec3& yzw_);
		inline								uvec4(const uvec2& xy_,const uvec2& zw_);
		inline								uvec4(const uvec2& xy_,const uint32 z_,const uint32 w_);
		inline								uvec4(const uint32 x_,const uvec2& yz_,const uint32 w_);
		inline								uvec4(const uint32 x_,const uint32 y_,const uvec2& zw_);
		inline								uvec4(const uint32 x_,const uint32 y_,const uint32 z_,const uint32 w_);
		inline								uvec4(const uvec4& a) = default;
		inline								uvec4(const vec4& a);
		inline								uvec4(const ivec4& a);
		inline								~uvec4() = default;

		inline uvec4&						operator = (const uvec4& a) = default;
		inline uvec4&						operator = (const uint32 source);
		inline uvec4&						operator = (const vec4& source);
		inline uvec4&						operator = (const ivec4& source);

		inline uvec4&						operator += (const uvec4& a);
		inline uvec4&						operator -= (const uvec4& a);
		inline uvec4&						operator *= (const uvec4& a);
		inline uvec4&						operator /= (const uvec4& a);



		//
		inline uvec4&						operator += (const uint32 a);
		inline uvec4&						operator -= (const uint32 a);
		inline uvec4&						operator *= (const uint32 a);
		inline uvec4&						operator /= (const uint32 a);

		inline bool							operator==(const uvec4& a) const;
		inline bool							operator!=(const uvec4& a) const;

		inline bool							operator==(const uint32 a) const;
		inline bool							operator!=(const uint32 a) const;

		inline uvec4						operator+() const;
		inline ivec4						operator-() const;
		//



		inline uvec4						operator + (const uvec4& a) const;
		inline uvec4						operator - (const uvec4& a) const;
		inline uvec4						operator * (const uvec4& a) const;
		inline uvec4						operator / (const uvec4& a) const;

		friend inline uvec4					operator + (const uvec4& a,const uint32 b);
		friend inline uvec4					operator - (const uvec4& a,const uint32 b);
		friend inline uvec4					operator * (const uvec4& a,const uint32 b);
		friend inline uvec4					operator / (const uvec4& a,const uint32 b);

		friend inline uvec4					operator + (const uint32 a,const uvec4& b);
		friend inline uvec4					operator - (const uint32 a,const uvec4& b);
		friend inline uvec4					operator * (const uint32 a,const uvec4& b);
		friend inline uvec4					operator / (const uint32 a,const uvec4& b);

		inline uvec3						xyz() const;
		inline uvec3						xyw() const;
		inline uvec3						xzw() const;
		inline uvec3						yzw() const;
	};
	struct mat2
	{
		float32			val[4];
	};
	struct mat3
	{
		static inline mat3					null();
		static inline mat3					one();
		static inline mat3					rotateX(float32 ang);
		static inline mat3					rotateY(float32 ang);
		static inline mat3					rotateZ(float32 ang);
		static inline mat3					rotateZXY(vec3 ang);
		static inline mat3					rotateYXZ(vec3 ang);

		float32								val[9];

		inline								mat3() = default;
		inline								mat3(const mat3& source);
		inline								~mat3() = default;

		inline mat3&						operator = (const mat3& source);

		inline friend mat3					operator * (const mat3& a,const mat3& b);

		inline friend vec3					operator * (const mat3& m,const vec3& v);

		inline void							makeNull();
		inline void							makeOne();
		inline void							makeRotateZXY(vec3 angle);
		inline void							makeRotateYXZ(vec3 angle);
	};
	struct mat4
	{
		static inline mat4					null();
		static inline mat4					one();
		static inline mat4					move(vec3 pos);
		static inline mat4					scale(vec3 scale);
		static inline mat4					rotateX(float32 ang);
		static inline mat4					rotateY(float32 ang);
		static inline mat4					rotateZ(float32 ang);
		static inline mat4					rotateZXY(vec3 ang);
		static inline mat4					rotateYXZ(vec3 ang);
		static inline mat4					perspective(float32 FOV,float32 aspect,float32 zNear,float32 zFar);
		static inline mat4					perspectiveInv(float32 FOV,float32 aspect,float32 zNear,float32 zFar);
		static inline mat4					orthogonal(float32 left,float32 right,float32 bottom,float32 top,float32 back,float32 front);

		float32								val[16];

		inline								mat4() = default;
		inline explicit						mat4(const mat3& source);
		inline								mat4(const mat4& source);
		inline								~mat4() = default;

		inline mat4&						operator = (const mat4& source);

		inline friend mat4					operator * (const mat4& a,const mat4& b);

		inline friend vec3					operator * (const mat4& m,const vec3& v);

		inline void							makeNull();
		inline void							makeOne();
		inline void							makeMove(vec3 move);
		inline void							makeScale(vec3 scale);
		inline void							makeRotateZXY(vec3 angle);
		inline void							makeRotateYXZ(vec3 angle);
		inline void							makeProjectionPerspective(float32 FOV,float32 aspect,float32 zNear,float32 zFar);
		inline void							makeProjectionPerspectiveInverse(float32 FOV,float32 aspect,float32 zNear,float32 zFar);
		inline void							makeProjectionOrthogonal(float32 left,float32 right,float32 bottom,float32 top,float32 back,float32 front);
		inline void							makeProjectionOrthogonalInverse(float32 left,float32 right,float32 bottom,float32 top,float32 back,float32 front);
	};
	struct quat
	{
		float32			x,y,z,w;
	};

	inline float32							sign(float32 val)
	{
		return val > 0 ? 1.0f : -1.0f;
	}

	/*Випадкове число в межах [0,1]*/
	inline float32							rnd();
	/*Випадкове число в межах [0,highLimit]*/
	inline float32							rnd(float32 highLimit);
	/*Випадкове число в межах [0,limit]*/
	inline float32							rnd(float32 lowLimit,float32 highLimit);

	/*Повертає таке val, що minVal < val < maxVal*/
	inline int32							clamp(int32 val,int32 minVal,int32 maxVal);
	inline float32							clamp(float32 val,float32 minVal,float32 maxVal);
	inline vec2								clamp(const vec2& val,const vec2& minVal,const vec2& maxVal);
	inline vec3								clamp(const vec3& val,const vec3& minVal,const vec3& maxVal);
	inline vec4								clamp(const vec4& val,const vec4& minVal,const vec4& maxVal);

	inline float32							wrap(float32 val,float32 minVal,float32 maxVal);

	/*Конвертує радіани в градуси*/
	inline float32							degrees(const float32 rads);
	/*Конвертує градуси в радіани*/
	inline float32							radians(const float32 degs);

	/*Синус від значення в градусах*/
	inline float32							sinDg(const float32 in);
	/*Косинус від значення в градусах*/
	inline float32							cosDg(const float32 in);
	/*Тангенс від значення в градусах*/
	inline float32							tanDg(const float32 in);
	/*Асинус в градусах*/
	inline float32							asinDg(const float32 in);
	/*Акосинус в градусах*/
	inline float32							acosDg(const float32 in);
	/*Атангенс в градусах*/
	inline float32							atanDg(const float32 in);


	/*Скалярний добуток vec2*/
	inline float32							dot(const vec2& a,const vec2& b);
	/*Скалярний добуток vec3*/
	inline float32							dot(const vec3& a,const vec3& b);
	/*Скалярний добуток vec4*/
	inline float32							dot(const vec4& a,const vec4& b);

	/*Скалярний квадрат vec2*/
	inline float32							sqr(const vec2& a);
	/*Скалярний квадрат vec3*/
	inline float32							sqr(const vec3& a);
	/*Скалярний квадрат vec4*/
	inline float32							sqr(const vec4& a);

	/*Довжина vec2*/
	inline float32							length(const vec2& a);
	/*Довжина vec3*/
	inline float32							length(const vec3& a);
	/*Довжина vec4*/
	inline float32							length(const vec4& a);

	/*Нормалізований vec2*/
	inline vec2								normalize(const vec2& a);
	/*Нормалізований vec3*/
	inline vec3								normalize(const vec3& a);
	/*Нормалізований vec4*/
	inline vec4								normalize(const vec4& a);

	/*Відстань між двома vec2*/
	inline float32							dist(const vec2& a,const vec2& b);
	/*Відстань між двома vec3*/
	inline float32							dist(const vec3& a,const vec3& b);
	/*Відстань між двома vec4*/
	inline float32							dist(const vec4& a,const vec4& b);

	/*Векторний добуток vec3*/
	inline vec3								cross(const vec3& a,const vec3& b);

	inline float32							getAng(const vec2& a,const vec2& b);
	inline float32							getAng(const vec2& a);
	inline vec2								getAng(const vec3& a);
	inline vec3								getAng(const mat3& mat);
	inline vec3								getAng(const mat4& mat);

	/*Криві Безьє*/
	/*Функція Безьє порядку 2*/
	inline float32							bezier(float32 t1,float32 t2,float32 t);
	inline vec2								bezier(const vec2& t1,const vec2& t2,float32 t);
	inline vec3								bezier(const vec3& t1,const vec3& t2,float32 t);
	inline vec4								bezier(const vec4& t1,const vec4& t2,float32 t);
	inline vec4								bezier(const vec4& t1,const vec4& t2,const vec4& t);
	/*Функція Безьє порядку 3*/
	inline float32							bezier(float32 t1,float32 t2,float32 t3,float32 t);
	inline vec2								bezier(const vec2& t1,const vec2& t2,const vec2& t3,float32 t);
	inline vec3								bezier(const vec3& t1,const vec3& t2,const vec3& t3,float32 t);
	inline vec4								bezier(const vec4& t1,const vec4& t2,const vec4& t3,float32 t);
	/*Функція Безьє порядку 4*/
	inline float32							bezier(float32 t1,float32 t2,float32 t3,float32 t4,float32 t);
	inline vec2								bezier(const vec2& t1,const vec2& t2,const vec2& t3,const vec2& t4,float32 t);
	inline vec3								bezier(const vec3& t1,const vec3& t2,const vec3& t3,const vec3& t4,float32 t);
	inline vec4								bezier(const vec4& t1,const vec4& t2,const vec4& t3,const vec4& t4,float32 t);
	/*Виводить криву Безьє з точністю accuracy за допомогою func*/
	template <class _Pr>
	void									bezier(const vec2& t1,const vec2& t2,_Pr pred,const uint32 accuracy = 32);
	template <class _Pr>
	void									bezier(const vec2& t1,const vec2& t2,const vec2& t3,_Pr pred,const uint32 accuracy = 32);
	template <class _Pr>
	void									bezier(const vec2& t1,const vec2& t2,const vec2& t3,const vec2& t4,_Pr pred,const uint32 accuracy = 32);

}


#pragma region vec2
inline										TexProject::vec2::vec2()
{
}
inline										TexProject::vec2::vec2(const float32 a_):
x(a_),
y(a_)
{
}
inline										TexProject::vec2::vec2(const float32 x_,const float32 y_) :
x(x_),
y(y_)
{
}
inline										TexProject::vec2::vec2(const ivec2& a_) :
x(float32(a_.x)),
y(float32(a_.y))
{
}
inline										TexProject::vec2::vec2(const uvec2& a_) :
x(float32(a_.x)),
y(float32(a_.y))
{
}

inline										TexProject::vec2& TexProject::vec2::operator = (const ivec2& a)
{
	x = float32(a.x);
	y = float32(a.y);
	return *this;
}

inline										TexProject::vec2& TexProject::vec2::operator = (const uvec2& a)
{
	x = float32(a.x);
	y = float32(a.y);
	return *this;
}

inline TexProject::vec2&					TexProject::vec2::operator = (const float32 a)
{
	x = a;
	y = a;
	return *this;
}

inline TexProject::vec2&					TexProject::vec2::operator += (const vec2& a)
{
	x += a.x;
	y += a.y;
	return *this;
}
inline TexProject::vec2&					TexProject::vec2::operator -= (const vec2& a)
{
	x -= a.x;
	y -= a.y;
	return *this;
}
inline TexProject::vec2&					TexProject::vec2::operator *= (const vec2& a)
{
	x *= a.x;
	y *= a.y;
	return *this;
}
inline TexProject::vec2&					TexProject::vec2::operator /= (const vec2& a)
{
	x /= a.x;
	y /= a.y;
	return *this;
}

//
inline TexProject::vec2&					TexProject::vec2::operator += (const float32 a)
{
	x += a;
	y += a;
	return *this;
}
inline TexProject::vec2&					TexProject::vec2::operator -= (const float32 a)
{
	x -= a;
	y -= a;
	return *this;
}
inline TexProject::vec2&					TexProject::vec2::operator *= (const float32 a)
{
	x *= a;
	y *= a;
	return *this;
}
inline TexProject::vec2&					TexProject::vec2::operator /= (const float32 a)
{
	x /= a;
	y /= a;
	return *this;
}
inline bool									TexProject::vec2::operator == (const vec2& a) const
{
	return this->x == a.x && this->y == a.y;
}
inline bool									TexProject::vec2::operator != (const vec2& a) const
{
	return this->x != a.x && this->y != a.y;
}

inline bool									TexProject::vec2::operator == (const float32 a) const
{
	return this->x == a && this->y == a;
}
inline bool									TexProject::vec2::operator != (const float32 a) const
{
	return this->x != a && this->y != a;
}

inline TexProject::vec2						TexProject::vec2::operator + () const
{
	return vec2(+this->x, +this->y);
}
inline TexProject::vec2						TexProject::vec2::operator - () const
{
	return vec2(-this->x, -this->y);
}
//

inline TexProject::vec2						TexProject::vec2::operator + (const vec2& a) const
{
	return vec2(
		x + a.x,
		y + a.y
		);
}
inline TexProject::vec2						TexProject::vec2::operator - (const vec2& a) const
{
	return vec2(
		x - a.x,
		y - a.y
		);
}
inline TexProject::vec2						TexProject::vec2::operator * (const vec2& a) const
{
	return vec2(
		x * a.x,
		y * a.y
		);
}
inline TexProject::vec2						TexProject::vec2::operator / (const vec2& a) const
{
	return vec2(
		x / a.x,
		y / a.y
		);
}

inline TexProject::vec2						TexProject::operator + (const vec2& a,const float32 b)
{
	return vec2(
		a.x + b,
		a.y + b
		);
}
inline TexProject::vec2						TexProject::operator - (const vec2& a,const float32 b)
{
	return vec2(
		a.x - b,
		a.y - b
		);
}
inline TexProject::vec2						TexProject::operator * (const vec2& a,const float32 b)
{
	return vec2(
		a.x * b,
		a.y * b
		);
}
inline TexProject::vec2						TexProject::operator / (const vec2& a,const float32 b)
{
	static float32 t;
	t = 1.0f/b;
	return vec2(
		a.x * t,
		a.y * t
		);
}

inline TexProject::vec2						TexProject::operator + (const float32 a,const vec2& b)
{
	return vec2(
		a + b.x,
		a + b.y
		);
}
inline TexProject::vec2						TexProject::operator - (const float32 a,const vec2& b)
{
	return vec2(
		a - b.x,
		a - b.y
		);
}
inline TexProject::vec2						TexProject::operator * (const float32 a,const vec2& b)
{
	return vec2(
		a * b.x,
		a * b.y
		);
}
inline TexProject::vec2						TexProject::operator / (const float32 a,const vec2& b)
{
	return vec2(
		a / b.x,
		a / b.y
		);
}

inline TexProject::float32					TexProject::vec2::length() const
{
	return sqrt(x * x + y * y);
}

inline TexProject::float32					TexProject::vec2::sqr()
{
	return x * x + y * y;
}

inline void									TexProject::vec2::normalize()
{
	float32 len = sqrt(x * x + y * y);
	x /= len;
	y /= len;
}
#pragma endregion
#pragma region ivec2
inline										TexProject::ivec2::ivec2()
{
}
inline										TexProject::ivec2::ivec2(const int32 a_):
x(a_),
y(a_)
{
}
inline										TexProject::ivec2::ivec2(const int32 x_,const int32 y_) :
x(x_),
y(y_)
{
}

inline										TexProject::ivec2::ivec2(const vec2& a):
x(int32(a.x)),
y(int32(a.y))
{
}

inline										TexProject::ivec2::ivec2(const uvec2& a):
x(int32(a.x)),
y(int32(a.y))
{
}


inline TexProject::ivec2&					TexProject::ivec2::operator = (const int32 source)
{
	x = source;
	y = source;
	return *this;
}
inline TexProject::ivec2&					TexProject::ivec2::operator = (const vec2& source)
{
	x = int32(source.x);
	y = int32(source.y);
	return *this;
}
inline TexProject::ivec2&					TexProject::ivec2::operator = (const uvec2& source)
{
	x = int32(source.x);
	y = int32(source.y);
	return *this;
}

inline TexProject::ivec2&					TexProject::ivec2::operator += (const ivec2& a)
{
	x += a.x;
	y += a.y;
	return *this;
}

inline TexProject::ivec2&					TexProject::ivec2::operator -= (const ivec2& a)
{
	x -= a.x;
	y -= a.y;
	return *this;
}
inline TexProject::ivec2&					TexProject::ivec2::operator *= (const ivec2& a)
{
	x *= a.x;
	y *= a.y;
	return *this;
}
inline TexProject::ivec2&					TexProject::ivec2::operator /= (const ivec2& a)
{
	x /= a.x;
	y /= a.y;
	return *this;
}

//
inline TexProject::ivec2&					TexProject::ivec2::operator += (const int32 a)
{
	x += a;
	y += a;
	return *this;
}
inline TexProject::ivec2&					TexProject::ivec2::operator -= (const int32 a)
{
	x -= a;
	y -= a;
	return *this;
}
inline TexProject::ivec2&					TexProject::ivec2::operator *= (const int32 a)
{
	x *= a;
	y *= a;
	return *this;
}
inline TexProject::ivec2&					TexProject::ivec2::operator /= (const int32 a)
{
	x /= a;
	y /= a;
	return *this;
}

inline bool									TexProject::ivec2::operator==(const ivec2& a) const
{
	return this->x == a.x && this->y == a.y;
}
inline bool									TexProject::ivec2::operator!=(const ivec2& a) const
{
	return this->x != a.x && this->y != a.y;
}

inline bool									TexProject::ivec2::operator==(const int32 a) const
{
	return this->x == a && this->y == a;
}
inline bool									TexProject::ivec2::operator!=(const int32 a) const
{
	return this->x != a && this->y != a;
}

inline TexProject::ivec2					TexProject::ivec2::operator+() const
{
	return ivec2(+this->x, +this->y);
}
inline TexProject::ivec2					TexProject::ivec2::operator-() const
{
	return ivec2(-this->x, -this->y);
}
//

inline TexProject::ivec2					TexProject::ivec2::operator + (const ivec2& a) const
{
	return ivec2(
		x + a.x,
		y + a.y
		);
}
inline TexProject::ivec2					TexProject::ivec2::operator - (const ivec2& a) const
{
	return ivec2(
		x - a.x,
		y - a.y
		);
}
inline TexProject::ivec2					TexProject::ivec2::operator * (const ivec2& a) const
{
	return ivec2(
		x * a.x,
		y * a.y
		);
}
inline TexProject::ivec2					TexProject::ivec2::operator / (const ivec2& a) const
{
	return ivec2(
		x / a.x,
		y / a.y
		);
}

inline TexProject::ivec2					TexProject::operator + (const ivec2& a,const int32 b)
{
	return ivec2(
		a.x + b,
		a.y + b
		);
}
inline TexProject::ivec2					TexProject::operator - (const ivec2& a,const int32 b)
{
	return ivec2(
		a.x - b,
		a.y - b
		);
}
inline TexProject::ivec2					TexProject::operator * (const ivec2& a,const int32 b)
{
	return ivec2(
		a.x * b,
		a.y * b
		);
}
inline TexProject::ivec2					TexProject::operator / (const ivec2& a,const int32 b)
{
	return ivec2(
		a.x / b,
		a.y / b
		);
}

inline TexProject::ivec2					TexProject::operator + (const int32 a,const ivec2& b)
{
	return ivec2(
		a + b.x,
		a + b.y
		);
}
inline TexProject::ivec2					TexProject::operator - (const int32 a,const ivec2& b)
{
	return ivec2(
		a - b.x,
		a - b.y
		);
}
inline TexProject::ivec2					TexProject::operator * (const int32 a,const ivec2& b)
{
	return ivec2(
		a * b.x,
		a * b.y
		);
}
inline TexProject::ivec2					TexProject::operator / (const int32 a,const ivec2& b)
{
	return ivec2(
		a / b.x,
		a / b.y
		);
}
#pragma endregion
#pragma region uvec2
inline TexProject::uvec2::uvec2()
{
}
inline										TexProject::uvec2::uvec2(const uint32 a_):
x(a_),
y(a_)
{
}
inline										TexProject::uvec2::uvec2(const uint32 x_,const uint32 y_) :
x(x_),
y(y_)
{
}
inline										TexProject::uvec2::uvec2(const vec2& a) :
x(uint32(a.x)),
y(uint32(a.y))
{
}
inline										TexProject::uvec2::uvec2(const ivec2& a) :
x(uint32(a.x)),
y(uint32(a.y))
{
}
inline TexProject::uvec2&					TexProject::uvec2::operator = (const uint32 source)
{
	x = source;
	y = source;
	return *this;
}
inline TexProject::uvec2&					TexProject::uvec2::operator = (const vec2& source)
{
	x = uint32(source.x);
	y = uint32(source.y);
	return *this;
}
inline TexProject::uvec2&					TexProject::uvec2::operator = (const ivec2& source)
{
	x = uint32(source.x);
	y = uint32(source.y);
	return *this;
}
inline TexProject::uvec2&					TexProject::uvec2::operator += (const uvec2& a)
{
	x += a.x;
	y += a.y;
	return *this;
}
inline TexProject::uvec2&					TexProject::uvec2::operator -= (const uvec2& a)
{
	x -= a.x;
	y -= a.y;
	return *this;
}
inline TexProject::uvec2&					TexProject::uvec2::operator *= (const uvec2& a)
{
	x *= a.x;
	y *= a.y;
	return *this;
}
inline TexProject::uvec2&					TexProject::uvec2::operator /= (const uvec2& a)
{
	x /= a.x;
	y /= a.y;
	return *this;
}

//
inline TexProject::uvec2&					TexProject::uvec2::operator += (const uint32 a)
{
	x += a;
	y += a;
	return *this;
}
inline TexProject::uvec2&					TexProject::uvec2::operator -= (const uint32 a)
{
	x -= a;
	y -= a;
	return *this;
}
inline TexProject::uvec2&					TexProject::uvec2::operator *= (const uint32 a)
{
	x *= a;
	y *= a;
	return *this;
}
inline TexProject::uvec2&					TexProject::uvec2::operator /= (const uint32 a)
{
	x /= a;
	y /= a;
	return *this;
}

inline bool									TexProject::uvec2::operator == (const uvec2& a) const
{
	return this->x == a.x && this->y == a.y;
}
inline bool									TexProject::uvec2::operator != (const uvec2& a) const
{
	return this->x != a.x && this->y != a.y;
}

inline bool									TexProject::uvec2::operator == (const uint32 a) const
{
	return this->x == a && this->y == a;
}
inline bool									TexProject::uvec2::operator != (const uint32 a) const
{
	return this->x != a && this->y != a;
}

inline TexProject::uvec2					TexProject::uvec2::operator + () const
{
	return uvec2(+this->x, +this->y);
}
inline TexProject::ivec2					TexProject::uvec2::operator - () const
{
	return ivec2(-int(this->x), -int(this->y));
}
//

inline TexProject::uvec2					TexProject::uvec2::operator + (const uvec2& a) const
{
	return uvec2(
		x + a.x,
		y + a.y
		);
}
inline TexProject::uvec2					TexProject::uvec2::operator - (const uvec2& a) const
{
	return uvec2(
		x - a.x,
		y - a.y
		);
}
inline TexProject::uvec2					TexProject::uvec2::operator * (const uvec2& a) const
{
	return uvec2(
		x * a.x,
		y * a.y
		);
}
inline TexProject::uvec2					TexProject::uvec2::operator / (const uvec2& a) const
{
	return uvec2(
		x / a.x,
		y / a.y
		);
}
inline TexProject::uvec2					TexProject::operator + (const uvec2& a,const uint32 b)
{
	return uvec2(
		a.x + b,
		a.y + b
		);
}
inline TexProject::uvec2					TexProject::operator - (const uvec2& a,const uint32 b)
{
	return uvec2(
		a.x - b,
		a.y - b
		);
}
inline TexProject::uvec2					TexProject::operator * (const uvec2& a,const uint32 b)
{
	return uvec2(
		a.x * b,
		a.y * b
		);
}
inline TexProject::uvec2					TexProject::operator / (const uvec2& a,const uint32 b)
{
	return uvec2(
		a.x / b,
		a.y / b
		);
}
inline TexProject::uvec2					TexProject::operator + (const uint32 a,const uvec2& b)
{
	return uvec2(
		a + b.x,
		a + b.y
		);
}
inline TexProject::uvec2					TexProject::operator - (const uint32 a,const uvec2& b)
{
	return uvec2(
		a - b.x,
		a - b.y
		);
}
inline TexProject::uvec2					TexProject::operator * (const uint32 a,const uvec2& b)
{
	return uvec2(
		a * b.x,
		a * b.y
		);
}
inline TexProject::uvec2					TexProject::operator / (const uint32 a,const uvec2& b)
{
	return uvec2(
		a / b.x,
		a / b.y
		);
}
#pragma endregion
#pragma region vec3
inline										TexProject::vec3::vec3()
{
}
inline										TexProject::vec3::vec3(const float32 a_):
x(a_),
y(a_),
z(a_)
{
}
inline										TexProject::vec3::vec3(const float32 x_,const float32 y_,const float32 z_):
x(x_),
y(y_),
z(z_)
{
}

inline										TexProject::vec3::vec3(const vec2& xy_,const float32 z_):
x(xy_.x),
y(xy_.y),
z(z_)
{
}

inline										TexProject::vec3::vec3(const float32 x_,const vec2& yz_):
x(x_),
y(yz_.x),
z(yz_.y)
{
}
inline										TexProject::vec3::vec3(const ivec3& a):
x(float32(a.x)),
y(float32(a.y)),
z(float32(a.z))
{
}
inline										TexProject::vec3::vec3(const uvec3& a):
x(float32(a.x)),
y(float32(a.y)),
z(float32(a.z))
{
}

inline TexProject::vec3&					TexProject::vec3::operator = (const float32 source)
{
	x = source;
	y = source;
	z = source;
	return *this;
}
inline TexProject::vec3&					TexProject::vec3::operator = (const uvec3& source)
{
	x = float32(source.x);
	y = float32(source.y);
	z = float32(source.z);
	return *this;
}
inline TexProject::vec3&					TexProject::vec3::operator = (const ivec3& source)
{
	x = float32(source.x);
	y = float32(source.y);
	z = float32(source.z);
	return *this;
}

inline TexProject::vec3						TexProject::vec3::operator + () const
{
	return vec3(+x,+y,+z);
}
inline TexProject::vec3						TexProject::vec3::operator - () const
{
	return vec3(-x,-y,-z);
}

inline TexProject::vec3&					TexProject::vec3::operator += (const vec3& a)
{
	x += a.x;
	y += a.y;
	z += a.z;
	return *this;
}
inline TexProject::vec3&					TexProject::vec3::operator -= (const vec3& a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	return *this;
}
inline TexProject::vec3&					TexProject::vec3::operator *= (const vec3& a)
{
	x *= a.x;
	y *= a.y;
	z *= a.z;
	return *this;
}
inline TexProject::vec3&					TexProject::vec3::operator /= (const vec3& a)
{
	x /= a.x;
	y /= a.y;
	z /= a.z;
	return *this;
}

//
inline TexProject::vec3&					TexProject::vec3::operator += (const float32 a)
{
	x += a;
	y += a;
	z += a;
	return *this;
}
inline TexProject::vec3&					TexProject::vec3::operator -= (const float32 a)
{
	x -= a;
	y -= a;
	z -= a;
	return *this;
}
inline TexProject::vec3&					TexProject::vec3::operator *= (const float32 a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}
inline TexProject::vec3&					TexProject::vec3::operator /= (const float32 a)
{
	x /= a;
	y /= a;
	z /= a;
	return *this;
}

inline bool									TexProject::vec3::operator==(const vec3& a) const
{
	return this->x == a.x && this->y == a.y && this->z == a.z;
}
inline bool									TexProject::vec3::operator!=(const vec3& a) const
{
	return this->x != a.x && this->y != a.y && this->z != a.z;
}

inline bool									TexProject::vec3::operator==(const float32 a) const
{
	return this->x == a && this->y == a && this->z == a;
}
inline bool									TexProject::vec3::operator!=(const float32 a) const
{
	return this->x != a && this->y != a && this->z != a;
}

//inline TexProject::vec3						TexProject::vec3::operator+() const
//{
//	return vec3(+this->x, +this->y, +this->z);
//}
//inline TexProject::vec3						TexProject::vec3::operator-() const
//{
//	return vec3(-this->x, -this->y, -this->z);
//}
//

inline TexProject::vec3						TexProject::vec3::operator + (const vec3& a) const
{
	return vec3(
		x + a.x,
		y + a.y,
		z + a.z
		);
}
inline TexProject::vec3						TexProject::vec3::operator - (const vec3& a) const
{
	return vec3(
		x - a.x,
		y - a.y,
		z - a.z
		);
}
inline TexProject::vec3						TexProject::vec3::operator * (const vec3& a) const
{
	return vec3(
		x * a.x,
		y * a.y,
		z * a.z
		);
}
inline TexProject::vec3						TexProject::vec3::operator / (const vec3& a) const
{
	return vec3(
		x / a.x,
		y / a.y,
		z / a.z
		);
}

inline TexProject::vec3						TexProject::operator + (const vec3& a,const float32 b)
{
	return vec3(
		a.x + b,
		a.y + b,
		a.z + b
		);
}
inline TexProject::vec3						TexProject::operator - (const vec3& a,const float32 b)
{
	return vec3(
		a.x - b,
		a.y - b,
		a.z - b
		);
}
inline TexProject::vec3						TexProject::operator * (const vec3& a,const float32 b)
{
	return vec3(
		a.x * b,
		a.y * b,
		a.z * b
		);
}
inline TexProject::vec3						TexProject::operator / (const vec3& a,const float32 b)
{
	return vec3(
		a.x / b,
		a.y / b,
		a.z / b
		);
}

inline TexProject::vec3						TexProject::operator + (const float32 a,const vec3& b)
{
	return vec3(
		a + b.x,
		a + b.y,
		a + b.z
		);
}
inline TexProject::vec3						TexProject::operator - (const float32 a,const vec3& b)
{
	return vec3(
		a - b.x,
		a - b.y,
		a - b.z
		);
}
inline TexProject::vec3						TexProject::operator * (const float32 a,const vec3& b)
{
	return vec3(
		a * b.x,
		a * b.y,
		a * b.z
		);
}
inline TexProject::vec3						TexProject::operator / (const float32 a,const vec3& b)
{
	return vec3(
		a / b.x,
		a / b.y,
		a / b.z
		);
}
inline TexProject::vec2						TexProject::vec3::xy() const
{
	return vec2(
		x,
		y
		);
}

inline TexProject::vec2						TexProject::vec3::xz() const
{
	return vec2(
		x,
		z
		);
}
inline TexProject::vec2						TexProject::vec3::yz() const
{
	return vec2(
		y,
		z
		);
}
inline TexProject::float32					TexProject::vec3::length() const
{
	return sqrt(x * x + y * y + z * z);
}
inline TexProject::float32					TexProject::vec3::sqr()
{
	return x * x + y * y + z * z;
}
inline void									TexProject::vec3::normalize()
{
	float32 len = sqrt(x * x + y * y + z * z);
	x /= len;
	y /= len;
	z /= len;
}
#pragma endregion
#pragma region ivec3
inline										TexProject::ivec3::ivec3()
{
}
inline										TexProject::ivec3::ivec3(const int32 a_):
x(a_),
y(a_),
z(a_)
{
}
inline										TexProject::ivec3::ivec3(const int32 x_,const int32 y_,const int32 z_):
x(x_),
y(y_),
z(z_)
{
}
inline										TexProject::ivec3::ivec3(const ivec2& xy_,const int32 z_):
x(xy_.x),
y(xy_.y),
z(z_)
{
}
inline										TexProject::ivec3::ivec3(const int32 x_,const ivec2& yz_):
x(x_),
y(yz_.x),
z(yz_.y)
{
}
inline										TexProject::ivec3::ivec3(const vec3& a):
x(int32(a.x)),
y(int32(a.y)),
z(int32(a.z))
{
}
inline										TexProject::ivec3::ivec3(const uvec3& a):
x(int32(a.x)),
y(int32(a.y)),
z(int32(a.z))
{
}

inline TexProject::ivec3&					TexProject::ivec3::operator = (const int32 source)
{
	x = source;
	y = source;
	z = source;
	return *this;
}
inline TexProject::ivec3&					TexProject::ivec3::operator = (const uvec3& source)
{
	x = int32(source.x);
	y = int32(source.y);
	z = int32(source.z);
	return *this;
}
inline TexProject::ivec3&					TexProject::ivec3::operator = (const vec3& source)
{
	x = int32(source.x);
	y = int32(source.y);
	z = int32(source.z);
	return *this;
}

inline TexProject::ivec3&					TexProject::ivec3::operator += (const ivec3& a)
{
	x += a.x;
	y += a.y;
	z += a.z;
	return *this;
}
inline TexProject::ivec3&					TexProject::ivec3::operator -= (const ivec3& a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	return *this;
}
inline TexProject::ivec3&					TexProject::ivec3::operator *= (const ivec3& a)
{
	x *= a.x;
	y *= a.y;
	z *= a.z;
	return *this;
}
inline TexProject::ivec3&					TexProject::ivec3::operator /= (const ivec3& a)
{
	x /= a.x;
	y /= a.y;
	z /= a.z;
	return *this;
}

//
inline TexProject::ivec3&					TexProject::ivec3::operator += (const int32 a)
{
	x += a;
	y += a;
	z += a;
	return *this;
}
inline TexProject::ivec3&					TexProject::ivec3::operator -= (const int32 a)
{
	x -= a;
	y -= a;
	z -= a;
	return *this;
}
inline TexProject::ivec3&					TexProject::ivec3::operator *= (const int32 a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}
inline TexProject::ivec3&					TexProject::ivec3::operator /= (const int32 a)
{
	x /= a;
	y /= a;
	z /= a;
	return *this;
}

inline bool									TexProject::ivec3::operator == (const ivec3& a) const
{
	return this->x == a.x && this->y == a.y && this->z == a.z;
}
inline bool									TexProject::ivec3::operator != (const ivec3& a) const
{
	return this->x != a.x && this->y != a.y && this->z != a.z;
}

inline bool									TexProject::ivec3::operator == (const int32 a) const
{
	return this->x == a && this->y == a && this->z == a;
}
inline bool									TexProject::ivec3::operator != (const int32 a) const
{
	return this->x != a && this->y != a && this->z != a;
}

inline TexProject::ivec3					TexProject::ivec3::operator + () const
{
	return ivec3(+this->x, +this->y, +this->z);
}
inline TexProject::ivec3					TexProject::ivec3::operator - () const
{
	return ivec3(-this->x, -this->y, -this->z);
}
//

inline TexProject::ivec3					TexProject::ivec3::operator + (const ivec3& a) const
{
	return ivec3(
		x + a.x,
		y + a.y,
		z + a.z
		);
}
inline TexProject::ivec3					TexProject::ivec3::operator - (const ivec3& a) const
{
	return ivec3(
		x - a.x,
		y - a.y,
		z - a.z
		);
}
inline TexProject::ivec3					TexProject::ivec3::operator * (const ivec3& a) const
{
	return ivec3(
		x * a.x,
		y * a.y,
		z * a.z
		);
}
inline TexProject::ivec3					TexProject::ivec3::operator / (const ivec3& a) const
{
	return ivec3(
		x / a.x,
		y / a.y,
		z / a.z
		);
}

inline TexProject::ivec3					TexProject::operator + (const ivec3& a,const int32 b)
{
	return ivec3(
		a.x + b,
		a.y + b,
		a.z + b
		);
}
inline TexProject::ivec3					TexProject::operator - (const ivec3& a,const int32 b)
{
	return ivec3(
		a.x - b,
		a.y - b,
		a.z - b
		);
}
inline TexProject::ivec3					TexProject::operator * (const ivec3& a,const int32 b)
{
	return ivec3(
		a.x * b,
		a.y * b,
		a.z * b
		);
}
inline TexProject::ivec3					TexProject::operator / (const ivec3& a,const int32 b)
{
	return ivec3(
		a.x / b,
		a.y / b,
		a.z / b
		);
}

inline TexProject::ivec3					TexProject::operator + (const int32 a,const ivec3& b)
{
	return ivec3(
		a + b.x,
		a + b.y,
		a + b.z
		);
}
inline TexProject::ivec3					TexProject::operator - (const int32 a,const ivec3& b)
{
	return ivec3(
		a - b.x,
		a - b.y,
		a - b.z
		);
}
inline TexProject::ivec3					TexProject::operator * (const int32 a,const ivec3& b)
{
	return ivec3(
		a * b.x,
		a * b.y,
		a * b.z
		);
}
inline TexProject::ivec3					TexProject::operator / (const int32 a,const ivec3& b)
{
	return ivec3(
		a / b.x,
		a / b.y,
		a / b.z
		);
}

inline TexProject::ivec2					TexProject::ivec3::xy() const
{
	return ivec2(
		x,
		y
		);
}
inline TexProject::ivec2					TexProject::ivec3::xz() const
{
	return ivec2(
		x,
		z
		);
}
inline TexProject::ivec2					TexProject::ivec3::yz() const
{
	return ivec2(
		y,
		z
		);
}
#pragma endregion
#pragma region  uvec3
inline										TexProject::uvec3::uvec3()
{
}
inline										TexProject::uvec3::uvec3(const uint32 a_):
x(a_),
y(a_),
z(a_)
{
}
inline										TexProject::uvec3::uvec3(const uint32 x_,const uint32 y_,const uint32 z_):
x(x_),
y(y_),
z(z_)
{
}

inline										TexProject::uvec3::uvec3(const uvec2& xy_,const uint32 z_):
x(xy_.x),
y(xy_.y),
z(z_)
{
}
inline										TexProject::uvec3::uvec3(const uint32 x_,const uvec2& yz_):
x(x_),
y(yz_.x),
z(yz_.y)
{
}
inline										TexProject::uvec3::uvec3(const vec3& a):
x(uint32(a.x)),
y(uint32(a.y)),
z(uint32(a.z))
{
}
inline										TexProject::uvec3::uvec3(const ivec3& a):
x(uint32(a.x)),
y(uint32(a.y)),
z(uint32(a.z))
{
}

inline TexProject::uvec3&					TexProject::uvec3::operator = (const uint32 source)
{
	x = source;
	y = source;
	z = source;
	return *this;
}
inline TexProject::uvec3&					TexProject::uvec3::operator = (const ivec3& source)
{
	x = uint32(source.x);
	y = uint32(source.y);
	z = uint32(source.z);
	return *this;
}
inline TexProject::uvec3&					TexProject::uvec3::operator = (const vec3& source)
{
	x = uint32(source.x);
	y = uint32(source.y);
	z = uint32(source.z);
	return *this;
}
inline TexProject::uvec3&					TexProject::uvec3::operator += (const uvec3& a)
{
	x += a.x;
	y += a.y;
	z += a.z;
	return *this;
}
inline TexProject::uvec3&					TexProject::uvec3::operator -= (const uvec3& a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	return *this;
}
inline TexProject::uvec3&					TexProject::uvec3::operator *= (const uvec3& a)
{
	x *= a.x;
	y *= a.y;
	z *= a.z;
	return *this;
}
inline TexProject::uvec3&					TexProject::uvec3::operator /= (const uvec3& a)
{
	x /= a.x;
	y /= a.y;
	z /= a.z;
	return *this;
}

//
inline TexProject::uvec3&					TexProject::uvec3::operator += (const uint32 a)
{
	x += a;
	y += a;
	z += a;
	return *this;
}
inline TexProject::uvec3&					TexProject::uvec3::operator -= (const uint32 a)
{
	x -= a;
	y -= a;
	z -= a;
	return *this;
}
inline TexProject::uvec3&					TexProject::uvec3::operator *= (const uint32 a)
{
	x *= a;
	y *= a;
	z *= a;
	return *this;
}
inline TexProject::uvec3&					TexProject::uvec3::operator /= (const uint32 a)
{
	x /= a;
	y /= a;
	z /= a;
	return *this;
}

inline bool									TexProject::uvec3::operator == (const uvec3& a) const
{
	return this->x == a.x && this->y == a.y && this->z == a.z;
}
inline bool									TexProject::uvec3::operator != (const uvec3& a) const
{
	return this->x != a.x && this->y != a.y && this->z != a.z;
}
													 
inline bool									TexProject::uvec3::operator == (const uint32 a) const
{
	return this->x == a && this->y == a && this->z == a;
}
inline bool									TexProject::uvec3::operator != (const uint32 a) const
{
	return this->x != a && this->y != a && this->z != a;
}

inline TexProject::uvec3					TexProject::uvec3::operator + () const
{
	return uvec3(+this->x, +this->y, +this->z);
}
inline TexProject::ivec3					TexProject::uvec3::operator - () const
{
	return ivec3(-int(this->x), -int(this->y), -int(this->z));
}
//

inline TexProject::uvec3					TexProject::uvec3::operator + (const uvec3& a) const
{
	return uvec3(
		x + a.x,
		y + a.y,
		z + a.z
		);
}
inline TexProject::uvec3					TexProject::uvec3::operator - (const uvec3& a) const
{
	return uvec3(
		x - a.x,
		y - a.y,
		z - a.z
		);
}
inline TexProject::uvec3					TexProject::uvec3::operator * (const uvec3& a) const
{
	return uvec3(
		x * a.x,
		y * a.y,
		z * a.z
		);
}
inline TexProject::uvec3					TexProject::uvec3::operator / (const uvec3& a) const
{
	return uvec3(
		x / a.x,
		y / a.y,
		z / a.z
		);
}

inline TexProject::uvec3					TexProject::operator + (const uvec3& a,const uint32 b)
{
	return uvec3(
		a.x + b,
		a.y + b,
		a.z + b
		);
}
inline TexProject::uvec3					TexProject::operator - (const uvec3& a,const uint32 b)
{
	return uvec3(
		a.x - b,
		a.y - b,
		a.z - b
		);
}
inline TexProject::uvec3					TexProject::operator * (const uvec3& a,const uint32 b)
{
	return uvec3(
		a.x * b,
		a.y * b,
		a.z * b
		);
}
inline TexProject::uvec3					TexProject::operator / (const uvec3& a,const uint32 b)
{
	return uvec3(
		a.x / b,
		a.y / b,
		a.z / b
		);
}

inline TexProject::uvec3					TexProject::operator + (const uint32 a,const uvec3& b)
{
	return uvec3(
		a + b.x,
		a + b.y,
		a + b.z
		);
}
inline TexProject::uvec3					TexProject::operator - (const uint32 a,const uvec3& b)
{
	return uvec3(
		a - b.x,
		a - b.y,
		a - b.z
		);
}
inline TexProject::uvec3					TexProject::operator * (const uint32 a,const uvec3& b)
{
	return uvec3(
		a * b.x,
		a * b.y,
		a * b.z
		);
}
inline TexProject::uvec3					TexProject::operator / (const uint32 a,const uvec3& b)
{
	return uvec3(
		a / b.x,
		a / b.y,
		a / b.z
		);
}

inline TexProject::uvec2					TexProject::uvec3::xy() const
{
	return uvec2(
		x,
		y
		);
}
inline TexProject::uvec2					TexProject::uvec3::xz() const
{
	return uvec2(
		x,
		z
		);
}
inline TexProject::uvec2					TexProject::uvec3::yz() const
{
	return uvec2(
		y,
		z
		);
}
#pragma endregion
#pragma region vec4
inline										TexProject::vec4::vec4(const float32& a_):
x(a_),y(a_),z(a_),w(a_)
{
}
inline										TexProject::vec4::vec4(const vec3& xyz_,const float32 w_):
x(xyz_.x),
y(xyz_.y),
z(xyz_.z),
w(w_)
{
}
inline										TexProject::vec4::vec4(const float32 x_,const vec3& yzw_):
x(x_),
y(yzw_.x),
z(yzw_.y),
w(yzw_.z)
{
}
inline										TexProject::vec4::vec4(const vec2& xy_,const vec2& zw_):
x(xy_.x),
y(xy_.y),
z(zw_.x),
w(zw_.y)
{
}
inline										TexProject::vec4::vec4(const vec2& xy_,const float32 z_,const float32 w_):
x(xy_.x),
y(xy_.y),
z(z_),
w(w_)
{
}
inline										TexProject::vec4::vec4(const float32 x_,const vec2& yz_,const float32 w_):
x(x_),
y(yz_.x),
z(yz_.y),
w(w_)
{
}
inline										TexProject::vec4::vec4(const float32 x_,const float32 y_,const vec2& zw_):
x(x_),
y(y_),
z(zw_.x),
w(zw_.y)
{
}
inline										TexProject::vec4::vec4(const float32 x_,const float32 y_,const float32 z_,const float32 w_):
x(x_),
y(y_),
z(z_),
w(w_)
{
}
inline										TexProject::vec4::vec4(const ivec4& a):
x(float32(a.x)),
y(float32(a.y)),
z(float32(a.z)),
w(float32(a.w))
{
}
inline										TexProject::vec4::vec4(const uvec4& a):
x(float32(a.x)),
y(float32(a.y)),
z(float32(a.z)),
w(float32(a.w))
{
}

inline TexProject::vec4&					TexProject::vec4::operator = (const float32 source)
{
	x = source;
	y = source;
	z = source;
	w = source;
	return *this;
}
inline TexProject::vec4&					TexProject::vec4::operator = (const ivec4& source)
{
	x = float32(source.x);
	y = float32(source.y);
	z = float32(source.z);
	w = float32(source.w);
	return *this;
}
inline TexProject::vec4&					TexProject::vec4::operator = (const uvec4& source)
{
	x = float32(source.x);
	y = float32(source.y);
	z = float32(source.z);
	w = float32(source.w);
	return *this;
}

inline TexProject::vec4&					TexProject::vec4::operator += (const vec4& a)
{
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;
	return *this;
}
inline TexProject::vec4&					TexProject::vec4::operator -= (const vec4& a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;
	return *this;
}
inline TexProject::vec4&					TexProject::vec4::operator *= (const vec4& a)
{
	x *= a.x;
	y *= a.y;
	z *= a.z;
	w *= a.w;
	return *this;
}
inline TexProject::vec4&					TexProject::vec4::operator /= (const vec4& a)
{
	x /= a.x;
	y /= a.y;
	z /= a.z;
	w /= a.w;
	return *this;
}

//
inline TexProject::vec4&					TexProject::vec4::operator += (const float32 a)
{
	x += a;
	y += a;
	z += a;
	w += a;
	return *this;
}
inline TexProject::vec4&					TexProject::vec4::operator -= (const float32 a)
{
	x -= a;
	y -= a;
	z -= a;
	w -= a;
	return *this;
}
inline TexProject::vec4&					TexProject::vec4::operator *= (const float32 a)
{
	x *= a;
	y *= a;
	z *= a;
	w *= a;
	return *this;
}
inline TexProject::vec4&					TexProject::vec4::operator /= (const float32 a)
{
	x /= a;
	y /= a;
	z /= a;
	w /= a;
	return *this;
}

inline bool									TexProject::vec4::operator == (const vec4& a) const
{
	return this->x == a.x && this->y == a.y && this->z == a.z && this->w == a.w;
}
inline bool									TexProject::vec4::operator != (const vec4& a) const
{
	return this->x != a.x && this->y != a.y && this->z != a.z && this->w != a.w;
}

inline bool									TexProject::vec4::operator == (const float32 a) const
{
	return this->x == a && this->y == a && this->z == a && this->w == a;
}
inline bool									TexProject::vec4::operator != (const float32 a) const
{
	return this->x != a && this->y != a && this->z != a && this->w != a;
}

inline TexProject::vec4						TexProject::vec4::operator + () const
{
	return vec4(+this->x, +this->y, +this->z, +this->w);
}
inline TexProject::vec4						TexProject::vec4::operator - () const
{
	return vec4(-this->x, -this->y, -this->z, -this->w);
}
//

inline TexProject::vec4						TexProject::vec4::operator + (const vec4& a) const
{
	return vec4(
		x + a.x,
		y + a.y,
		z + a.z,
		w + a.w
		);
}
inline TexProject::vec4						TexProject::vec4::operator - (const vec4& a) const
{
	return vec4(
		x - a.x,
		y - a.y,
		z - a.z,
		w - a.w
		);
}
inline TexProject::vec4						TexProject::vec4::operator * (const vec4& a) const
{
	return vec4(
		x * a.x,
		y * a.y,
		z * a.z,
		w * a.w
		);
}
inline TexProject::vec4						TexProject::vec4::operator / (const vec4& a) const
{
	return vec4(
		x / a.x,
		y / a.y,
		z / a.z,
		w / a.w
		);
}

inline TexProject::vec4						TexProject::operator + (const vec4& a,const float32 b)
{
	return vec4(
		a.x + b,
		a.y + b,
		a.z + b,
		a.w + b
		);
}
inline TexProject::vec4						TexProject::operator - (const vec4& a,const float32 b)
{
	return vec4(
		a.x - b,
		a.y - b,
		a.z - b,
		a.w - b
		);
}
inline TexProject::vec4						TexProject::operator * (const vec4& a,const float32 b)
{
	return vec4(
		a.x * b,
		a.y * b,
		a.z * b,
		a.w * b
		);
}
inline TexProject::vec4						TexProject::operator / (const vec4& a,const float32 b)
{
	return vec4(
		a.x / b,
		a.y / b,
		a.z / b,
		a.w / b
		);
}

inline TexProject::vec4						TexProject::operator + (const float32 a,const vec4& b)
{
	return vec4(
		a + b.x,
		a + b.y,
		a + b.z,
		a + b.w
		);
}
inline TexProject::vec4						TexProject::operator - (const float32 a,const vec4& b)
{
	return vec4(
		a - b.x,
		a - b.y,
		a - b.z,
		a - b.w
		);
}
inline TexProject::vec4						TexProject::operator * (const float32 a,const vec4& b)
{
	return vec4(
		a * b.x,
		a * b.y,
		a * b.z,
		a * b.w
		);
}
inline TexProject::vec4						TexProject::operator / (const float32 a,const vec4& b)
{
	return vec4(
		a / b.x,
		a / b.y,
		a / b.z,
		a / b.w
		);
}

inline TexProject::vec3						TexProject::vec4::xyz() const
{
	return vec3(
		x,
		y,
		z
		);
}
inline TexProject::vec3						TexProject::vec4::xyw() const
{
	return vec3(
		x,
		y,
		w
		);
}
inline TexProject::vec3						TexProject::vec4::xzw() const
{
	return vec3(
		x,
		z,
		w
		);
}
inline TexProject::vec3						TexProject::vec4::yzw() const
{
	return vec3(
		y,
		z,
		w
		);
}

inline TexProject::float32					TexProject::vec4::length() const
{
	return sqrt(x * x + y * y + z * z + w * w);
}
inline TexProject::float32					TexProject::vec4::sqr()
{
	return x * x + y * y + z * z + w * w;
}
inline void									TexProject::vec4::normalize()
{
	float32 len = x * x + y * y + z * z + w * w;
	x /= len;
	y /= len;
	z /= len;
	w /= len;
}
#pragma endregion
#pragma region ivec4
inline										TexProject::ivec4::ivec4(const ivec3& xyz_,const int32 w_):
x(xyz_.x),
y(xyz_.y),
z(xyz_.z),
w(w_)
{
}
inline										TexProject::ivec4::ivec4(const int32 x_,const ivec3& yzw_):
x(x_),
y(yzw_.x),
z(yzw_.y),
w(yzw_.z)
{
}
inline										TexProject::ivec4::ivec4(const ivec2& xy_,const ivec2& zw_):
x(xy_.x),
y(xy_.y),
z(zw_.x),
w(zw_.y)
{
}
inline										TexProject::ivec4::ivec4(const ivec2& xy_,const int32 z_,const int32 w_):
x(xy_.x),
y(xy_.y),
z(z_),
w(w_)
{
}
inline										TexProject::ivec4::ivec4(const int32 x_,const ivec2& yz_,const int32 w_):
x(x_),
y(yz_.x),
z(yz_.y),
w(w_)
{
}
inline										TexProject::ivec4::ivec4(const int32 x_,const int32 y_,const ivec2& zw_):
x(x_),
y(y_),
z(zw_.x),
w(zw_.y)
{
}
inline										TexProject::ivec4::ivec4(const int32 x_,const int32 y_,const int32 z_,const int32 w_):
x(x_),
y(y_),
z(z_),
w(w_)
{
}
inline										TexProject::ivec4::ivec4(const vec4& a):
x(int32(a.x)),
y(int32(a.y)),
z(int32(a.z)),
w(int32(a.w))
{
}
inline										TexProject::ivec4::ivec4(const uvec4& a):
x(int32(a.x)),
y(int32(a.y)),
z(int32(a.z)),
w(int32(a.w))
{
}

inline TexProject::ivec4&					TexProject::ivec4::operator = (const int32 source)
{
	x = source;
	y = source;
	z = source;
	w = source;
	return *this;
}
inline TexProject::ivec4&					TexProject::ivec4::operator = (const vec4& source)
{
	x = int32(source.x);
	y = int32(source.y);
	z = int32(source.z);
	w = int32(source.w);
	return *this;
}
inline TexProject::ivec4&					TexProject::ivec4::operator = (const uvec4& source)
{
	x = int32(source.x);
	y = int32(source.y);
	z = int32(source.z);
	w = int32(source.w);
	return *this;
}

inline TexProject::ivec4&					TexProject::ivec4::operator += (const ivec4& a)
{
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;
	return *this;
}
inline TexProject::ivec4&					TexProject::ivec4::operator -= (const ivec4& a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;
	return *this;
}
inline TexProject::ivec4&					TexProject::ivec4::operator *= (const ivec4& a)
{
	x *= a.x;
	y *= a.y;
	z *= a.z;
	w *= a.w;
	return *this;
}
inline TexProject::ivec4&					TexProject::ivec4::operator /= (const ivec4& a)
{
	x /= a.x;
	y /= a.y;
	z /= a.z;
	w /= a.w;
	return *this;
}

//
inline TexProject::ivec4&					TexProject::ivec4::operator += (const int32 a)
{
	x += a;
	y += a;
	z += a;
	w += a;
	return *this;
}
inline TexProject::ivec4&					TexProject::ivec4::operator -= (const int32 a)
{
	x -= a;
	y -= a;
	z -= a;
	w -= a;
	return *this;
}
inline TexProject::ivec4&					TexProject::ivec4::operator *= (const int32 a)
{
	x *= a;
	y *= a;
	z *= a;
	w *= a;
	return *this;
}
inline TexProject::ivec4&					TexProject::ivec4::operator /= (const int32 a)
{
	x /= a;
	y /= a;
	z /= a;
	w /= a;
	return *this;
}

inline bool									TexProject::ivec4::operator == (const ivec4& a) const
{
	return this->x == a.x && this->y == a.y && this->z == a.z && this->w == a.w;
}
inline bool									TexProject::ivec4::operator != (const ivec4& a) const
{
	return this->x != a.x && this->y != a.y && this->z != a.z && this->w != a.w;
}

inline bool									TexProject::ivec4::operator == (const int32 a) const
{
	return this->x == a && this->y == a && this->z == a && this->w == a;
}
inline bool									TexProject::ivec4::operator != (const int32 a) const
{
	return this->x != a && this->y != a && this->z != a && this->w != a;
}

inline TexProject::ivec4					TexProject::ivec4::operator + () const
{
	return ivec4(+this->x, +this->y, +this->z, +this->w);
}
inline TexProject::ivec4					TexProject::ivec4::operator - () const
{
	return ivec4(-this->x, -this->y, -this->z, -this->w);
}
//

inline TexProject::ivec4					TexProject::ivec4::operator + (const ivec4& a) const
{
	return ivec4(
		x + a.x,
		y + a.y,
		z + a.z,
		w + a.w
		);
}
inline TexProject::ivec4					TexProject::ivec4::operator - (const ivec4& a) const
{
	return ivec4(
		x - a.x,
		y - a.y,
		z - a.z,
		w - a.w
		);
}
inline TexProject::ivec4					TexProject::ivec4::operator * (const ivec4& a) const
{
	return ivec4(
		x * a.x,
		y * a.y,
		z * a.z,
		w * a.w
		);
}
inline TexProject::ivec4					TexProject::ivec4::operator / (const ivec4& a) const
{
	return ivec4(
		x / a.x,
		y / a.y,
		z / a.z,
		w / a.w
		);
}

inline TexProject::ivec4					TexProject::operator + (const ivec4& a,const int32 b)
{
	return ivec4(
		a.x + b,
		a.y + b,
		a.z + b,
		a.w + b
		);
}
inline TexProject::ivec4					TexProject::operator - (const ivec4& a,const int32 b)
{
	return ivec4(
		a.x - b,
		a.y - b,
		a.z - b,
		a.w - b
		);
}
inline TexProject::ivec4					TexProject::operator * (const ivec4& a,const int32 b)
{
	return ivec4(
		a.x * b,
		a.y * b,
		a.z * b,
		a.w * b
		);
}
inline TexProject::ivec4					TexProject::operator / (const ivec4& a,const int32 b)
{
	return ivec4(
		a.x / b,
		a.y / b,
		a.z / b,
		a.w / b
		);
}

inline TexProject::ivec4					TexProject::operator + (const int32 a,const ivec4& b)
{
	return ivec4(
		a + b.x,
		a + b.y,
		a + b.z,
		a + b.w
		);
}
inline TexProject::ivec4					TexProject::operator - (const int32 a,const ivec4& b)
{
	return ivec4(
		a - b.x,
		a - b.y,
		a - b.z,
		a - b.w
		);
}
inline TexProject::ivec4					TexProject::operator * (const int32 a,const ivec4& b)
{
	return ivec4(
		a * b.x,
		a * b.y,
		a * b.z,
		a * b.w
		);
}
inline TexProject::ivec4					TexProject::operator / (const int32 a,const ivec4& b)
{
	return ivec4(
		a / b.x,
		a / b.y,
		a / b.z,
		a / b.w
		);
}

inline TexProject::ivec3					TexProject::ivec4::xyz() const
{
	return ivec3(
		x,
		y,
		z
		);
}
inline TexProject::ivec3					TexProject::ivec4::xyw() const
{
	return ivec3(
		x,
		y,
		w
		);
}
inline TexProject::ivec3					TexProject::ivec4::xzw() const
{
	return ivec3(
		x,
		z,
		w
		);
}
inline TexProject::ivec3					TexProject::ivec4::yzw() const
{
	return ivec3(
		y,
		z,
		w
		);
}
#pragma endregion
#pragma region uvec4
inline										TexProject::uvec4::uvec4(const uvec3& xyz_,const uint32 w_):
x(xyz_.x),
y(xyz_.y),
z(xyz_.z),
w(w_)
{
}
inline										TexProject::uvec4::uvec4(const uint32 x_,const uvec3& yzw_):
x(x_),
y(yzw_.x),
z(yzw_.y),
w(yzw_.z)
{
}
inline										TexProject::uvec4::uvec4(const uvec2& xy_,const uvec2& zw_):
x(xy_.x),
y(xy_.y),
z(zw_.x),
w(zw_.y)
{
}
inline										TexProject::uvec4::uvec4(const uvec2& xy_,const uint32 z_,const uint32 w_):
x(xy_.x),
y(xy_.y),
z(z_),
w(w_)
{
}
inline										TexProject::uvec4::uvec4(const uint32 x_,const uvec2& yz_,const uint32 w_):
x(x_),
y(yz_.x),
z(yz_.y),
w(w_)
{
}
inline										TexProject::uvec4::uvec4(const uint32 x_,const uint32 y_,const uvec2& zw_):
x(x_),
y(y_),
z(zw_.x),
w(zw_.y)
{
}
inline										TexProject::uvec4::uvec4(const uint32 x_,const uint32 y_,const uint32 z_,const uint32 w_):
x(x_),
y(y_),
z(z_),
w(w_)
{
}
inline										TexProject::uvec4::uvec4(const vec4& a):
x(uint32(a.x)),
y(uint32(a.y)),
z(uint32(a.z)),
w(uint32(a.w))
{
}
inline										TexProject::uvec4::uvec4(const ivec4& a):
x(uint32(a.x)),
y(uint32(a.y)),
z(uint32(a.z)),
w(uint32(a.w))
{
}

inline TexProject::uvec4&					TexProject::uvec4::operator = (const uint32 source)
{
	x = source;
	y = source;
	z = source;
	w = source;
	return *this;
}
inline TexProject::uvec4&					TexProject::uvec4::operator = (const vec4& source)
{
	x = uint32(source.x);
	y = uint32(source.y);
	z = uint32(source.z);
	w = uint32(source.w);
	return *this;
}
inline TexProject::uvec4&					TexProject::uvec4::operator = (const ivec4& source)
{
	x = uint32(source.x);
	y = uint32(source.y);
	z = uint32(source.z);
	w = uint32(source.w);
	return *this;
}

inline TexProject::uvec4&					TexProject::uvec4::operator += (const uvec4& a)
{
	x += a.x;
	y += a.y;
	z += a.z;
	w += a.w;
	return *this;
}
inline TexProject::uvec4&					TexProject::uvec4::operator -= (const uvec4& a)
{
	x -= a.x;
	y -= a.y;
	z -= a.z;
	w -= a.w;
	return *this;
}
inline TexProject::uvec4&					TexProject::uvec4::operator *= (const uvec4& a)
{
	x *= a.x;
	y *= a.y;
	z *= a.z;
	w *= a.w;
	return *this;
}
inline TexProject::uvec4&					TexProject::uvec4::operator /= (const uvec4& a)
{
	x /= a.x;
	y /= a.y;
	z /= a.z;
	w /= a.w;
	return *this;
}

//
inline TexProject::uvec4&					TexProject::uvec4::operator += (const uint32 a)
{
	x += a;
	y += a;
	z += a;
	w += a;
	return *this;
}
inline TexProject::uvec4&					TexProject::uvec4::operator -= (const uint32 a)
{
	x -= a;
	y -= a;
	z -= a;
	w -= a;
	return *this;
}
inline TexProject::uvec4&					TexProject::uvec4::operator *= (const uint32 a)
{
	x *= a;
	y *= a;
	z *= a;
	w *= a;
	return *this;
}
inline TexProject::uvec4&					TexProject::uvec4::operator /= (const uint32 a)
{
	x /= a;
	y /= a;
	z /= a;
	w /= a;
	return *this;
}

inline bool									TexProject::uvec4::operator == (const uvec4& a) const
{
	return this->x == a.x && this->y == a.y && this->z == a.z && this->w == a.w;
}
inline bool									TexProject::uvec4::operator != (const uvec4& a) const
{
	return this->x != a.x && this->y != a.y && this->z != a.z && this->w != a.w;
}

inline bool									TexProject::uvec4::operator == (const uint32 a) const
{
	return this->x == a && this->y == a && this->z == a && this->w == a;
}
inline bool									TexProject::uvec4::operator != (const uint32 a) const
{
	return this->x != a && this->y != a && this->z != a && this->w != a;
}

inline TexProject::uvec4					TexProject::uvec4::operator + () const
{
	return uvec4(+this->x, +this->y, +this->z, +this->w);
}
inline TexProject::ivec4					TexProject::uvec4::operator - () const
{
	return ivec4(-int(this->x), -int(this->y), -int(this->z), -int(this->w));
}
//

inline TexProject::uvec4					TexProject::uvec4::operator + (const uvec4& a) const
{
	return uvec4(
		x + a.x,
		y + a.y,
		z + a.z,
		w + a.w
		);
}
inline TexProject::uvec4					TexProject::uvec4::operator - (const uvec4& a) const
{
	return uvec4(
		x - a.x,
		y - a.y,
		z - a.z,
		w - a.w
		);
}
inline TexProject::uvec4					TexProject::uvec4::operator * (const uvec4& a) const
{
	return uvec4(
		x * a.x,
		y * a.y,
		z * a.z,
		w * a.w
		);
}
inline TexProject::uvec4					TexProject::uvec4::operator / (const uvec4& a) const
{
	return uvec4(
		x / a.x,
		y / a.y,
		z / a.z,
		w / a.w
		);
}

inline TexProject::uvec4					TexProject::operator + (const uvec4& a,const uint32 b)
{
	return uvec4(
		a.x + b,
		a.y + b,
		a.z + b,
		a.w + b
		);
}
inline TexProject::uvec4					TexProject::operator - (const uvec4& a,const uint32 b)
{
	return uvec4(
		a.x - b,
		a.y - b,
		a.z - b,
		a.w - b
		);
}
inline TexProject::uvec4					TexProject::operator * (const uvec4& a,const uint32 b)
{
	return uvec4(
		a.x * b,
		a.y * b,
		a.z * b,
		a.w * b
		);
}
inline TexProject::uvec4					TexProject::operator / (const uvec4& a,const uint32 b)
{
	return uvec4(
		a.x / b,
		a.y / b,
		a.z / b,
		a.w / b
		);
}

inline TexProject::uvec4					TexProject::operator + (const uint32 a,const uvec4& b)
{
	return uvec4(
		a + b.x,
		a + b.y,
		a + b.z,
		a + b.w
		);
}
inline TexProject::uvec4					TexProject::operator - (const uint32 a,const uvec4& b)
{
	return uvec4(
		a - b.x,
		a - b.y,
		a - b.z,
		a - b.w
		);
}
inline TexProject::uvec4					TexProject::operator * (const uint32 a,const uvec4& b)
{
	return uvec4(
		a * b.x,
		a * b.y,
		a * b.z,
		a * b.w
		);
}
inline TexProject::uvec4					TexProject::operator / (const uint32 a,const uvec4& b)
{
	return uvec4(
		a / b.x,
		a / b.y,
		a / b.z,
		a / b.w
		);
}

inline TexProject::uvec3					TexProject::uvec4::xyz() const
{
	return uvec3(
		x,
		y,
		z
		);
}
inline TexProject::uvec3					TexProject::uvec4::xyw() const
{
	return uvec3(
		x,
		y,
		w
		);
}
inline TexProject::uvec3					TexProject::uvec4::xzw() const
{
	return uvec3(
		x,
		z,
		w
		);
}
inline TexProject::uvec3					TexProject::uvec4::yzw() const
{
	return uvec3(
		y,
		z,
		w
		);
}
#pragma endregion
#pragma region mat3
inline TexProject::mat3						TexProject::mat3::null()
{
	mat3 res; res.makeNull(); return res;
}
inline TexProject::mat3						TexProject::mat3::one()
{
	mat3 res; res.makeOne(); return res;
}
inline TexProject::mat3						TexProject::mat3::rotateZXY(vec3 ang)
{
	mat3 res; res.makeRotateZXY(ang); return res;
}
inline TexProject::mat3						TexProject::mat3::rotateYXZ(vec3 ang)
{
	mat3 res; res.makeRotateYXZ(ang); return res;
}

inline TexProject::mat3::mat3(const mat3& source)
{
	val[0] = source.val[0];
	val[1] = source.val[1];
	val[2] = source.val[2];
	val[3] = source.val[3];
	val[4] = source.val[4];
	val[5] = source.val[5];
	val[6] = source.val[6];
	val[7] = source.val[7];
	val[8] = source.val[8];
}

inline TexProject::mat3&					TexProject::mat3::operator = (const mat3& source)
{
	val[0] = source.val[0];
	val[1] = source.val[1];
	val[2] = source.val[2];
	val[3] = source.val[3];
	val[4] = source.val[4];
	val[5] = source.val[5];
	val[6] = source.val[6];
	val[7] = source.val[7];
	val[8] = source.val[8];
	return *this;
}

inline TexProject::mat3						TexProject::operator * (const TexProject::mat3& a,const TexProject::mat3& b)
{
	TexProject::mat3 res;

	res.val[0] = a.val[0]*b.val[0] + a.val[3]*b.val[1] + a.val[6]*b.val[2];
	res.val[1] = a.val[1]*b.val[0] + a.val[4]*b.val[1] + a.val[7]*b.val[2];
	res.val[2] = a.val[2]*b.val[0] + a.val[5]*b.val[1] + a.val[8]*b.val[2];

	res.val[3] = a.val[0]*b.val[3] + a.val[3]*b.val[4] + a.val[6]*b.val[5];
	res.val[4] = a.val[1]*b.val[3] + a.val[4]*b.val[4] + a.val[7]*b.val[5];
	res.val[5] = a.val[2]*b.val[3] + a.val[5]*b.val[4] + a.val[8]*b.val[5];

	res.val[6] = a.val[0]*b.val[6] + a.val[3]*b.val[7] + a.val[6]*b.val[8];
	res.val[7] = a.val[1]*b.val[6] + a.val[4]*b.val[7] + a.val[7]*b.val[8];
	res.val[8] = a.val[2]*b.val[6] + a.val[5]*b.val[7] + a.val[8]*b.val[8];

	return res;
}

inline TexProject::vec3						TexProject::operator * (const mat3& m,const vec3& v)
{
	return vec3
		(
		m.val[0]*v.x + m.val[1]*v.y + m.val[2]*v.z,
		m.val[3]*v.x + m.val[4]*v.y + m.val[5]*v.z,
		m.val[6]*v.x + m.val[7]*v.y + m.val[8]*v.z
		);
}

inline void									TexProject::mat3::makeNull()
{
	val[0] = _0f;
	val[1] = _0f;
	val[2] = _0f;
	val[3] = _0f;
	val[4] = _0f;
	val[5] = _0f;
	val[6] = _0f;
	val[7] = _0f;
	val[8] = _0f;
}
inline void									TexProject::mat3::makeOne()
{
	val[0] = _1f;
	val[1] = _0f;
	val[2] = _0f;
	val[3] = _0f;
	val[4] = _1f;
	val[5] = _0f;
	val[6] = _0f;
	val[7] = _0f;
	val[8] = _1f;
}
inline void									TexProject::mat3::makeRotateZXY(vec3 angle)
{
	static float cX_,sX_,cY_,sY_,cZ_,sZ_;
	_asm
	{
		FLD				angle.x
			FMUL			_PIdev180f
			FSINCOS
			FSTP			cX_
			FSTP			sX_
			FLD				angle.y
			FMUL			_PIdev180f
			FSINCOS
			FSTP			cY_
			FSTP			sY_
			FLD				angle.z
			FMUL			_PIdev180f
			FSINCOS
			FSTP			cZ_
			FSTP			sZ_
	}
	val[0] = cZ_*cY_ - sZ_*sX_*sY_;
	val[1] = sZ_*cY_ + cZ_*sX_*sY_;
	val[2] = cX_*sY_;
	val[3] = -sZ_*cX_;
	val[4] = cZ_*cX_;
	val[5] = -sX_;
	val[6] = -cZ_*sY_ - sZ_*sX_*cY_;
	val[7] = -sZ_*sY_ + cZ_*sX_*cY_;
	val[8] = cX_*cY_;
}
inline void									TexProject::mat3::makeRotateYXZ(vec3 angle)
{
	static float cX_,sX_,cY_,sY_,cZ_,sZ_;
	_asm
	{
		FLD				angle.x
			FMUL			_PIdev180f
			FSINCOS
			FSTP			cX_
			FSTP			sX_

			FLD				angle.y
			FMUL			_PIdev180f
			FSINCOS
			FSTP			cY_
			FSTP			sY_

			FLD				angle.z
			FMUL			_PIdev180f
			FSINCOS
			FSTP			cZ_
			FSTP			sZ_
	}
	val[0] = cY_*cZ_ + sY_*sX_*sZ_;
	val[1] = cX_*sZ_;
	val[2] = sY_*cZ_ - cY_*sX_*sZ_;
	val[3] = -cY_*sZ_ + sY_*sX_*cZ_;
	val[4] = cX_*cZ_;
	val[5] = -sY_*sZ_ - cY_*sX_*cZ_;
	val[6] = -sY_*cX_;
	val[7] = sX_;
	val[8] = cY_*cX_;
}
#pragma endregion
#pragma region mat4
inline TexProject::mat4						TexProject::mat4::null()
{
	mat4 res; res.makeNull(); return res;
}
inline TexProject::mat4						TexProject::mat4::one()
{
	mat4 res; res.makeOne(); return res;
}
inline TexProject::mat4						TexProject::mat4::move(vec3 pos)
{
	mat4 res; res.makeMove(pos); return res;
}
inline TexProject::mat4						TexProject::mat4::scale(vec3 scale)
{
	mat4 res; res.makeScale(scale); return res;
}
inline TexProject::mat4						TexProject::mat4::rotateZXY(vec3 ang)
{
	mat4 res; res.makeRotateZXY(ang); return res;
}
inline TexProject::mat4						TexProject::mat4::rotateYXZ(vec3 ang)
{
	mat4 res; res.makeRotateYXZ(ang); return res;
}
inline TexProject::mat4						TexProject::mat4::perspective(float32 FOV,float32 aspect,float32 zNear,float32 zFar)
{
	mat4 res; res.makeProjectionPerspective(FOV,aspect,zNear,zFar); return res;
}
/*inline TexProject::mat4						TexProject::mat4::perspectiveInv(float32 FOV,float32 aspect,float32 zNear,float32 zFar)
{
}*/
inline TexProject::mat4						TexProject::mat4::orthogonal(float32 left,float32 right,float32 bottom,float32 top,float32 back,float32 front)
{
	mat4 res; res.makeProjectionOrthogonal(left,right,bottom,top,back,front); return res;
}

inline TexProject::mat4::mat4(const mat3& source)
{
	val[0] = source.val[0];
	val[1] = source.val[1];
	val[2] = source.val[2];
	val[3] = _0f;
	val[4] = source.val[3];
	val[5] = source.val[4];
	val[6] = source.val[5];
	val[7] = _0f;
	val[8] = source.val[6];
	val[9] = source.val[7];
	val[10] = source.val[8];
	val[11] = _0f;
	val[12] = _0f;
	val[13] = _0f;
	val[14] = _0f;
	val[15] = _1f;
}
inline TexProject::mat4::mat4(const mat4& source)
{
	val[0] = source.val[0];
	val[1] = source.val[1];
	val[2] = source.val[2];
	val[3] = source.val[3];
	val[4] = source.val[4];
	val[5] = source.val[5];
	val[6] = source.val[6];
	val[7] = source.val[7];
	val[8] = source.val[8];
	val[9] = source.val[9];
	val[10] = source.val[10];
	val[11] = source.val[11];
	val[12] = source.val[12];
	val[13] = source.val[13];
	val[14] = source.val[14];
	val[15] = source.val[15];
}

inline TexProject::mat4&					TexProject::mat4::operator = (const mat4& source)
{
	val[0] = source.val[0];
	val[1] = source.val[1];
	val[2] = source.val[2];
	val[3] = source.val[3];
	val[4] = source.val[4];
	val[5] = source.val[5];
	val[6] = source.val[6];
	val[7] = source.val[7];
	val[8] = source.val[8];
	val[9] = source.val[9];
	val[10] = source.val[10];
	val[11] = source.val[11];
	val[12] = source.val[12];
	val[13] = source.val[13];
	val[14] = source.val[14];
	val[15] = source.val[15];
	return *this;
}

inline TexProject::mat4						TexProject::operator * (const TexProject::mat4& a,const TexProject::mat4& b)
{
	TexProject::mat4 c;

	c.val[0] = a.val[0]*b.val[0] + a.val[4]*b.val[1] + a.val[8]*b.val[2] + a.val[12]*b.val[3];
	c.val[4] = a.val[0]*b.val[4] + a.val[4]*b.val[5] + a.val[8]*b.val[6] + a.val[12]*b.val[7];
	c.val[8] = a.val[0]*b.val[8] + a.val[4]*b.val[9] + a.val[8]*b.val[10] + a.val[12]*b.val[11];
	c.val[12] = a.val[0]*b.val[12] + a.val[4]*b.val[13] + a.val[8]*b.val[14] + a.val[12]*b.val[15];

	c.val[1] = a.val[1]*b.val[0] + a.val[5]*b.val[1] + a.val[9]*b.val[2] + a.val[13]*b.val[3];
	c.val[5] = a.val[1]*b.val[4] + a.val[5]*b.val[5] + a.val[9]*b.val[6] + a.val[13]*b.val[7];
	c.val[9] = a.val[1]*b.val[8] + a.val[5]*b.val[9] + a.val[9]*b.val[10] + a.val[13]*b.val[11];
	c.val[13] = a.val[1]*b.val[12] + a.val[5]*b.val[13] + a.val[9]*b.val[14] + a.val[13]*b.val[15];

	c.val[2] = a.val[2]*b.val[0] + a.val[6]*b.val[1] + a.val[10]*b.val[2] + a.val[14]*b.val[3];
	c.val[6] = a.val[2]*b.val[4] + a.val[6]*b.val[5] + a.val[10]*b.val[6] + a.val[14]*b.val[7];
	c.val[10] = a.val[2]*b.val[8] + a.val[6]*b.val[9] + a.val[10]*b.val[10] + a.val[14]*b.val[11];
	c.val[14] = a.val[2]*b.val[12] + a.val[6]*b.val[13] + a.val[10]*b.val[14] + a.val[14]*b.val[15];

	c.val[3] = a.val[3]*b.val[0] + a.val[7]*b.val[1] + a.val[11]*b.val[2] + a.val[15]*b.val[3];
	c.val[7] = a.val[3]*b.val[4] + a.val[7]*b.val[5] + a.val[11]*b.val[6] + a.val[15]*b.val[7];
	c.val[11] = a.val[3]*b.val[8] + a.val[7]*b.val[9] + a.val[11]*b.val[10] + a.val[15]*b.val[11];
	c.val[15] = a.val[3]*b.val[12] + a.val[7]*b.val[13] + a.val[11]*b.val[14] + a.val[15]*b.val[15];

	return c;
}

inline TexProject::vec3						TexProject::operator * (const mat4& m,const vec3& v)
{
	return vec3
		(
		m.val[0]*v.x + m.val[1]*v.y + m.val[2]*v.z + m.val[3],
		m.val[4]*v.x + m.val[5]*v.y + m.val[6]*v.z + m.val[7],
		m.val[8]*v.x + m.val[9]*v.y + m.val[10]*v.z + m.val[11]
		);
}

inline void									TexProject::mat4::makeNull()
{
	val[0] = _0f;
	val[1] = _0f;
	val[2] = _0f;
	val[3] = _0f;
	val[4] = _0f;
	val[5] = _0f;
	val[6] = _0f;
	val[7] = _0f;
	val[8] = _0f;
	val[9] = _0f;
	val[10] = _0f;
	val[11] = _0f;
	val[12] = _0f;
	val[13] = _0f;
	val[14] = _0f;
	val[15] = _0f;
}
inline void									TexProject::mat4::makeOne()
{
	val[0] = _1f;
	val[1] = _0f;
	val[2] = _0f;
	val[3] = _0f;
	val[4] = _0f;
	val[5] = _1f;
	val[6] = _0f;
	val[7] = _0f;
	val[8] = _0f;
	val[9] = _0f;
	val[10] = _1f;
	val[11] = _0f;
	val[12] = _0f;
	val[13] = _0f;
	val[14] = _0f;
	val[15] = _1f;
}
inline void									TexProject::mat4::makeMove(vec3 move)
{
	val[0] = _1f;
	val[1] = _0f;
	val[2] = _0f;
	val[3] = move.x;
	val[4] = _0f;
	val[5] = _1f;
	val[6] = _0f;
	val[7] = move.y;
	val[8] = _0f;
	val[9] = _0f;
	val[10] = _1f;
	val[11] = move.z;
	val[12] = _0f;
	val[13] = _0f;
	val[14] = _0f;
	val[15] = _1f;
}
inline void									TexProject::mat4::makeScale(vec3 scale)
{
	val[0] = scale.x;
	val[1] = _0f;
	val[2] = _0f;
	val[3] = _0f;
	val[4] = _0f;
	val[5] = scale.y;
	val[6] = _0f;
	val[7] = _0f;
	val[8] = _0f;
	val[9] = _0f;
	val[10] = scale.z;
	val[11] = _0f;
	val[12] = _0f;
	val[13] = _0f;
	val[14] = _0f;
	val[15] = _1f;
}
inline void									TexProject::mat4::makeRotateZXY(vec3 angle)
{
	static float32 cX_,sX_,cY_,sY_,cZ_,sZ_;
	_asm
	{
		FLD				angle.x
			FMUL			_PIdev180f
			FSINCOS
			FSTP			cX_
			FSTP			sX_
			FLD				angle.y
			FMUL			_PIdev180f
			FSINCOS
			FSTP			cY_
			FSTP			sY_
			FLD				angle.z
			FMUL			_PIdev180f
			FSINCOS
			FSTP			cZ_
			FSTP			sZ_
	}
	val[0] = cZ_*cY_ - sZ_*sX_*sY_;
	val[1] = sZ_*cY_ + cZ_*sX_*sY_;
	val[2] = cX_*sY_;
	val[4] = -sZ_*cX_;
	val[5] = cZ_*cX_;
	val[6] = -sX_;
	val[8] = -cZ_*sY_ - sZ_*sX_*cY_;
	val[9] = -sZ_*sY_ + cZ_*sX_*cY_;
	val[10] = cX_*cY_;
	val[3] = _0f;
	val[7] = _0f;
	val[11] = _0f;
	val[12] = _0f;
	val[13] = _0f;
	val[14] = _0f;
	val[15] = _1f;
}
inline void									TexProject::mat4::makeRotateYXZ(vec3 angle)
{
	static float32 cX_,sX_,cY_,sY_,cZ_,sZ_;
	_asm
	{
		FLD				angle.x
			FMUL			_PIdev180f
			FSINCOS
			FSTP			cX_
			FSTP			sX_
			FLD				angle.y
			FMUL			_PIdev180f
			FSINCOS
			FSTP			cY_
			FSTP			sY_
			FLD				angle.z
			FMUL			_PIdev180f
			FSINCOS
			FSTP			cZ_
			FSTP			sZ_
	}
	val[0] = cY_*cZ_ + sY_*sX_*sZ_;
	val[1] = cX_*sZ_;
	val[2] = sY_*cZ_ - cY_*sX_*sZ_;
	val[4] = -cY_*sZ_ + sY_*sX_*cZ_;
	val[5] = cX_*cZ_;
	val[6] = -sY_*sZ_ - cY_*sX_*cZ_;
	val[8] = -sY_*cX_;
	val[9] = sX_;
	val[10] = cY_*cX_;
	val[3] = _0f;
	val[7] = _0f;
	val[11] = _0f;
	val[12] = _0f;
	val[13] = _0f;
	val[14] = _0f;
	val[15] = _1f;
}

inline void									TexProject::mat4::makeProjectionPerspective(float32 FOV,float32 aspect,float32 zNear,float32 zFar)
{
	FOV = FOV * _PIdev180f;
	float32 f = 1.0f / tanf(FOV*_dev2f);
	float32 A = (zFar + zNear) / (zNear - zFar);
	float32 B = (2.0f * zFar * zNear) / (zNear - zFar);

	val[0] = f / aspect;
	val[5] = f;
	val[10] = A;
	val[11] = B;
	val[14] = -_1f;
	val[1] = _0f;
	val[2] = _0f;
	val[3] = _0f;
	val[4] = _0f;
	val[6] = _0f;
	val[7] = _0f;
	val[8] = _0f;
	val[9] = _0f;
	val[12] = _0f;
	val[13] = _0f;
	val[15] = _0f;
}
inline void									TexProject::mat4::makeProjectionPerspectiveInverse(float32 FOV,float32 aspect,float32 zNear,float32 zFar)
{
	FOV = FOV * _PIdev180f;
	float32 f = 1 / tanf(FOV*0.5f);
	float32 A = (zFar + zNear) / (zNear - zFar);
	float32 B = (2.0f * zFar * zNear) / (zNear - zFar);

	val[0] = aspect / f;
	val[5] = 1.0f / f;
	val[10] = 0.0f;
	val[11] = -1.0f;
	val[14] = 1.0f / B;
	val[15] = A / B;
	val[1] = 0.0f;
	val[2] = 0.0f;
	val[3] = 0.0f;
	val[4] = 0.0f;
	val[6] = 0.0f;
	val[7] = 0.0f;
	val[8] = 0.0f;
	val[9] = 0.0f;
	val[10] = 0.0f;
	val[12] = 0.0f;
	val[13] = 0.0f;
}
inline void									TexProject::mat4::makeProjectionOrthogonal(float32 left,float32 right,float32 bottom,float32 top,float32 back,float32 front)
{
	float32	dx = _1f / (right - left),
		dy = _1f / (top-bottom),
		dz = _1f / (front - back);
	val[0] = _2f * dx;
	val[1] = _0f;
	val[2] = _0f;
	val[3] =  - (right + left) * dx;
	val[4] = _0f;
	val[5] = _2f * dy;
	val[6] = _0f;
	val[7] =  - (top + bottom) * dy;
	val[8] = _0f;
	val[9] = _0f;
	val[10] = - _2f * dz;
	val[11] =  - (front + back) * dz;
	val[12] = _0f;
	val[13] = _0f;
	val[14] = _0f;
	val[15] =  _1f;
}
inline void									TexProject::mat4::makeProjectionOrthogonalInverse(float32 left,float32 right,float32 bottom,float32 top,float32 back,float32 front)
{
}
#pragma endregion
#pragma region functions;
inline TexProject::float32					TexProject::rnd()
{
	return static_cast <float32> (rand()) / static_cast <float32> (RAND_MAX);
}
inline TexProject::float32					TexProject::rnd(float32 highLimit)
{
	return static_cast <float32> (rand()) / (static_cast <float32> (RAND_MAX/highLimit));
}
inline TexProject::float32					TexProject::rnd(float32 lowLimit,float32 highLimit)
{
	return lowLimit + static_cast <float32> (rand()) / (static_cast <float32> (RAND_MAX/(highLimit-lowLimit)));
}

inline TexProject::int32					TexProject::clamp(int32 val,int32 minVal,int32 maxVal)
{
	return (val < minVal) ? (minVal) : ((val > maxVal) ? maxVal : val);
}
inline TexProject::float32					TexProject::clamp(float32 val,float32 minVal,float32 maxVal)
{
	return (val < minVal) ? (minVal) : ((val > maxVal) ? maxVal : val);
}
inline TexProject::vec2						TexProject::clamp(const vec2& val,const vec2& minVal,const vec2& maxVal)
{
	return vec2
	(
		clamp(val.x,minVal.x,maxVal.x),
		clamp(val.y,minVal.y,maxVal.y)
	);
}
inline TexProject::vec3						TexProject::clamp(const vec3& val,const vec3& minVal,const vec3& maxVal)
{
	return vec3
	(
		clamp(val.x,minVal.x,maxVal.x),
		clamp(val.y,minVal.y,maxVal.y),
		clamp(val.z,minVal.z,maxVal.z)
	);
}
inline TexProject::vec4						TexProject::clamp(const vec4& val,const vec4& minVal,const vec4& maxVal)
{
	return vec4
	(
		clamp(val.x,minVal.x,maxVal.x),
		clamp(val.y,minVal.y,maxVal.y),
		clamp(val.z,minVal.z,maxVal.z),
		clamp(val.w,minVal.w,maxVal.w)
	);
}

inline TexProject::float32					TexProject::wrap(float32 val,float32 minVal,float32 maxVal)
{
	return val - floor((val - minVal) / (maxVal - minVal))*(maxVal - minVal);
}

inline TexProject::float32					TexProject::degrees(const float32 rads)
{
	return rads * _180devPIf;
}
inline TexProject::float32					TexProject::radians(const float32 degs)
{
	return degs * _PIdev180f;
}

inline TexProject::float32					TexProject::sinDg(const float32 in)
{
	return sin(radians(in));
}
inline TexProject::float32					TexProject::cosDg(const float32 in)
{
	return cos(radians(in));
}
inline TexProject::float32					TexProject::tanDg(const float32 in)
{
	return tan(radians(in));
}
inline TexProject::float32					TexProject::asinDg(const float32 in)
{
	return degrees(asin(in));
}
inline TexProject::float32					TexProject::acosDg(const float32 in)
{
	return degrees(acos(in));
}
inline TexProject::float32					TexProject::atanDg(const float32 in)
{
	return degrees(atan(in));
}


inline TexProject::float32					TexProject::dot(const vec2& a,const vec2& b)
{
	return a.x * b.x + a.y * b.y;
}
inline TexProject::float32					TexProject::dot(const vec3& a,const vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline TexProject::float32					TexProject::dot(const vec4& a,const vec4& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
}

inline TexProject::float32					TexProject::sqr(const vec2& a)
{
	//return dot(a,a); bad!
	return a.x * a.x + a.y * a.y;
}

inline TexProject::float32					TexProject::sqr(const vec3& a)
{
	return a.x * a.x + a.y * a.y + a.z * a.z;
}

inline TexProject::float32					TexProject::sqr(const vec4& a)
{
	return a.x * a.x + a.y * a.y + a.z * a.z + a.w * a.w;
}

inline TexProject::float32					TexProject::length(const vec2& a)
{
	return sqrt(sqr(a));
}

inline TexProject::float32					TexProject::length(const vec3& a)
{
	return sqrt(sqr(a));
}

inline TexProject::float32					TexProject::length(const vec4& a)
{
	return sqrt(sqr(a));
}

inline TexProject::vec2						TexProject::normalize(const vec2& a)
{
	return a / length(a);
}

inline TexProject::vec3						TexProject::normalize(const vec3& a)
{
	return a / length(a);
}

inline TexProject::vec4						TexProject::normalize(const vec4& a)
{
	return a / length(a);
}

inline TexProject::float32					TexProject::dist(const vec2& a,const vec2& b)
{
	return length(a-b);
}

inline TexProject::float32					TexProject::dist(const vec3& a,const vec3& b)
{
	return length(a - b);
}

inline TexProject::float32					TexProject::dist(const vec4& a,const vec4& b)
{
	return length(a - b);
}

inline TexProject::vec3						TexProject::cross(const vec3& a,const vec3& b)
{
	return vec3(
		a.y*b.z - a.z*b.y,
		a.z*b.x - a.x*b.z,
		a.x*b.y - a.y*b.x
		);
}

inline TexProject::float32					TexProject::getAng(const vec2& a,const vec2& b)
{
	return acosDg(dot(a,b) / (length(a)*length(b)));
}
inline TexProject::float32					TexProject::getAng(const vec2& a)
{
	return degrees(atan2(a.x,a.y));
}
inline TexProject::vec2						TexProject::getAng(const vec3& a)
{
	vec2 out;
	out.x = getAng(vec2(-a.y,sqrt(a.x*a.x + a.z*a.z)));
	out.y = getAng(vec2(a.x,a.z));
	return out;
}
inline TexProject::vec3						TexProject::getAng(const mat3& mat)
{
	vec3	result(0.0f),v_xz(0.0f),v_y(0.0f);

	v_xz = mat * vec3(0.0f,0.0f,1.0f);

	auto t = getAng(v_xz);

	result.x = t.x;
	result.y = t.y;

	v_y = (mat * mat3::rotateYXZ(vec3(-result.x,-result.y,0.0f))) * vec3(0.0f,1.0f,0.0f);

	result.z = degrees(atan2(v_y.x,v_y.y));

	return result;
}
inline TexProject::vec3						TexProject::getAng(const mat4& mat)
{
	vec3	result,
		v_xz,v_y;

	v_xz = mat * vec3(0.0f,0.0f,1.0f);

	result.x = degrees(atan2(-v_xz.y,sqrt(v_xz.x*v_xz.x + v_xz.z*v_xz.z)));
	result.y = degrees(atan2(v_xz.x,v_xz.z));

	v_y = (mat * mat4::rotateYXZ(vec3(-result.x,-result.y,0.0f))) * vec3(0.0f,1.0f,0.0f);

	result.z = degrees(atan2(v_y.x,v_y.y));

	return result;
}

inline TexProject::float32					TexProject::bezier(float32 t1,float32 t2,float32 t)
{
	return t1*(1.0f-t) + t2*t;
}
inline TexProject::vec2						TexProject::bezier(const vec2& t1,const vec2& t2,float32 t)
{
	return t1*(1.0f-t) + t2*t;
}
inline TexProject::vec3						TexProject::bezier(const vec3& t1,const vec3& t2,float32 t)
{
	return t1*(1.0f-t) + t2*t;
}
inline TexProject::vec4						TexProject::bezier(const vec4& t1,const vec4& t2,float32 t)
{
	return t1*(1.0f-t) + t2*t;
}
inline TexProject::vec4						TexProject::bezier(const vec4& t1,const vec4& t2,const vec4& t)
{
	return t1 + (t2 - t1)*t;
}
inline TexProject::float32					TexProject::bezier(float32 t1,float32 t2,float32 t3,float32 t)
{
	return bezier(bezier(t1,t2,t),bezier(t2,t3,t),t);
}
inline TexProject::vec2						TexProject::bezier(const vec2& t1,const vec2& t2,const vec2& t3,float32 t)
{
	return bezier(bezier(t1,t2,t),bezier(t2,t3,t),t);
}
inline TexProject::vec3						TexProject::bezier(const vec3& t1,const vec3& t2,const vec3& t3,float32 t)
{
	return bezier(bezier(t1,t2,t),bezier(t2,t3,t),t);
}
inline TexProject::vec4						TexProject::bezier(const vec4& t1,const vec4& t2,const vec4& t3,float32 t)
{
	return bezier(bezier(t1,t2,t),bezier(t2,t3,t),t);
}
inline TexProject::float32					TexProject::bezier(float32 t1,float32 t2,float32 t3,float32 t4,float32 t)
{
	return bezier(bezier(t1,t2,t3,t),bezier(t2,t3,t4,t),t);
}
inline TexProject::vec2						TexProject::bezier(const vec2& t1,const vec2& t2,const vec2& t3,const vec2& t4,float32 t)
{
	return bezier(bezier(t1,t2,t3,t),bezier(t2,t3,t4,t),t);
}
inline TexProject::vec3						TexProject::bezier(const vec3& t1,const vec3& t2,const vec3& t3,const vec3& t4,float32 t)
{
	return bezier(bezier(t1,t2,t3,t),bezier(t2,t3,t4,t),t);
}
inline TexProject::vec4						TexProject::bezier(const vec4& t1,const vec4& t2,const vec4& t3,const vec4& t4,float32 t)
{
	return bezier(bezier(t1,t2,t3,t),bezier(t2,t3,t4,t),t);
}
template <class _Pr>
void										TexProject::bezier(const vec2& t1,const vec2& t2,_Pr pred,const uint32 accuracy)
{
	float32 t,nt;
	for(uint32 i = 0; i < accuracy; ++i)
	{
		t = float32(i)/accuracy;
		nt = float32(i+1)/accuracy;

		pred(bezier(t1,t2,t),bezier(t1,t2,nt));
	}
}
template <class _Pr>
void										TexProject::bezier(const vec2& t1,const vec2& t2,const vec2& t3,_Pr pred,const uint32 accuracy)
{
	float32 t,nt;
	for(uint32 i = 0; i < accuracy; ++i)
	{
		t = float32(i)/accuracy;
		nt = float32(i+1)/accuracy;

		pred(bezier(t1,t2,t3,t),bezier(t1,t2,t3,nt));
	}
}
template <class _Pr>
void										TexProject::bezier(const vec2& t1,const vec2& t2,const vec2& t3,const vec2& t4,_Pr pred,const uint32 accuracy)
{
	float32 t,nt;
	for(uint32 i = 0; i < accuracy; ++i)
	{
		t = float32(i)/accuracy;
		nt = float32(i+1)/accuracy;

		pred(bezier(t1,t2,t3,t4,t),bezier(t1,t2,t3,t4,nt));
	}
}
#pragma endregion











