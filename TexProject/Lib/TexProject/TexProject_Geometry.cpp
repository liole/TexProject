#include "TexProject_Geometry.h"
using namespace TexProject;


TexProject::Geometry::Mesh::~Mesh()
{
	Delete();
}

void					TexProject::Geometry::Mesh::Create(uint32 vCount_,uint32 iCount_)
{
	Delete();
	if(vCount_ > 0)
	{
		vCount = vCount_;
		vPos = (vec3*)malloc(sizeof(vec3)*vCount);
		vTex = (vec2*)malloc(sizeof(vec3)*vCount);
		vTan = (vec3*)malloc(sizeof(vec3)*vCount);
		vBin = (vec3*)malloc(sizeof(vec3)*vCount);
		vNor = (vec3*)malloc(sizeof(vec3)*vCount);
	}
	if(iCount_ > 0)
	{
		iCount = iCount_;
		vInd = (uint32*)malloc(sizeof(uint32)*iCount);
	}
}
void					TexProject::Geometry::Mesh::CreateBox(const vec3& size,const vec3& tex,const uvec3& seg)
{
	if(seg.x == 0 || seg.y == 0 || seg.z == 0) return;

	Create
	(
		2*((seg.x+1)*(seg.y+1) + (seg.y+1)*(seg.z+1) + (seg.z+1)*(seg.x+1)),
		2*6*(seg.x*seg.y + seg.y*seg.z + seg.z*seg.x)
	);

	uint32 id;
	vec3 maxPos = size * 0.5f;
	vec3 minPos = size * -0.5f;

	const uint32 offsetVertexBack = 0;
	const uint32 offsetVertexFront = offsetVertexBack + (seg.x+1)*(seg.y+1);
	const uint32 offsetVertexLeft = offsetVertexFront + (seg.x+1)*(seg.y+1);
	const uint32 offsetVertexRight = offsetVertexLeft + (seg.y+1)*(seg.z+1);
	const uint32 offsetVertexBottom = offsetVertexRight + (seg.y+1)*(seg.z+1);
	const uint32 offsetVertexTop = offsetVertexBottom + (seg.z+1)*(seg.x+1);
	const uint32 offsetIndexBack = 0;
	const uint32 offsetIndexFront = offsetIndexBack + 6*(seg.x*seg.y);
	const uint32 offsetIndexLeft = offsetIndexFront + 6*(seg.x*seg.y);
	const uint32 offsetIndexRight = offsetIndexLeft + 6*(seg.y*seg.z);
	const uint32 offsetIndexBottom = offsetIndexRight + 6*(seg.y*seg.z);
	const uint32 offsetIndexTop = offsetIndexBottom + 6*(seg.z*seg.y);

	for(uint32 x = 0; x <= seg.x; ++x)
	for(uint32 y = 0; y <= seg.y; ++y)
	{
		vec2 t(float32(x)/float32(seg.x),float32(y)/float32(seg.y));

		id = offsetVertexBack + y*(seg.x+1) + x;
		vPos[id] = vec3(minPos.x + size.x*t.x,minPos.y + size.y*t.y,minPos.z);
		vTex[id] = t * tex.xy();
		vTan[id] = vec3(1.0f,0.0f,0.0f);
		vBin[id] = vec3(0.0f,1.0f,0.0f);
		vNor[id] = vec3(0.0f,0.0f,-1.0f);

		id = offsetVertexFront + y*(seg.x+1) + x;
		vPos[id] = vec3(minPos.x + size.x*t.x,minPos.y + size.y*t.y,maxPos.z);
		vTex[id] = vec2(1.0f - t.x,t.y) * tex.xy();
		vTan[id] = vec3(-1.0f,0.0f,0.0f);
		vBin[id] = vec3(0.0f,1.0f,0.0f);
		vNor[id] = vec3(0.0f,0.0f,1.0f);
	}
	for(uint32 y = 0; y <= seg.y; ++y)
	for(uint32 z = 0; z <= seg.z; ++z)
	{
		vec2 t(float32(z)/float32(seg.z),float32(y)/float32(seg.y));

		id = offsetVertexLeft + z*(seg.y+1) + y;
		vPos[id] = vec3(minPos.x,minPos.y + size.y*t.y,minPos.z + size.z*t.x);
		vTex[id] = vec2(1.0f - t.x,t.y) * vec2(tex.z,tex.y);
		vTan[id] = vec3(0.0f,0.0f,-1.0f);
		vBin[id] = vec3(0.0f,1.0f,0.0f);
		vNor[id] = vec3(-1.0f,0.0f,0.0f);

		id = offsetVertexRight + z*(seg.y+1) + y;
		vPos[id] = vec3(maxPos.x,minPos.y + size.y*t.y,minPos.z + size.z*t.x);
		vTex[id] = t * vec2(tex.z,tex.y);
		vTan[id] = vec3(0.0f,0.0f,1.0f);
		vBin[id] = vec3(0.0f,1.0f,0.0f);
		vNor[id] = vec3(1.0f,0.0f,0.0f);
	}
	for(uint32 z = 0; z <= seg.z; ++z)
	for(uint32 x = 0; x <= seg.x; ++x)
	{
		vec2 t(float32(x)/float32(seg.x),float32(z)/float32(seg.z));

		id = offsetVertexBottom + x*(seg.z+1) + z;
		vPos[id] = vec3(minPos.x + size.x*t.x,minPos.y,minPos.z + size.z*t.y);
		vTex[id] = vec2(t.x,1.0f - t.y) * vec2(tex.x,tex.z);
		vTan[id] = vec3(1.0f,0.0f,0.0f);
		vBin[id] = vec3(0.0f,0.0f,-1.0f);
		vNor[id] = vec3(0.0f,-1.0f,0.0f);

		id = offsetVertexTop + x*(seg.z+1) + z;
		vPos[id] = vec3(minPos.x + size.x*t.x,maxPos.y,minPos.z + size.z*t.y);
		vTex[id] = t * vec2(tex.x,tex.z);
		vTan[id] = vec3(1.0f,0.0f,0.0f);
		vBin[id] = vec3(0.0f,0.0f,1.0f);
		vNor[id] = vec3(0.0f,1.0f,0.0f);
	}

	for(uint32 x = 0; x < seg.x; ++x)
	for(uint32 y = 0; y < seg.y; ++y)
	{
		id = offsetIndexBack + 6*(y*seg.x + x);
		vInd[id+0] = offsetVertexBack + (y+0)*(seg.x+1) + (x+0);
		vInd[id+1] = offsetVertexBack + (y+0)*(seg.x+1) + (x+1);
		vInd[id+2] = offsetVertexBack + (y+1)*(seg.x+1) + (x+0);
		vInd[id+3] = vInd[id+2];
		vInd[id+4] = vInd[id+1];
		vInd[id+5] = offsetVertexBack + (y+1)*(seg.x+1) + (x+1);

		id = offsetIndexFront + 6*(y*seg.x + x);
		vInd[id+0] = offsetVertexFront + (y+0)*(seg.x+1) + (x+0);
		vInd[id+2] = offsetVertexFront + (y+0)*(seg.x+1) + (x+1);
		vInd[id+1] = offsetVertexFront + (y+1)*(seg.x+1) + (x+0);
		vInd[id+3] = vInd[id+2];
		vInd[id+4] = vInd[id+1];
		vInd[id+5] = offsetVertexFront + (y+1)*(seg.x+1) + (x+1);
	}
	for(uint32 y = 0; y < seg.y; ++y)
	for(uint32 z = 0; z < seg.z; ++z)
	{
		id = offsetIndexLeft + 6*(z*seg.y + y);
		vInd[id+0] = offsetVertexLeft + (z+0)*(seg.y+1) + (y+0);
		vInd[id+1] = offsetVertexLeft + (z+0)*(seg.y+1) + (y+1);
		vInd[id+2] = offsetVertexLeft + (z+1)*(seg.y+1) + (y+0);
		vInd[id+3] = vInd[id+2];
		vInd[id+4] = vInd[id+1];
		vInd[id+5] = offsetVertexLeft + (z+1)*(seg.y+1) + (y+1);

		id = offsetIndexRight + 6*(z*seg.y + y);
		vInd[id+0] = offsetVertexRight + (z+0)*(seg.y+1) + (y+0);
		vInd[id+2] = offsetVertexRight + (z+0)*(seg.y+1) + (y+1);
		vInd[id+1] = offsetVertexRight + (z+1)*(seg.y+1) + (y+0);
		vInd[id+3] = vInd[id+2];
		vInd[id+4] = vInd[id+1];
		vInd[id+5] = offsetVertexRight + (z+1)*(seg.y+1) + (y+1);
	}
	for(uint32 z = 0; z < seg.z; ++z)
	for(uint32 x = 0; x < seg.x; ++x)
	{
		id = offsetIndexBottom + 6*(x*seg.z + z);
		vInd[id+0] = offsetVertexBottom + (x+0)*(seg.z+1) + (z+0);
		vInd[id+1] = offsetVertexBottom + (x+0)*(seg.z+1) + (z+1);
		vInd[id+2] = offsetVertexBottom + (x+1)*(seg.z+1) + (z+0);
		vInd[id+3] = vInd[id+2];
		vInd[id+4] = vInd[id+1];
		vInd[id+5] = offsetVertexBottom + (x+1)*(seg.z+1) + (z+1);

		id = offsetIndexTop + 6*(x*seg.z + z);
		vInd[id+0] = offsetVertexTop + (x+0)*(seg.z+1) + (z+0);
		vInd[id+2] = offsetVertexTop + (x+0)*(seg.z+1) + (z+1);
		vInd[id+1] = offsetVertexTop + (x+1)*(seg.z+1) + (z+0);
		vInd[id+3] = vInd[id+2];
		vInd[id+4] = vInd[id+1];
		vInd[id+5] = offsetVertexTop + (x+1)*(seg.z+1) + (z+1);
	}
}
void					TexProject::Geometry::Mesh::CreateSphere(float32 radius,const vec2& tex,const uvec2& seg)
{
	if(seg.x < 3 || seg.y < 3) return;

	Create((seg.x+1)*(seg.y+1),6*seg.x*seg.y);

	for(uint32 x = 0; x <= seg.x; ++x)
	for(uint32 y = 0; y <= seg.y; ++y)
	{
		float32 dx = float32(x) / float32(seg.x);
		float32 dy = float32(y) / float32(seg.y);
		uint32 id = y*(seg.x+1) + x;
		mat3 rMat = mat3::rotateZXY(vec3(90.0f - dy*180.0f,180.0f - dx*360.0f,0.0f));
		vPos[id] = rMat * vec3(0.0f,0.0f,radius);
		vTex[id] = vec2(dx,dy)*tex;
		vTan[id] = rMat * vec3(-1.0f,0.0f,0.0f);
		vBin[id] = rMat * vec3(0.0f,1.0f,0.0f);
		vNor[id] = rMat * vec3(0.0f,0.0f,1.0f);
	}

	for(uint32 x = 0; x < seg.x; ++x)
	for(uint32 y = 0; y < seg.y; ++y)
	{
		uint32 id = 6*(y*seg.x + x);
		vInd[id+0] = (y+0)*(seg.x+1) + (x+0);
		vInd[id+1] = (y+0)*(seg.x+1) + (x+1);
		vInd[id+2] = (y+1)*(seg.x+1) + (x+0);
		vInd[id+3] = vInd[id+1];
		vInd[id+4] = (y+1)*(seg.x+1) + (x+1);
		vInd[id+5] = vInd[id+2];
	}
}
void					TexProject::Geometry::Mesh::CreateCylinder(float32 radius,float32 height,const vec2& texSide,const vec2& texCap,const uvec2& segSide,uint32 segCap)
{
	if(segSide.x < 3) return;

	Create
	(
		(segSide.x+1)*(segSide.y+1) + ((segCap > 0) ? 2*(segCap*(segSide.x+1)+1) : 2*(segSide.x+1)),
		6*segSide.x*segSide.y + ((segCap > 0) ? 2*(3*segSide.x + 6*segSide.x*(segCap-1)) : 2*3*(segSide.x-2)) // todo
	);

	uint32 offsetVertexCap = (segSide.x+1)*(segSide.y+1);
	uint32 offsetIndexCap = 6*segSide.x*segSide.y;

	for(uint32 x = 0; x <= segSide.x; ++x)
	for(uint32 y = 0; y <= segSide.y; ++y)
	{
		float32 dx = float32(x) / float32(segSide.x);
		float32 dy = float32(y) / float32(segSide.y);
		uint32 id = y*(segSide.x+1)+x;
		vPos[id] = vec3(sinDg(180.0f - 360.0f * dx)*radius,-height*0.5f + height*dy,cosDg(180.0f - 360.0f * dx)*radius);
		vTex[id] = vec2(dx,dy)*texSide;
		vTan[id] = vec3(sinDg(180.0f - 360.0f * dx - 90.0f),0.0f,cosDg(180.0f - 360.0f * dx - 90.0f));
		vBin[id] = vec3(0.0f,1.0f,0.0f);
		vNor[id] = vec3(sinDg(180.0f - 360.0f * dx),0.0f,cosDg(180.0f - 360.0f * dx));
	}

	for(uint32 x = 0; x < segSide.x; ++x)
	for(uint32 y = 0; y < segSide.y; ++y)
	{
		uint32 i = y*segSide.x+x;
		vInd[i*6 + 0] = (y+0)*(segSide.x+1)+x;
		vInd[i*6 + 1] = (y+0)*(segSide.x+1)+x+1;
		vInd[i*6 + 2] = (y+1)*(segSide.x+1)+x;
		vInd[i*6 + 3] = vInd[i*6 + 2];
		vInd[i*6 + 4] = vInd[i*6 + 1];
		vInd[i*6 + 5] = (y+1)*(segSide.x+1)+x+1;
	}

	if(segCap > 0)
	{
		uint32 id = offsetVertexCap;
		vPos[id] = vec3(0.0f,+height*0.5f,0.0f);
		vTex[id] = vec2(0.5f);
		vTan[id] = vec3(1.0f,0.0f,0.0f);
		vBin[id] = vec3(0.0f,0.0f,1.0f);
		vNor[id] = vec3(0.0f,1.0f,0.0f);
		id = offsetVertexCap+(segCap*(segSide.x+1)+1);
		vPos[id] = vec3(0.0f,-height*0.5f,0.0f);
		vTex[id] = vec2(0.5f);
		vTan[id] = vec3(-1.0f,0.0f,0.0f);
		vBin[id] = vec3(0.0f,0.0f,-1.0f);
		vNor[id] = vec3(0.0f,-1.0f,0.0f);
		for(uint32 i = 0; i < segCap; ++i)
		{
			float32 di = float32(i+1) / float32(segCap);
			for(uint32 x = 0; x <= segSide.x; ++x)
			{
				float32 dx = float32(x) / float32(segSide.x);
				uint32 id = offsetVertexCap + 1 + i*(segSide.x+1) + x;
				vPos[id] = vec3(sinDg(360.0f * dx)*di*radius,height*0.5f,cosDg(360.0f * dx)*di*radius);
				vTex[id] = vec2(sinDg(360.0f * dx),cosDg(360.0f * dx))*texCap*di*0.5f + 0.5f;
				vTan[id] = vec3(1.0f,0.0f,0.0f);
				vBin[id] = vec3(0.0f,0.0f,1.0f);
				vNor[id] = vec3(0.0f,1.0f,0.0f);
				id = offsetVertexCap + (segCap*(segSide.x+1)+1) + 1 + i*(segSide.x+1) + x;
				vPos[id] = vec3(sinDg(360.0f * -dx)*di*radius,-height*0.5f,cosDg(360.0f * -dx)*di*radius);
				vTex[id] = vec2(sinDg(360.0f * -dx),cosDg(360.0f * -dx))*texCap*di*0.5f + 0.5f;
				vTan[id] = vec3(-1.0f,0.0f,0.0f);
				vBin[id] = vec3(0.0f,0.0f,-1.0f);
				vNor[id] = vec3(0.0f,-1.0f,0.0f);
			}
		}
		for(uint32 x = 0; x < segSide.x; ++x)
		{
			uint32 id = offsetIndexCap + 3*x;
			vInd[id+0] = offsetVertexCap;
			vInd[id+1] = offsetVertexCap + 1 + x + 1;
			vInd[id+2] = offsetVertexCap + 1 + x;
			id = offsetIndexCap + (3*segSide.x + 6*segSide.x*(segCap-1)) + 3*x;
			vInd[id+0] = offsetVertexCap + (segCap*(segSide.x+1)+1);
			vInd[id+1] = offsetVertexCap + (segCap*(segSide.x+1)+1) + 1 + x + 1;
			vInd[id+2] = offsetVertexCap + (segCap*(segSide.x+1)+1) + 1 + x;
			for(uint32 i = 1; i < segCap; ++i)
			{
				float32 di = float32(i+1) / float32(segCap);
				id = offsetIndexCap + 3*segSide.x + (i-1)*6*segSide.x + x*6;
				vInd[id+0] = offsetVertexCap + 1 + (i-1)*(segSide.x+1) + x;
				vInd[id+1] = offsetVertexCap + 1 + (i-1)*(segSide.x+1) + (x+1);
				vInd[id+2] = offsetVertexCap + 1 + i*(segSide.x+1) + x;
				vInd[id+3] = vInd[id+1];
				vInd[id+4] = offsetVertexCap + 1 + i*(segSide.x+1) + (x+1);
				vInd[id+5] = vInd[id+2];
				id = offsetIndexCap + (3*segSide.x + 6*segSide.x*(segCap-1)) + 3*segSide.x + (i-1)*6*segSide.x + x*6;
				vInd[id+0] = offsetVertexCap + (segCap*(segSide.x+1)+1) + 1 + (i-1)*(segSide.x+1) + x;
				vInd[id+1] = offsetVertexCap + (segCap*(segSide.x+1)+1) + 1 + (i-1)*(segSide.x+1) + (x+1);
				vInd[id+2] = offsetVertexCap + (segCap*(segSide.x+1)+1) + 1 + i*(segSide.x+1) + x;
				vInd[id+3] = vInd[id+1];
				vInd[id+4] = offsetVertexCap + (segCap*(segSide.x+1)+1) + 1 + i*(segSide.x+1) + (x+1);
				vInd[id+5] = vInd[id+2];
			}
		}
	}
	else
	{
		for(uint32 x = 0; x <= segSide.x; ++x)
		{
			float32 dx = float32(x) / float32(segSide.x);
			uint32 id = offsetVertexCap + x;
			vPos[id] = vec3(sinDg(360.0f * dx)*radius,height*0.5f,cosDg(360.0f * dx)*radius);
			vTex[id] = vec2(sinDg(360.0f * dx),cosDg(360.0f * dx))*texCap;
			vTan[id] = vec3(1.0f,0.0f,0.0f);
			vBin[id] = vec3(0.0f,0.0f,1.0f);
			vNor[id] = vec3(0.0f,1.0f,0.0f);
			id = offsetVertexCap + (segSide.x+1) + x;
			vPos[id] = vec3(sinDg(360.0f * dx)*radius,-height*0.5f,cosDg(360.0f * dx)*radius);
			vTex[id] = vec2(sinDg(360.0f * -dx),cosDg(360.0f * -dx))*texCap;
			vTan[id] = vec3(-1.0f,0.0f,0.0f);
			vBin[id] = vec3(0.0f,0.0f,-1.0f);
			vNor[id] = vec3(0.0f,-1.0f,0.0f);
		}
		for(uint32 x = 0; x < segSide.x-2; ++x)
		{
			uint32 i = offsetIndexCap + 3*x;
			vInd[i+0] = offsetVertexCap + 0;
			vInd[i+1] = offsetVertexCap + x + 2;
			vInd[i+2] = offsetVertexCap + x + 1;
			i = offsetIndexCap + 3*((segSide.x-2) + x);
			vInd[i+0] = offsetVertexCap + (segSide.x+1) + 0;
			vInd[i+1] = offsetVertexCap + (segSide.x+1) + x + 1;
			vInd[i+2] = offsetVertexCap + (segSide.x+1) + x + 2;
		}
	}
}
void					TexProject::Geometry::Mesh::CreateCone(float32 radiusBottom_,float32 radiusTop_,float32 height_,const vec2& texSide_,const vec2& texCap_,const uvec2& segSide_,uint32 segCap_,bool cap_)
{
	if(segSide_.x < 3) return;

	Create
	(
		(segSide_.x+1)*(segSide_.y+1) + ((segCap_ > 0) ? 2*(segCap_*(segSide_.x+1)+1) : 2*(segSide_.x+1)),
		6*segSide_.x*segSide_.y + ((segCap_ > 0) ? 2*(3*segSide_.x + 6*segSide_.x*(segCap_-1)) : 2*3*(segSide_.x-2))
	);

	uint32 offsetVertexCap = (segSide_.x + 1)*(segSide_.y + 1);
	uint32 offsetIndexCap = 6*segSide_.x*segSide_.y;

	vec2 dn = normalize(vec2(height_,radiusTop_ - radiusBottom_));

	for(uint32 x = 0; x <= segSide_.x; ++x)
	for(uint32 y = 0; y <= segSide_.y; ++y)
	{
		float32 dx = float32(x) / float32(segSide_.x);
		float32 dy = float32(y) / float32(segSide_.y);
		float32 r = bezier(radiusBottom_,radiusTop_,dy);
		uint32 id = y*(segSide_.x + 1) + x;
		vPos[id] = vec3(sinDg(180.0f - 360.0f * dx)*r,-height_*0.5f + height_*dy,cosDg(180.0f - 360.0f * dx)*r);
		vTex[id] = vec2(dx,dy)*texSide_;
		vTan[id] = vec3(sinDg(180.0f - 360.0f * dx - 90.0f),0.0f,cosDg(180.0f - 360.0f * dx - 90.0f));
		vBin[id] = vec3(0.0f,1.0f,0.0f);
		vNor[id] = vec3(sinDg(180.0f - 360.0f * dx)*dn.x,dn.y,cosDg(180.0f - 360.0f * dx)*dn.x);
	}

	for(uint32 x = 0; x < segSide_.x; ++x)
	for(uint32 y = 0; y < segSide_.y; ++y)
	{
		uint32 i = y*segSide_.x + x;
		vInd[i*6 + 0] = (y+0)*(segSide_.x+1)+x;
		vInd[i*6 + 1] = (y+0)*(segSide_.x+1)+x+1;
		vInd[i*6 + 2] = (y+1)*(segSide_.x+1)+x;
		vInd[i*6 + 3] = vInd[i*6 + 2];
		vInd[i*6 + 4] = vInd[i*6 + 1];
		vInd[i*6 + 5] = (y+1)*(segSide_.x+1)+x+1;
	}

	if(segCap_ > 0)
	{
		uint32 id = offsetVertexCap;
		vPos[id] = vec3(0.0f,+height_*0.5f,0.0f);
		vTex[id] = vec2(0.5f);
		vTan[id] = vec3(1.0f,0.0f,0.0f);
		vBin[id] = vec3(0.0f,0.0f,1.0f);
		vNor[id] = vec3(0.0f,1.0f,0.0f);
		id = offsetVertexCap+(segCap_*(segSide_.x+1)+1);
		vPos[id] = vec3(0.0f,-height_*0.5f,0.0f);
		vTex[id] = vec2(0.5f);
		vTan[id] = vec3(-1.0f,0.0f,0.0f);
		vBin[id] = vec3(0.0f,0.0f,-1.0f);
		vNor[id] = vec3(0.0f,-1.0f,0.0f);
		for(uint32 i = 0; i < segCap_; ++i)
		{
			float32 di = float32(i+1) / float32(segCap_);
			for(uint32 x = 0; x <= segSide_.x; ++x)
			{
				float32 dx = float32(x) / float32(segSide_.x);
				uint32 id = offsetVertexCap + 1 + i*(segSide_.x + 1) + x;
				vPos[id] = vec3(sinDg(360.0f * dx)*di*radiusTop_,height_*0.5f,cosDg(360.0f * dx)*di*radiusTop_);
				vTex[id] = vec2(sinDg(360.0f * dx),cosDg(360.0f * dx))*texCap_*di*0.5f + 0.5f;
				vTan[id] = vec3(1.0f,0.0f,0.0f);
				vBin[id] = vec3(0.0f,0.0f,1.0f);
				vNor[id] = vec3(0.0f,1.0f,0.0f);
				id = offsetVertexCap + (segCap_*(segSide_.x + 1) + 1) + 1 + i*(segSide_.x + 1) + x;
				vPos[id] = vec3(sinDg(360.0f * -dx)*di*radiusBottom_,-height_*0.5f,cosDg(360.0f * -dx)*di*radiusBottom_);
				vTex[id] = vec2(sinDg(360.0f * -dx),cosDg(360.0f * -dx))*texCap_*di*0.5f + 0.5f;
				vTan[id] = vec3(-1.0f,0.0f,0.0f);
				vBin[id] = vec3(0.0f,0.0f,-1.0f);
				vNor[id] = vec3(0.0f,-1.0f,0.0f);
			}
		}
		for(uint32 x = 0; x < segSide_.x; ++x)
		{
			uint32 id = offsetIndexCap + 3*x;
			vInd[id+0] = offsetVertexCap;
			vInd[id+1] = offsetVertexCap + 1 + x + 1;
			vInd[id+2] = offsetVertexCap + 1 + x;
			id = offsetIndexCap + (3*segSide_.x + 6*segSide_.x*(segCap_-1)) + 3*x;
			vInd[id+0] = offsetVertexCap + (segCap_*(segSide_.x+1)+1);
			vInd[id+1] = offsetVertexCap + (segCap_*(segSide_.x+1)+1) + 1 + x + 1;
			vInd[id+2] = offsetVertexCap + (segCap_*(segSide_.x+1)+1) + 1 + x;
			for(uint32 i = 1; i < segCap_; ++i)
			{
				float32 di = float32(i+1) / float32(segCap_);
				id = offsetIndexCap + 3*segSide_.x + (i-1)*6*segSide_.x + x*6;
				vInd[id+0] = offsetVertexCap + 1 + (i-1)*(segSide_.x+1) + x;
				vInd[id+1] = offsetVertexCap + 1 + (i-1)*(segSide_.x+1) + (x+1);
				vInd[id+2] = offsetVertexCap + 1 + i*(segSide_.x+1) + x;
				vInd[id+3] = vInd[id+1];
				vInd[id+4] = offsetVertexCap + 1 + i*(segSide_.x+1) + (x+1);
				vInd[id+5] = vInd[id+2];
				id = offsetIndexCap + (3*segSide_.x + 6*segSide_.x*(segCap_-1)) + 3*segSide_.x + (i-1)*6*segSide_.x + x*6;
				vInd[id+0] = offsetVertexCap + (segCap_*(segSide_.x+1)+1) + 1 + (i-1)*(segSide_.x+1) + x;
				vInd[id+1] = offsetVertexCap + (segCap_*(segSide_.x+1)+1) + 1 + (i-1)*(segSide_.x+1) + (x+1);
				vInd[id+2] = offsetVertexCap + (segCap_*(segSide_.x+1)+1) + 1 + i*(segSide_.x+1) + x;
				vInd[id+3] = vInd[id+1];
				vInd[id+4] = offsetVertexCap + (segCap_*(segSide_.x+1)+1) + 1 + i*(segSide_.x+1) + (x+1);
				vInd[id+5] = vInd[id+2];
			}
		}
	}
	else
	{
		for(uint32 x = 0; x <= segSide_.x; ++x)
		{
			float32 dx = float32(x) / float32(segSide_.x);
			uint32 id = offsetVertexCap + x;
			vPos[id] = vec3(sinDg(360.0f * dx)*radiusTop_,height_*0.5f,cosDg(360.0f * dx)*radiusTop_);
			vTex[id] = vec2(sinDg(360.0f * dx),cosDg(360.0f * dx))*texCap_;
			vTan[id] = vec3(1.0f,0.0f,0.0f);
			vBin[id] = vec3(0.0f,0.0f,1.0f);
			vNor[id] = vec3(0.0f,1.0f,0.0f);
			id = offsetVertexCap + (segSide_.x + 1) + x;
			vPos[id] = vec3(sinDg(360.0f * dx)*radiusBottom_,-height_*0.5f,cosDg(360.0f * dx)*radiusBottom_);
			vTex[id] = vec2(sinDg(360.0f * -dx),cosDg(360.0f * -dx))*texCap_;
			vTan[id] = vec3(-1.0f,0.0f,0.0f);
			vBin[id] = vec3(0.0f,0.0f,-1.0f);
			vNor[id] = vec3(0.0f,-1.0f,0.0f);
		}
		for(uint32 x = 0; x < segSide_.x - 2; ++x)
		{
			uint32 i = offsetIndexCap + 3*x;
			vInd[i+0] = offsetVertexCap + 0;
			vInd[i+1] = offsetVertexCap + x + 2;
			vInd[i+2] = offsetVertexCap + x + 1;
			i = offsetIndexCap + 3*((segSide_.x-2) + x);
			vInd[i+0] = offsetVertexCap + (segSide_.x+1) + 0;
			vInd[i+1] = offsetVertexCap + (segSide_.x+1) + x + 1;
			vInd[i+2] = offsetVertexCap + (segSide_.x+1) + x + 2;
		}
	}
}
void					TexProject::Geometry::Mesh::CreateCapsule(float32 radius_,float32 height_,const vec2& tex_,const uvec2& seg_)
{
	Create((seg_.x + 1)*(seg_.y+1)*2, (6*((seg_.y-1)*2+1) + 3*2) * seg_.x);

	float32 st = (radius_*_PIdev2f) / (2.0f*(radius_*_PIdev2f) + height_);
	mat3 tMat;

	for(uint32 x = 0; x <= seg_.x; ++x)
	{
		float32 dx = float32(x) / float32(seg_.x);
		for(uint32 y = 0; y <= seg_.y; ++y)
		{
			float32 dy = float32(y) / float32(seg_.y);
			{
				uint32 id = (seg_.y+1)*2*x + y;
				tMat.makeRotateZXY(vec3(-90.0f + 90.0f*dy,360.0f*dx-180.0f,0.0f));
				vPos[id] = (tMat * vec3(0.0f,0.0f,radius_)) + vec3(0.0f,height_*0.5f,0.0f);
				vTan[id] = tMat*vec3(1.0f,0.0f,0.0f);
				vBin[id] = tMat*vec3(0.0f,1.0f,0.0f);
				vNor[id] = tMat*vec3(0.0f,0.0f,1.0f);
				vTex[id] = vec2(1.0f - dx,1.0f - dy*st) * tex_;
			}
			{
				uint32 id = (seg_.y+1)*2*x + (seg_.y+1) + y;
				tMat.makeRotateZXY(vec3(90.0f*dy,360.0f*dx - 180.0f,0.0f));
				vPos[id] = (tMat * vec3(0.0f,0.0f,radius_)) + vec3(0.0f,-height_*0.5f,0.0f);
				vTan[id] = tMat*vec3(1.0f,0.0f,0.0f);
				vBin[id] = tMat*vec3(0.0f,1.0f,0.0f);
				vNor[id] = tMat*vec3(0.0f,0.0f,1.0f);
				vTex[id] = vec2(1.0f - dx,(1.0f - dy)*st) * tex_;
			}
		}
	}

	uint32 iR = 6*(1 + 2*(seg_.y-1)) + 3*2;
	for(uint32 x = 0; x < seg_.x; ++x)
	{
		{
			uint32 id = iR*x + 0;
			vInd[id + 0] = (seg_.y + 1)*2*(x+0) + 0;
			vInd[id + 1] = (seg_.y + 1)*2*(x+1) + 1;
			vInd[id + 2] = (seg_.y + 1)*2*(x+0) + 1;
		}
		{
			uint32 id = iR*x + (3 + 6*(2*(seg_.y-1) + 1)) + 0;
			vInd[id + 0] = (seg_.y + 1)*2*(x+0) + (2*seg_.y);
			vInd[id + 1] = (seg_.y + 1)*2*(x+1) + (2*seg_.y);
			vInd[id + 2] = (seg_.y + 1)*2*(x+0) + (2*seg_.y + 1);
		}
		{
			uint32 id = iR*x + 3 + 6*(seg_.y-1);
			vInd[id + 0] = (seg_.y + 1)*2*(x+0) + seg_.y + 0;
			vInd[id + 1] = (seg_.y + 1)*2*(x+1) + seg_.y + 0;
			vInd[id + 2] = (seg_.y + 1)*2*(x+0) + seg_.y + 1;
			vInd[id + 3] = vInd[id + 2];
			vInd[id + 4] = vInd[id + 1];
			vInd[id + 5] = (seg_.y + 1)*2*(x+1) + seg_.y + 1;
		}
		for(uint32 y = 0; y < seg_.y-1; ++y)
		{
			{
				uint32 id = iR*x + 3 + 6*y;
				vInd[id + 0] = (seg_.y + 1)*2*(x+0) + 1 + (y+0);
				vInd[id + 1] = (seg_.y + 1)*2*(x+1) + 1 + (y+0);
				vInd[id + 2] = (seg_.y + 1)*2*(x+0) + 1 + (y+1);
				vInd[id + 3] = vInd[id + 2];
				vInd[id + 4] = vInd[id + 1];
				vInd[id + 5] = (seg_.y + 1)*2*(x+1) + 1 + (y+1);
			}
			{
				uint32 id = iR*x + 3 + 6*(seg_.y-1) + 6 + 6*y;
				vInd[id + 0] = (seg_.y + 1)*2*(x+0) + (seg_.y + 1) + (y+0);
				vInd[id + 1] = (seg_.y + 1)*2*(x+1) + (seg_.y + 1) + (y+0);
				vInd[id + 2] = (seg_.y + 1)*2*(x+0) + (seg_.y + 1) + (y+1);
				vInd[id + 3] = vInd[id + 2];
				vInd[id + 4] = vInd[id + 1];
				vInd[id + 5] = (seg_.y + 1)*2*(x+1) + (seg_.y + 1) + (y+1);
			}
		}
	}
}

void					TexProject::Geometry::Mesh::Delete()
{
	if(vCount > 0)
	{
		if(vPos) { free(vPos); vPos = nullptr; }
		if(vTex) { free(vTex); vTex = nullptr; }
		if(vTan) { free(vTan); vTan = nullptr; }
		if(vBin) { free(vBin); vBin = nullptr; }
		if(vNor) { free(vNor); vNor = nullptr; }
		vCount = 0;
	}
	if(iCount > 0)
	{
		if(vInd) { free(vInd); vInd = nullptr; }
		iCount = 0;
	}
}






























