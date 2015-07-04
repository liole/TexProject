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
void					TexProject::Geometry::Mesh::CreateBox(vec3 size,vec3 tex,uvec3 seg)
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
		vTex[id] = t;
		vTan[id] = vec3(1.0f,0.0f,0.0f);
		vBin[id] = vec3(0.0f,1.0f,0.0f);
		vNor[id] = vec3(0.0f,0.0f,-1.0f);

		id = offsetVertexFront + y*(seg.x+1) + x;
		vPos[id] = vec3(minPos.x + size.x*t.x,minPos.y + size.y*t.y,maxPos.z);
		vTex[id] = vec2(1.0f-t.x,t.y);
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
		vTex[id] = vec2(1.0f-t.x,t.y);
		vTan[id] = vec3(0.0f,0.0f,-1.0f);
		vBin[id] = vec3(0.0f,1.0f,0.0f);
		vNor[id] = vec3(-1.0f,0.0f,0.0f);

		id = offsetVertexRight + z*(seg.y+1) + y;
		vPos[id] = vec3(maxPos.x,minPos.y + size.y*t.y,minPos.z + size.z*t.x);
		vTex[id] = t;
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
		vTex[id] = vec2(t.x,1.0f-t.y);
		vTan[id] = vec3(1.0f,0.0f,0.0f);
		vBin[id] = vec3(0.0f,0.0f,-1.0f);
		vNor[id] = vec3(0.0f,-1.0f,0.0f);

		id = offsetVertexTop + x*(seg.z+1) + z;
		vPos[id] = vec3(minPos.x + size.x*t.x,maxPos.y,minPos.z + size.z*t.y);
		vTex[id] = t;
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
void					TexProject::Geometry::Mesh::CreateCylinder(float32 radius,float32 height,vec2 texSide,vec2 texCap,uvec2 segSide,uint32 segCap)
{
	if(segSide.x < 3) return;

	Create
	(
		(segSide.x+1)*(segSide.y+1) + ((segCap > 0) ? 2*segCap*(segSide.x+1) : 2*segSide.x),
		6*segSide.x*segSide.y + ((segCap > 0) ? 0 : 3*(segSide.x-2)) // todo
	);

	uint32 offsetVertexCap = (segSide.x+1)*(segSide.y+1);
	uint32 offsetIndexCap = 6*segSide.x*segSide.y;

	for(uint32 x = 0; x <= segSide.x; ++x)
	for(uint32 y = 0; y <= segSide.y; ++y)
	{
		float32 dx = float32(x) / float32(segSide.x);
		float32 dy = float32(y) / float32(segSide.y);
		uint32 id = y*(segSide.x+1)+x;
		vPos[id] = vec3(sinDg(360.0f * dx)*radius,-height*0.5f + height*dy,cosDg(360.0f * dx)*radius);
		vTex[id] = vec2(dx,dy)*texSide;
		vTan[id] = vec3(sinDg(360.0f * dx + 90.0f),0.0f,cosDg(360.0f * dx + 90.0f));
		vBin[id] = vec3(0.0f,1.0f,0.0f);
		vNor[id] = vec3(sinDg(360.0f * dx),0.0f,cosDg(360.0f * dx));
	}

	if(segCap > 0)
	{
		//vPos[offsetVertexCap] = vec3(0.0f,+height*0.5f,0.0f);
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
		}
		/*for(uint32 x = 0; x <= segSide.x-2; ++x)
		{
			uint32 i = offsetIndexCap + 3*x;
			vInd[i+0] = offsetVertexCap + 0;
			vInd[i+1] = offsetVertexCap + x + 1;
			vInd[i+2] = offsetVertexCap + x + 2;
		}*/
	}

	for(uint32 x = 0; x < segSide.x; ++x)
	for(uint32 y = 0; y < segSide.y; ++y)
	{
		uint32 i = y*segSide.x+x;
		vInd[i*6 + 0] = (y+0)*(segSide.x+1)+x;
		vInd[i*6 + 1] = (y+0)*(segSide.x+1)+x+1;
		vInd[i*6 + 2] = (y+1)*(segSide.x+1)+x;
		vInd[i*6 + 3] = vInd[i*6 + 1];
		vInd[i*6 + 4] = (y+1)*(segSide.x+1)+x+1;
		vInd[i*6 + 5] = vInd[i*6 + 2];
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






























