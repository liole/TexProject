#pragma once
#include <TexProject/TexProject_Header.h>

#include <TexProject/TexProject_Math.h>


namespace TexProject
{
	namespace Geometry
	{
		class Mesh
		{
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

			Mesh&							operator = (const Mesh&) = delete;
			Mesh&							operator = (Mesh&&) = delete;

			void							Create(uint32 vCount_,uint32 iCount_);
			void							CreateBox(vec3 size, vec3 tex, uvec3 seg);
			void							CreateSphere(float32 radius,vec2 tex, uvec2 seg);
			void							CreateCylinder(float32 radius,float32 height,vec2 texSide,vec2 texCap,uvec2 segSide,uint32 segCap);
			void							CreateCone(float32 radiusBottom,float32 radiusTop,float32 height,vec2 texSize,vec2 texCap,uvec2 segSize,uint32 segCap,bool cap = true);
			void							CreateCapsule(float32 radius,float32 height,vec2 tex,uvec2 seg);
			void							CreateTorus(float32 radius,float32 width,vec2 tex,uvec2 seg);
			void							Delete();

			inline uint32					GetVertexSize() const
			{
				return sizeof(vec3)*4 + sizeof(vec2);
			}
			inline uint32					GetIndexSize() const
			{
				return sizeof(uint32);
			}
			inline uint32					GetVertexCount() const;
			inline uint32					GetIndexCount() const;
			inline float32*					GetVertexArray() const;
			inline uint32*					GetIndexArray() const;
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
inline TexProject::float32*					TexProject::Geometry::Mesh::GetVertexArray() const
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
}
inline TexProject::uint32*					TexProject::Geometry::Mesh::GetIndexArray() const
{
	auto arr = new uint32[iCount];
	for(uint32 i = 0; i < iCount; ++i) arr[i] = vInd[i];
	return arr;
}


















