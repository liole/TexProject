#version 330 core


uniform mat3 RotateMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ModelViewProjectionMatrix;


layout(location = 0) in vec3	vPos;
layout(location = 1) in vec2	vTex;
layout(location = 2) in vec3	vTan;
layout(location = 3) in vec3	vBin;
layout(location = 4) in vec3	vNor;


out vec3	pPos;
out vec2	pTex;
out mat3	pTBN;


void main()
{
	gl_Position = ModelViewProjectionMatrix * vec4(vPos,1.0f);
	pPos = (ModelMatrix * vec4(vPos,1.0f)).xyz;
	pTex = vTex;
	pTBN[0] = RotateMatrix * vTan;
	pTBN[1] = RotateMatrix * vBin;
	pTBN[2] = RotateMatrix * vNor;
}
