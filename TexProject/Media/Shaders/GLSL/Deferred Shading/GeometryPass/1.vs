#version 330 core


uniform mat3 RotateMatrix;
uniform mat4 ModelMatrix;
uniform mat4 ModelViewProjectionMatrix;


in vec3	vPos;
in vec3	vTan;
in vec3	vBin;
in vec3	vNor;
in vec2	vTex;


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

