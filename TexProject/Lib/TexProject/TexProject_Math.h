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
		inline								vec2(const float32 x_, const float32 y_);			  
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
																								  
		inline vec2							operator + (const vec2& a) const;					  
		inline vec2							operator - (const vec2& a) const;					  
		inline vec2							operator * (const vec2& a) const;					  
		inline vec2							operator / (const vec2& a) const;					  
																								  
		friend inline vec2					operator + (const vec2& a, const float32 b);		  
		friend inline vec2					operator - (const vec2& a, const float32 b);		  
		friend inline vec2					operator * (const vec2& a, const float32 b);		  
		friend inline vec2					operator / (const vec2& a, const float32 b);		  
																								  
		friend inline vec2					operator + (const float32 a, const vec2& b);		  
		friend inline vec2					operator - (const float32 a, const vec2& b);		  
		friend inline vec2					operator * (const float32 a, const vec2& b);		  
		friend inline vec2					operator / (const float32 a, const vec2& b);		  

		inline float32						length() const;										  
		inline float32						sqr();												  
		inline void							normalize();										  
	};
	struct ivec2
	{
		int32								x, y;

		inline								ivec2();											 
		explicit inline						ivec2(const int32 a_);								 
		inline								ivec2(const int32 x_, const int32 y_);				 
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
		uint32								x, y;

		inline								uvec2();											 
		inline								uvec2(const uvec2&) = default;						 
		explicit inline						uvec2(const uint32 a_);								 
		inline								uvec2(const uint32 x_, const uint32 y_);			 
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
																								 
		inline uvec2						operator + (const uvec2& a) const;					 
		inline uvec2						operator - (const uvec2& a) const;					 
		inline uvec2						operator * (const uvec2& a) const;					 
		inline uvec2						operator / (const uvec2& a) const;					 
																								 
		friend inline uvec2					operator + (const uvec2& a, const uint32 b);		 
		friend inline uvec2					operator - (const uvec2& a, const uint32 b);		 
		friend inline uvec2					operator * (const uvec2& a, const uint32 b);		 
		friend inline uvec2					operator / (const uvec2& a, const uint32 b);		 
																								 
		friend inline uvec2					operator + (const uint32 a, const uvec2& b);		 
		friend inline uvec2					operator - (const uint32 a, const uvec2& b);		 
		friend inline uvec2					operator * (const uint32 a, const uvec2& b);		 
		friend inline uvec2					operator / (const uint32 a, const uvec2& b);		 

		//inline uvec2						operator + (const uint32& a) const;
		//inline ivec2						operator - (const uint32& a) const;
		//inline ivec2						operator * (const uint32& a) const;
		//inline ivec2						operator / (const uint32& a) const;

	};
	struct vec3
	{
		float32			x, y, z;

		inline								vec3();															  
		explicit inline						vec3(const float32 a_);											  
		inline								vec3(const float32 x_, const float32 y_, const float32 z_);		  
		explicit inline						vec3(const vec2& xy_, const float32 z_);						  
		explicit inline						vec3(const float32 x_, const vec2& yz_);						  
		inline								vec3(const vec3& a) = default;									  
		explicit inline						vec3(const ivec3& a);											  
		explicit inline						vec3(const uvec3& a);											  
		inline								~vec3() = default;												  
																											  
		inline vec3&						operator = (const vec3& a) = default;							  
		inline vec3&						operator = (const float32 source);								  
		inline vec3&						operator = (const uvec3& source);								  
		inline vec3&						operator = (const ivec3& source);								  
																											  
		inline vec3&						operator += (const vec3& a);									  
		inline vec3&						operator -= (const vec3& a);									  
		inline vec3&						operator *= (const vec3& a);									  
		inline vec3&						operator /= (const vec3& a);									  
																											  
		inline vec3							operator + (const vec3& a) const;								  
		inline vec3							operator - (const vec3& a) const;								  
		inline vec3							operator * (const vec3& a) const;								  
		inline vec3							operator / (const vec3& a) const;								  
																											  
		friend inline vec3					operator + (const vec3& a, const float32 b);					  
		friend inline vec3					operator - (const vec3& a, const float32 b);					  
		friend inline vec3					operator * (const vec3& a, const float32 b);					  
		friend inline vec3					operator / (const vec3& a, const float32 b);					  
																											  
		friend inline vec3					operator + (const float32 a, const vec3& b);					  
		friend inline vec3					operator - (const float32 a, const vec3& b);					  
		friend inline vec3					operator * (const float32 a, const vec3& b);					  
		friend inline vec3					operator / (const float32 a, const vec3& b);					  
																											  
		inline vec2							xy() const;														  
		inline vec2							xz() const;														  
		inline vec2							yz() const;														  
																											  
		inline float32						length() const;													  
		inline float32						sqr();															  
		inline void							normalize();													  
	};
	struct ivec3
	{
		int32			x, y, z;

		inline								ivec3();															
		explicit inline						ivec3(const int32 a_);												
		inline								ivec3(const int32 x_, const int32 y_, const int32 z_);				
		explicit inline						ivec3(const ivec2& xy_, const int32 z_);							
		explicit inline						ivec3(const int32 x_, const ivec2& yz_);							
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
																												
		inline ivec3						operator + (const ivec3& a) const;								  	
		inline ivec3						operator - (const ivec3& a) const;								  	
		inline ivec3						operator * (const ivec3& a) const;								  	
		inline ivec3						operator / (const ivec3& a) const;								  	
																												
		friend inline ivec3					operator + (const ivec3& a, const int32 b);					  		
		friend inline ivec3					operator - (const ivec3& a, const int32 b);					  		
		friend inline ivec3					operator * (const ivec3& a, const int32 b);					  		
		friend inline ivec3					operator / (const ivec3& a, const int32 b);					  		
					  																							
		friend inline ivec3					operator + (const int32 a, const ivec3& b);					  		
		friend inline ivec3					operator - (const int32 a, const ivec3& b);					  		
		friend inline ivec3					operator * (const int32 a, const ivec3& b);					  		
		friend inline ivec3					operator / (const int32 a, const ivec3& b);					  		
																												
		inline ivec2						xy() const;														  	
		inline ivec2						xz() const;														  	
		inline ivec2						yz() const;														  	
	};
	struct uvec3
	{
		uint32			x, y, z;

		inline								uvec3();													 
		inline explicit						uvec3(const uint32 a_);										 
		inline								uvec3(const uint32 x_, const uint32 y_, const uint32 z_);	 
		explicit inline						uvec3(const uvec2& xy_, const uint32 z_);					 
		explicit inline						uvec3(const uint32 x_, const uvec2& yz_);					 
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
																										 
		inline uvec3						operator + (const uvec3& a) const;							 
		inline uvec3						operator - (const uvec3& a) const;							 
		inline uvec3						operator * (const uvec3& a) const;							 
		inline uvec3						operator / (const uvec3& a) const;							 
																										 
		friend inline uvec3					operator + (const uvec3& a, const uint32 b);				 
		friend inline uvec3					operator - (const uvec3& a, const uint32 b);				 
		friend inline uvec3					operator * (const uvec3& a, const uint32 b);				 
		friend inline uvec3					operator / (const uvec3& a, const uint32 b);				 
																										 
		friend inline uvec3					operator + (const uint32 a, const uvec3& b);				 
		friend inline uvec3					operator - (const uint32 a, const uvec3& b);				 
		friend inline uvec3					operator * (const uint32 a, const uvec3& b);				 
		friend inline uvec3					operator / (const uint32 a, const uvec3& b);				 
																										 
		inline uvec2						xy() const;													 
		inline uvec2						xz() const;													 
		inline uvec2						yz() const;													 
	};
	struct vec4
	{
		float32			x, y, z, w;

		inline								vec4() = default;																   
		inline								vec4(const vec3& xyz_, const float32 w_);										   
		inline								vec4(const float32 x_, const vec3& yzw_);										   
		inline								vec4(const vec2& xy_, const vec2& zw_);											   
		inline								vec4(const vec2& xy_, const float32 z_, const float32 w_);						   
		inline								vec4(const float32 x_, const vec2& yz_, const float32 w_);						   
		inline								vec4(const float32 x_, const float32 y_, const vec2& zw_);						   
		inline								vec4(const float32 x_, const float32 y_, const float32 z_, const float32 w_);	   
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
																															   
		inline vec4							operator + (const vec4& a) const;												   
		inline vec4							operator - (const vec4& a) const;												   
		inline vec4							operator * (const vec4& a) const;												   
		inline vec4							operator / (const vec4& a) const;												   
																															   
		friend inline vec4					operator + (const vec4& a, const float32 b);									   
		friend inline vec4					operator - (const vec4& a, const float32 b);									   
		friend inline vec4					operator * (const vec4& a, const float32 b);									   
		friend inline vec4					operator / (const vec4& a, const float32 b);									   
																															   
		friend inline vec4					operator + (const float32 a, const vec4& b);									   
		friend inline vec4					operator - (const float32 a, const vec4& b);									   
		friend inline vec4					operator * (const float32 a, const vec4& b);									   
		friend inline vec4					operator / (const float32 a, const vec4& b);									   
																															   
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
		int32			x, y, z, w;

		inline								ivec4() = default;																	
		inline								ivec4(const ivec3& xyz_, const int32 w_);											
		inline								ivec4(const int32 x_, const ivec3& yzw_);											
		inline								ivec4(const ivec2& xy_, const ivec2& zw_);											
		inline								ivec4(const ivec2& xy_, const int32 z_, const int32 w_);							
		inline								ivec4(const int32 x_, const ivec2& yz_, const int32 w_);							
		inline								ivec4(const int32 x_, const int32 y_, const ivec2& zw_);							
		inline								ivec4(const int32 x_, const int32 y_, const int32 z_, const int32 w_);				
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
																																
		inline ivec4						operator + (const ivec4& a) const;													
		inline ivec4						operator - (const ivec4& a) const;													
		inline ivec4						operator * (const ivec4& a) const;													
		inline ivec4						operator / (const ivec4& a) const;													
																																
		friend inline ivec4					operator + (const ivec4& a, const int32 b);											
		friend inline ivec4					operator - (const ivec4& a, const int32 b);											
		friend inline ivec4					operator * (const ivec4& a, const int32 b);											
		friend inline ivec4					operator / (const ivec4& a, const int32 b);											
																																
		friend inline ivec4					operator + (const int32 a, const ivec4& b);											
		friend inline ivec4					operator - (const int32 a, const ivec4& b);											
		friend inline ivec4					operator * (const int32 a, const ivec4& b);											
		friend inline ivec4					operator / (const int32 a, const ivec4& b);											
																																
		inline ivec3						xyz() const;																		
		inline ivec3						xyw() const;																		
		inline ivec3						xzw() const;																		
		inline ivec3						yzw() const;																		
	};
	struct uvec4
	{
		uint32			x, y, z, w;

		inline								uvec4() = default;																	   
		inline								uvec4(const uvec3& xyz_, const uint32 w_);											   
		inline								uvec4(const uint32 x_, const uvec3& yzw_);											   
		inline								uvec4(const uvec2& xy_, const uvec2& zw_);											   
		inline								uvec4(const uvec2& xy_, const uint32 z_, const uint32 w_);							   
		inline								uvec4(const uint32 x_, const uvec2& yz_, const uint32 w_);							   
		inline								uvec4(const uint32 x_, const uint32 y_, const uvec2& zw_);							   
		inline								uvec4(const uint32 x_, const uint32 y_, const uint32 z_, const uint32 w_);			   
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
																																   
		inline uvec4						operator + (const uvec4& a) const;													   
		inline uvec4						operator - (const uvec4& a) const;													   
		inline uvec4						operator * (const uvec4& a) const;													   
		inline uvec4						operator / (const uvec4& a) const;													   
																																   
		friend inline uvec4					operator + (const uvec4& a, const uint32 b);										   
		friend inline uvec4					operator - (const uvec4& a, const uint32 b);										   
		friend inline uvec4					operator * (const uvec4& a, const uint32 b);										   
		friend inline uvec4					operator / (const uvec4& a, const uint32 b);										   
																																   
		friend inline uvec4					operator + (const uint32 a, const uvec4& b);										   
		friend inline uvec4					operator - (const uint32 a, const uvec4& b);										   
		friend inline uvec4					operator * (const uint32 a, const uvec4& b);										   
		friend inline uvec4					operator / (const uint32 a, const uvec4& b);										   
																																   
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
	inline float32							dot(const vec2& a, const vec2& b);
	/*Скалярний добуток vec3*/
	inline float32							dot(const vec3& a, const vec3& b);
	/*Скалярний добуток vec4*/
	inline float32							dot(const vec4& a, const vec4& b);

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
	inline float32							dist(const vec3& a, const vec3& b);
	/*Відстань між двома vec4*/
	inline float32							dist(const vec4& a, const vec4& b);

	/*Векторний добуток vec3*/
	inline vec3								cross(const vec3& a,const vec3& b);

	inline float32							getAng(const vec2& a,const vec2& b);

}


// vec2
inline										TexProject::vec2::vec2()
{
}
inline										TexProject::vec2::vec2(const float32 a_) :
	x(a_), 
	y(a_)
{
}
inline										TexProject::vec2::vec2(const float32 x_, const float32 y_) :
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


inline TexProject::vec2						TexProject::vec2::operator + (const vec2& a) const
{
	return vec2	(
					x + a.x,
					y + a.y
				);
}
inline TexProject::vec2						TexProject::vec2::operator - (const vec2& a) const
{
	return vec2	(
					x - a.x,
					y - a.y
				);
}
inline TexProject::vec2						TexProject::vec2::operator * (const vec2& a) const
{
	return vec2	(
					x * a.x,
					y * a.y
				);
}
inline TexProject::vec2						TexProject::vec2::operator / (const vec2& a) const
{
	return vec2	(
					x / a.x,
					y / a.y
				);
}

inline TexProject::vec2						TexProject::operator + (const vec2& a, const float32 b)
{
	return vec2	(
					a.x + b,
					a.y + b
				);
}
inline TexProject::vec2						TexProject::operator - (const vec2& a, const float32 b)
{
	return vec2	(
					a.x - b,
					a.y - b
				);
}
inline TexProject::vec2						TexProject::operator * (const vec2& a, const float32 b)
{
	return vec2	(
					a.x * b,
					a.y * b
				);
}
inline TexProject::vec2						TexProject::operator / (const vec2& a, const float32 b)
{
	static float32 t;
	t = 1.0f/b;
	return vec2	(
					a.x * t,
					a.y * t
				);
}

inline TexProject::vec2						TexProject::operator + (const float32 a, const vec2& b)
{
	return vec2	(
					a + b.x,
					a + b.y
				);
}
inline TexProject::vec2						TexProject::operator - (const float32 a, const vec2& b)
{
	return vec2	(
					a - b.x,
					a - b.y
				);
}
inline TexProject::vec2						TexProject::operator * (const float32 a, const vec2& b)
{
	return vec2	(
					a * b.x,
					a * b.y
				);
}
inline TexProject::vec2						TexProject::operator / (const float32 a, const vec2& b)
{
	return vec2	(
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

// ivec2
inline										TexProject::ivec2::ivec2()
{
}
inline										TexProject::ivec2::ivec2(const int32 a_) :
	x(a_),
	y(a_)
{
}
inline										TexProject::ivec2::ivec2(const int32 x_, const int32 y_) :
	x(x_),
	y(y_)
{
}

inline										TexProject::ivec2::ivec2(const vec2& a) :
	x(int32(a.x)),
	y(int32(a.y))
{
}

inline										TexProject::ivec2::ivec2(const uvec2& a) :
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

inline TexProject::ivec2					TexProject::operator + (const ivec2& a, const int32 b)
{
	return ivec2(
					a.x + b,
					a.y + b
				);
}
inline TexProject::ivec2					TexProject::operator - (const ivec2& a, const int32 b)
{
	return ivec2(
					a.x - b,
					a.y - b
				);
}
inline TexProject::ivec2					TexProject::operator * (const ivec2& a, const int32 b)
{
	return ivec2(
					a.x * b,
					a.y * b
				);
}
inline TexProject::ivec2					TexProject::operator / (const ivec2& a, const int32 b)
{
	return ivec2(
					a.x / b,
					a.y / b
				);
}

/*TexProject::ivec2					TexProject::operator + (const ivec2& a,const uvec2& b)
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
}*/

inline TexProject::ivec2					TexProject::operator + (const int32 a, const ivec2& b)
{
	return ivec2(
					a + b.x,
					a + b.y
				);
}
inline TexProject::ivec2					TexProject::operator - (const int32 a, const ivec2& b)
{
	return ivec2(
					a - b.x,
					a - b.y
				);
}
inline TexProject::ivec2					TexProject::operator * (const int32 a, const ivec2& b)
{
	return ivec2(
					a * b.x,
					a * b.y
				);
}
inline TexProject::ivec2					TexProject::operator / (const int32 a, const ivec2& b)
{
	return ivec2(
					a / b.x,
					a / b.y
				);
}

// uvec2
inline TexProject::uvec2::uvec2()
{
}
inline										TexProject::uvec2::uvec2(const uint32 a_):
	x(a_),
	y(a_)
{
}
inline										TexProject::uvec2::uvec2(const uint32 x_, const uint32 y_) :
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
inline TexProject::uvec2					TexProject::operator + (const uvec2& a, const uint32 b)
{
	return uvec2(
					a.x + b,
					a.y + b
				);
}
inline TexProject::uvec2					TexProject::operator - (const uvec2& a, const uint32 b)
{
	return uvec2(
					a.x - b,
					a.y - b
				);
}
inline TexProject::uvec2					TexProject::operator * (const uvec2& a, const uint32 b)
{
	return uvec2(
					a.x * b,
					a.y * b
				);
}
inline TexProject::uvec2					TexProject::operator / (const uvec2& a, const uint32 b)
{
	return uvec2(
					a.x / b,
					a.y / b
				);
}
inline TexProject::uvec2					TexProject::operator + (const uint32 a, const uvec2& b)
{
	return uvec2(
					a + b.x,
					a + b.y
				);
}
inline TexProject::uvec2					TexProject::operator - (const uint32 a, const uvec2& b)
{
	return uvec2(
					a - b.x,
					a - b.y
				);
}
inline TexProject::uvec2					TexProject::operator * (const uint32 a, const uvec2& b)
{
	return uvec2(
					a * b.x,
					a * b.y
				);
}
inline TexProject::uvec2					TexProject::operator / (const uint32 a, const uvec2& b)
{
	return uvec2(
					a / b.x,
					a / b.y
				);
}

/*TexProject::uvec2							TexProject::uvec2::operator + (const uint32& a) const
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
}*/


// vec3
inline										TexProject::vec3::vec3()
{
}
inline										TexProject::vec3::vec3(const float32 a_) :
	x(a_), 
	y(a_), 
	z(a_)
{
}
inline										TexProject::vec3::vec3(const float32 x_, const float32 y_, const float32 z_) :
	x(x_), 
	y(y_), 
	z(z_)
{
}

inline										TexProject::vec3::vec3(const vec2& xy_, const float32 z_) :
	x(xy_.x), 
	y(xy_.y), 
	z(z_)
{
}

inline										TexProject::vec3::vec3(const float32 x_, const vec2& yz_) :
	x(x_), 
	y(yz_.x), 
	z(yz_.y)
{
}
inline										TexProject::vec3::vec3(const ivec3& a) :
	x(float32(a.x)),
	y(float32(a.y)),
	z(float32(a.z))
{
}
inline										TexProject::vec3::vec3(const uvec3& a) :
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

inline TexProject::vec3						TexProject::operator + (const vec3& a, const float32 b)
{
	return vec3(
					a.x + b,
					a.y + b,
					a.z + b
				);
}
inline TexProject::vec3						TexProject::operator - (const vec3& a, const float32 b)
{
	return vec3(
					a.x - b,
					a.y - b,
					a.z - b
				);
}
inline TexProject::vec3						TexProject::operator * (const vec3& a, const float32 b)
{
	return vec3(
					a.x * b,
					a.y * b,
					a.z * b
				);
}
inline TexProject::vec3						TexProject::operator / (const vec3& a, const float32 b)
{
	return vec3(
		a.x / b,
		a.y / b,
		a.z / b
		);
}

inline TexProject::vec3						TexProject::operator + (const float32 a, const vec3& b)
{
	return vec3(
					a + b.x,
					a + b.y,
					a + b.z
				);
}
inline TexProject::vec3						TexProject::operator - (const float32 a, const vec3& b)
{
	return vec3(
					a - b.x,
					a - b.y,
					a - b.z
				);
}
inline TexProject::vec3						TexProject::operator * (const float32 a, const vec3& b)
{
	return vec3(
					a * b.x,
					a * b.y,
					a * b.z
				);
}
inline TexProject::vec3						TexProject::operator / (const float32 a, const vec3& b)
{
	return vec3(
					a / b.x,
					a / b.y,
					a / b.z
				);
}
inline TexProject::vec2						TexProject::vec3::xy() const
{
	return vec2 (
					x,
					y
				);
}

inline TexProject::vec2						TexProject::vec3::xz() const
{
	return vec2 (
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

// ivec3;
inline										TexProject::ivec3::ivec3()
{
}
inline										TexProject::ivec3::ivec3(const int32 a_) :
	x(a_),
	y(a_),
	z(a_)
{
}
inline										TexProject::ivec3::ivec3(const int32 x_, const int32 y_, const int32 z_) :
	x(x_),
	y(y_),
	z(z_)
{
}
inline										TexProject::ivec3::ivec3(const ivec2& xy_, const int32 z_) :
	x(xy_.x),
	y(xy_.y),
	z(z_)
{
}
inline										TexProject::ivec3::ivec3(const int32 x_, const ivec2& yz_) :
	x(x_),
	y(yz_.x),
	z(yz_.y)
{
}
inline										TexProject::ivec3::ivec3(const vec3& a) :
	x(int32(a.x)),
	y(int32(a.y)),
	z(int32(a.z))
{
}
inline										TexProject::ivec3::ivec3(const uvec3& a) :
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

inline TexProject::ivec3					TexProject::operator + (const ivec3& a, const int32 b)
{
	return ivec3(
					a.x + b,
					a.y + b,
					a.z + b
				);
}
inline TexProject::ivec3					TexProject::operator - (const ivec3& a, const int32 b)
{
	return ivec3(
					a.x - b,
					a.y - b,
					a.z - b
				);
}
inline TexProject::ivec3					TexProject::operator * (const ivec3& a, const int32 b)
{
	return ivec3(
					a.x * b,
					a.y * b,
					a.z * b
				);
}
inline TexProject::ivec3					TexProject::operator / (const ivec3& a, const int32 b)
{
	return ivec3(
					a.x / b,
					a.y / b,
					a.z / b
				);
}

inline TexProject::ivec3					TexProject::operator + (const int32 a, const ivec3& b)
{
	return ivec3(
					a + b.x,
					a + b.y,
					a + b.z
				);
}
inline TexProject::ivec3					TexProject::operator - (const int32 a, const ivec3& b)
{
	return ivec3(
					a - b.x,
					a - b.y,
					a - b.z
				);
}
inline TexProject::ivec3					TexProject::operator * (const int32 a, const ivec3& b)
{
	return ivec3(
					a * b.x,
					a * b.y,
					a * b.z
				);
}
inline TexProject::ivec3					TexProject::operator / (const int32 a, const ivec3& b)
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

// uvec3
inline										TexProject::uvec3::uvec3()
{
}
inline										TexProject::uvec3::uvec3(const uint32 a_) :
	x(a_), 
	y(a_), 
	z(a_)
{
}
inline										TexProject::uvec3::uvec3(const uint32 x_, const uint32 y_, const uint32 z_) :
	x(x_),
	y(y_),
	z(z_)
{
}

inline										TexProject::uvec3::uvec3(const uvec2& xy_, const uint32 z_) :
	x(xy_.x),
	y(xy_.y),
	z(z_)
{
}
inline										TexProject::uvec3::uvec3(const uint32 x_, const uvec2& yz_) :
	x(x_),
	y(yz_.x),
	z(yz_.y)
{
}
inline										TexProject::uvec3::uvec3(const vec3& a) :
	x(uint32(a.x)),
	y(uint32(a.y)),
	z(uint32(a.z))
{
}
inline										TexProject::uvec3::uvec3(const ivec3& a) :
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

inline TexProject::uvec3					TexProject::operator + (const uvec3& a, const uint32 b)
{
	return uvec3(
					a.x + b,
					a.y + b,
					a.z + b
				);
}
inline TexProject::uvec3					TexProject::operator - (const uvec3& a, const uint32 b)
{
	return uvec3(
					a.x - b,
					a.y - b,
					a.z - b
				);
}
inline TexProject::uvec3					TexProject::operator * (const uvec3& a, const uint32 b)
{
	return uvec3(
					a.x * b,
					a.y * b,
					a.z * b
				);
}
inline TexProject::uvec3					TexProject::operator / (const uvec3& a, const uint32 b)
{
	return uvec3(
					a.x / b,
					a.y / b,
					a.z / b
				);
}

inline TexProject::uvec3					TexProject::operator + (const uint32 a, const uvec3& b)
{
	return uvec3(
					a + b.x,
					a + b.y,
					a + b.z
				);
}
inline TexProject::uvec3					TexProject::operator - (const uint32 a, const uvec3& b)
{
	return uvec3(
					a - b.x,
					a - b.y,
					a - b.z
				);
}
inline TexProject::uvec3					TexProject::operator * (const uint32 a, const uvec3& b)
{
	return uvec3(
					a * b.x,
					a * b.y,
					a * b.z
				);
}
inline TexProject::uvec3					TexProject::operator / (const uint32 a, const uvec3& b)
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

// vec4
inline										TexProject::vec4::vec4(const vec3& xyz_, const float32 w_) :
	x(xyz_.x),
	y(xyz_.y),
	z(xyz_.z),
	w(w_)
{
}
inline										TexProject::vec4::vec4(const float32 x_, const vec3& yzw_) :
	x(x_),
	y(yzw_.x),
	z(yzw_.y),
	w(yzw_.z)
{
}
inline										TexProject::vec4::vec4(const vec2& xy_, const vec2& zw_) :
	x(xy_.x),
	y(xy_.y),
	z(zw_.x),
	w(zw_.y)
{
}
inline										TexProject::vec4::vec4(const vec2& xy_, const float32 z_, const float32 w_) :
	x(xy_.x),
	y(xy_.y),
	z(z_),
	w(w_)
{
}
inline										TexProject::vec4::vec4(const float32 x_, const vec2& yz_, const float32 w_) :
	x(x_),
	y(yz_.x),
	z(yz_.y),
	w(w_)
{
}
inline										TexProject::vec4::vec4(const float32 x_, const float32 y_, const vec2& zw_) :
	x(x_),
	y(y_),
	z(zw_.x),
	w(zw_.y)
{
}
inline										TexProject::vec4::vec4(const float32 x_, const float32 y_, const float32 z_, const float32 w_) :
	x(x_),
	y(y_),
	z(z_),
	w(w_)
{
}
inline										TexProject::vec4::vec4(const ivec4& a) :
	x(float32(a.x)),
	y(float32(a.y)),
	z(float32(a.z)),
	w(float32(a.w))
{
}
inline										TexProject::vec4::vec4(const uvec4& a) :
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

inline TexProject::vec4						TexProject::operator + (const vec4& a, const float32 b)
{
	return vec4(
					a.x + b,
					a.y + b,
					a.z + b,
					a.w + b
				);
}
inline TexProject::vec4						TexProject::operator - (const vec4& a, const float32 b)
{
	return vec4(
					a.x - b,
					a.y - b,
					a.z - b,
					a.w - b
				);
}
inline TexProject::vec4						TexProject::operator * (const vec4& a, const float32 b)
{
	return vec4(
					a.x * b,
					a.y * b,
					a.z * b,
					a.w * b
				);
}
inline TexProject::vec4						TexProject::operator / (const vec4& a, const float32 b)
{
	return vec4(
					a.x / b,
					a.y / b,
					a.z / b,
					a.w / b
				);
}

inline TexProject::vec4						TexProject::operator + (const float32 a, const vec4& b)
{
	return vec4(
					a + b.x,
					a + b.y,
					a + b.z,
					a + b.w
				);
}
inline TexProject::vec4						TexProject::operator - (const float32 a, const vec4& b)
{
	return vec4(
					a - b.x,
					a - b.y,
					a - b.z,
					a - b.w
				);
}
inline TexProject::vec4						TexProject::operator * (const float32 a, const vec4& b)
{
	return vec4(
					a * b.x,
					a * b.y,
					a * b.z,
					a * b.w
				);
}
inline TexProject::vec4						TexProject::operator / (const float32 a, const vec4& b)
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

// ivec4;
inline										TexProject::ivec4::ivec4(const ivec3& xyz_, const int32 w_) :
	x(xyz_.x),
	y(xyz_.y),
	z(xyz_.z),
	w(w_)
{
}
inline										TexProject::ivec4::ivec4(const int32 x_, const ivec3& yzw_) :
	x(x_),
	y(yzw_.x),
	z(yzw_.y),
	w(yzw_.z)
{
}
inline										TexProject::ivec4::ivec4(const ivec2& xy_, const ivec2& zw_) :
	x(xy_.x),
	y(xy_.y),
	z(zw_.x),
	w(zw_.y)
{
}
inline										TexProject::ivec4::ivec4(const ivec2& xy_, const int32 z_, const int32 w_) :
	x(xy_.x),
	y(xy_.y),
	z(z_),
	w(w_)
{
}
inline										TexProject::ivec4::ivec4(const int32 x_, const ivec2& yz_, const int32 w_) :
	x(x_),
	y(yz_.x),
	z(yz_.y),
	w(w_)
{
}
inline										TexProject::ivec4::ivec4(const int32 x_, const int32 y_, const ivec2& zw_):
	x(x_),
	y(y_),
	z(zw_.x),
	w(zw_.y)
{
}
inline										TexProject::ivec4::ivec4(const int32 x_, const int32 y_, const int32 z_, const int32 w_) :
	x(x_),
	y(y_),
	z(z_),
	w(w_)
{
}
inline										TexProject::ivec4::ivec4(const vec4& a) :
	x(int32(a.x)),
	y(int32(a.y)),
	z(int32(a.z)),
	w(int32(a.w))
{
}
inline										TexProject::ivec4::ivec4(const uvec4& a) :
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

inline TexProject::ivec4					TexProject::operator + (const ivec4& a, const int32 b)
{
	return ivec4(
					a.x + b,
					a.y + b,
					a.z + b,
					a.w + b
				);
}
inline TexProject::ivec4					TexProject::operator - (const ivec4& a, const int32 b)
{
	return ivec4(
					a.x - b,
					a.y - b,
					a.z - b,
					a.w - b
				);
}
inline TexProject::ivec4					TexProject::operator * (const ivec4& a, const int32 b)
{
	return ivec4(
					a.x * b,
					a.y * b,
					a.z * b,
					a.w * b
				);
}
inline TexProject::ivec4					TexProject::operator / (const ivec4& a, const int32 b)
{
	return ivec4(
					a.x / b,
					a.y / b,
					a.z / b,
					a.w / b
				);
}

inline TexProject::ivec4					TexProject::operator + (const int32 a, const ivec4& b)
{
	return ivec4(
					a + b.x,
					a + b.y,
					a + b.z,
					a + b.w
				);
}
inline TexProject::ivec4					TexProject::operator - (const int32 a, const ivec4& b)
{
	return ivec4(
					a - b.x,
					a - b.y,
					a - b.z,
					a - b.w
				);
}
inline TexProject::ivec4					TexProject::operator * (const int32 a, const ivec4& b)
{
	return ivec4(
					a * b.x,
					a * b.y,
					a * b.z,
					a * b.w
				);
}
inline TexProject::ivec4					TexProject::operator / (const int32 a, const ivec4& b)
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

// uvec4;
inline										TexProject::uvec4::uvec4(const uvec3& xyz_, const uint32 w_) :
	x(xyz_.x),
	y(xyz_.y),
	z(xyz_.z),
	w(w_)
{
}
inline										TexProject::uvec4::uvec4(const uint32 x_, const uvec3& yzw_) :
	x(x_),
	y(yzw_.x),
	z(yzw_.y),
	w(yzw_.z)
{
}
inline										TexProject::uvec4::uvec4(const uvec2& xy_, const uvec2& zw_) :
	x(xy_.x),
	y(xy_.y),
	z(zw_.x),
	w(zw_.y)
{
}
inline										TexProject::uvec4::uvec4(const uvec2& xy_, const uint32 z_, const uint32 w_) :
	x(xy_.x),
	y(xy_.y),
	z(z_),
	w(w_)
{
}
inline										TexProject::uvec4::uvec4(const uint32 x_, const uvec2& yz_, const uint32 w_):
	x(x_),
	y(yz_.x),
	z(yz_.y),
	w(w_)
{
}
inline										TexProject::uvec4::uvec4(const uint32 x_, const uint32 y_, const uvec2& zw_) :
	x(x_),
	y(y_),
	z(zw_.x),
	w(zw_.y)
{
}
inline										TexProject::uvec4::uvec4(const uint32 x_, const uint32 y_, const uint32 z_, const uint32 w_) :
	x(x_),
	y(y_),
	z(z_),
	w(w_)
{
}
inline										TexProject::uvec4::uvec4(const vec4& a) :
	x(uint32(a.x)),
	y(uint32(a.y)),
	z(uint32(a.z)),
	w(uint32(a.w))
{
}
inline										TexProject::uvec4::uvec4(const ivec4& a) :
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

inline TexProject::uvec4					TexProject::operator + (const uvec4& a, const uint32 b)
{
	return uvec4(
					a.x + b,
					a.y + b,
					a.z + b,
					a.w + b
				);
}
inline TexProject::uvec4					TexProject::operator - (const uvec4& a, const uint32 b)
{
	return uvec4(
					a.x - b,
					a.y - b,
					a.z - b,
					a.w - b
				);
}
inline TexProject::uvec4					TexProject::operator * (const uvec4& a, const uint32 b)
{
	return uvec4(
					a.x * b,
					a.y * b,
					a.z * b,
					a.w * b
				);
}
inline TexProject::uvec4					TexProject::operator / (const uvec4& a, const uint32 b)
{
	return uvec4(
					a.x / b,
					a.y / b,
					a.z / b,
					a.w / b
				);
}

inline TexProject::uvec4					TexProject::operator + (const uint32 a, const uvec4& b)
{
	return uvec4(
					a + b.x,
					a + b.y,
					a + b.z,
					a + b.w
				);
}
inline TexProject::uvec4					TexProject::operator - (const uint32 a, const uvec4& b)
{
	return uvec4(
					a - b.x,
					a - b.y,
					a - b.z,
					a - b.w
				);
}
inline TexProject::uvec4					TexProject::operator * (const uint32 a, const uvec4& b)
{
	return uvec4(
					a * b.x,
					a * b.y,
					a * b.z,
					a * b.w
				);
}
inline TexProject::uvec4					TexProject::operator / (const uint32 a, const uvec4& b)
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

// functions;
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


inline TexProject::float32					TexProject::dot(const vec2& a, const vec2& b)
{
	return a.x * b.x + a.y * b.y;
}
inline TexProject::float32					TexProject::dot(const vec3& a, const vec3& b)
{
	return a.x * b.x + a.y * b.y + a.z * b.z;
}
inline TexProject::float32					TexProject::dot(const vec4& a, const vec4& b)
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

inline TexProject::float32					TexProject::dist(const vec3& a, const vec3& b)
{
	return length(a - b);
}

inline TexProject::float32					TexProject::dist(const vec4& a, const vec4& b)
{
	return length(a - b);
}

inline TexProject::vec3						TexProject::cross(const vec3& a, const vec3& b)
{
	return vec3	(
					a.y*b.z - a.z*b.y,
					a.z*b.x - a.x*b.z,
					a.x*b.y - a.y*b.x					
				);
}

inline TexProject::float32					TexProject::getAng(const vec2& a, const vec2& b)
{
	return acosDg(dot(a,b) / (length(a)*length(b)));
}













