#pragma once
#include "TexProject_Header.h"
#include "TexProject_Math.h"

namespace TexProject
{
	namespace Geometry
	{
		class Mesh
		{
		public:
			/*
			float float float	pos(12)
			half half half		tan(6)
			half half half		nor(6)
			float float			tex(8)
			(32)
			*/
			/*
			half half half		pos(6)
			half half half		tan(6)
			half half half		nor(6)
			half half			tex(4)
			(22), bin - restore from tan & nor
			*/
			/*
			half half half		pos(6)
			half half			tan(4) spherical
			half half			nor(4) spherical
			half half			tex(4)
			(18)
			*/
			/*
			half half half		pos(6)
			half half			nor(4) spherical
			half				tan(4) polar
			half half			tex(4)
			(16)
			*/
			/*
			half half half		pos(6)
			byte byte byte		tbn(3) spherical + polar
			half half			tex(4)
			(13)
			*/
			enum class CompressionMode
			{
				Pos12TBN36Tex8,				//56
				Pos12TN12Tex8,				//32
				Default = Pos12TBN36Tex8
			};
		protected:
			uint32							vCount = 0;
			uint32							iCount = 0;
			vec3*							vPos = nullptr;
			vec2*							vTex = nullptr;
			vec3*							vTan = nullptr;
			vec3*							vBin = nullptr;
			vec3*							vNor = nullptr;
			uint32*							vInd = nullptr;
		public:
											Mesh() = default;
											Mesh(const Mesh&) = delete;
											Mesh(Mesh&&) = delete;
											~Mesh();
		public:
			Mesh&							operator = (const Mesh&) = delete;
			Mesh&							operator = (Mesh&&) = delete;
		public:
			void							Create(uint32 vCount_,uint32 iCount_);
			void							CreateBox(const vec3& size_,const vec3& tex_,const uvec3& seg_);
			void							CreateSphere(float32 radius_,const vec2& tex_,const uvec2& seg_);
			void							CreateCylinder(float32 radius_,float32 height_,const vec2& texSide_,const vec2& texCap_,const uvec2& segSide_,uint32 segCap_);
			void							CreateCone(float32 radiusBottom_,float32 radiusTop_,float32 height_,const vec2& texSide_,const vec2& texCap_,const uvec2& segSide_,uint32 segCap_,bool cap_ = true);
			void							CreateCapsule(float32 radius_,float32 height_,const vec2& tex_,const uvec2& seg_);
			void							CreateTorus(float32 radius_,float32 width_,const vec2& tex_,const uvec2& seg_);
			void							Delete();
		public:
			inline uint32					GetVertexSize(CompressionMode mode_ = CompressionMode::Default) const
			{
				switch(mode_)
				{
				case CompressionMode::Pos12TBN36Tex8: return 56;
				case CompressionMode::Pos12TN12Tex8: return 32;
				default: return 0;
				}
				return sizeof(vec3)*4 + sizeof(vec2);
			}
			inline uint32					GetIndexSize() const
			{
				return sizeof(uint32);
			}
			inline uint32					GetVertexCount() const;
			inline uint32					GetIndexCount() const;
			inline void*					GetVertexArray(CompressionMode mode_ = CompressionMode::Default) const;
			inline uint32*					GetIndexArray() const;
		public:
			inline void						GenTBN(bool flip_t = false,bool flip_b = false);
		};
	}
}


inline TexProject::uint32					TexProject::Geometry::Mesh::GetVertexCount() const
{
	return vCount;
}
inline TexProject::uint32					TexProject::Geometry::Mesh::GetIndexCount() const
{
	return iCount;
}
inline void*								TexProject::Geometry::Mesh::GetVertexArray(CompressionMode mode_) const
{
	switch(mode_)
	{
	case CompressionMode::Pos12TBN36Tex8:
	{
		auto arr = new float32[14 * vCount];
		for(uint32 i = 0; i < vCount; ++i)
		{
			uint32 id = i*14;
			arr[id+0] = vPos[i].x;
			arr[id+1] = vPos[i].y;
			arr[id+2] = vPos[i].z;
			arr[id+3] = vTan[i].x;
			arr[id+4] = vTan[i].y;
			arr[id+5] = vTan[i].z;
			arr[id+6] = vBin[i].x;
			arr[id+7] = vBin[i].y;
			arr[id+8] = vBin[i].z;
			arr[id+9] = vNor[i].x;
			arr[id+10] = vNor[i].y;
			arr[id+11] = vNor[i].z;
			arr[id+12] = vTex[i].x;
			arr[id+13] = vTex[i].y;
		}
		return arr;
	} break;
	case CompressionMode::Pos12TN12Tex8:
	{
		auto d = GetVertexSize(CompressionMode::Pos12TN12Tex8);
		void* arr = new uint8[d * vCount];
		for(uint32 i = 0; i < vCount; ++i)
		{
			*((float32*)((uint8*)arr + i*d + 0)) = vPos[i].x;
			*((float32*)((uint8*)arr + i*d + 4)) = vPos[i].y;
			*((float32*)((uint8*)arr + i*d + 8)) = vPos[i].z;
			*((float16*)((uint8*)arr + i*d + 12)) = vTan[i].x;
			*((float16*)((uint8*)arr + i*d + 14)) = vTan[i].y;
			*((float16*)((uint8*)arr + i*d + 16)) = vTan[i].z;
			*((float16*)((uint8*)arr + i*d + 18)) = vNor[i].x;
			*((float16*)((uint8*)arr + i*d + 20)) = vNor[i].y;
			*((float16*)((uint8*)arr + i*d + 22)) = vNor[i].z;
			*((float32*)((uint8*)arr + i*d + 24)) = vTex[i].x;
			*((float32*)((uint8*)arr + i*d + 28)) = vTex[i].y;
		}
		return arr;
	} break;
	default: return nullptr;
	}
}
inline TexProject::uint32*					TexProject::Geometry::Mesh::GetIndexArray() const
{
	auto arr = new uint32[iCount];
	for(uint32 i = 0; i < iCount; ++i) arr[i] = vInd[i];
	return arr;
}
inline void									TexProject::Geometry::Mesh::GenTBN(bool flip_t,bool flip_b)
{
	uint32 id0,id1,id2;
	for(uint32 i = 0; i < iCount; i += 3)
	{
		id0 = vInd[i + 0];
		id1 = vInd[i + 1];
		id2 = vInd[i + 2];

		vec3 e0 = vPos[id1] - vPos[id0];
		vec3 e1 = vPos[id2] - vPos[id0];
		vec2 e0uv = vTex[id1] - vTex[id0];
		vec2 e1uv = vTex[id2] - vTex[id0];
		float32 cp = e0uv.y * e1uv.x - e0uv.x * e1uv.y;
		if(cp != 0.0f)
		{
			float32 k = 1.0f / cp;
			vTan[id0] = (e0 * -e1uv.y + e1 * e0uv.y) * k;
			vBin[id0] = (e0 * -e1uv.x + e1 * e0uv.x) * k;
			vTan[id0].normalize();
			vBin[id0].normalize();
		}

		vTan[id2] = vTan[id1] = vTan[id0];
		vBin[id2] = vBin[id1] = vBin[id0];

		if(flip_t)
		{
			vTan[id0] = -vTan[id0];
			vTan[id1] = -vTan[id1];
			vTan[id2] = -vTan[id2];
		}
		if(flip_b)
		{
			vBin[id0] = -vBin[id0];
			vBin[id1] = -vBin[id1];
			vBin[id2] = -vBin[id2];
		}
	}
}


















