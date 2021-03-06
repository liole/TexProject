#version 330 core


layout (points) in;
layout (triangle_strip, max_vertices = 4) out;


uniform mat4			ViewProjectionInverseMatrix;


out vec4	pView;
out vec2	pTex;


void main()
{

	gl_Position = vec4(-1,-1,1,1);
	pView = ViewProjectionInverseMatrix * gl_Position;
	pTex = vec2(0,0);
	EmitVertex();

	gl_Position = vec4(1,-1,1,1);
	pView = ViewProjectionInverseMatrix * gl_Position;
	pTex = vec2(1,0);
	EmitVertex();

	gl_Position = vec4(-1,1,1,1);
	pView = ViewProjectionInverseMatrix * gl_Position;
	pTex = vec2(0,1);
	EmitVertex();

	gl_Position = vec4(1,1,1,1);
	pView = ViewProjectionInverseMatrix * gl_Position;
	pTex = vec2(1,1);
	EmitVertex();

    EndPrimitive();
}

