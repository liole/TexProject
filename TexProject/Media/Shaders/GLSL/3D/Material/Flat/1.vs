#version 330 core


uniform mat4 ModelViewProjectionMatrix;


in vec3	vPos;
in vec2	vTex;


out vec2	pTex;


void main()
{
	gl_Position = ModelViewProjectionMatrix * vec4(vPos,1.0f);
	pTex = vTex;
}

