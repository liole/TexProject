#version 330 core


layout (points) in;
layout (triangle_strip, max_vertices = 4) out;


uniform mat4			ViewProjectionInverseMatrix;


out vec4	P_Tex;


void main()
{

	gl_Position = vec4(-1,-1,1,1);
	P_Tex = ViewProjectionInverseMatrix * gl_Position;
	EmitVertex();

	gl_Position = vec4(1,-1,1,1);
	P_Tex = ViewProjectionInverseMatrix * gl_Position;
	EmitVertex();

	gl_Position = vec4(-1,1,1,1);
	P_Tex = ViewProjectionInverseMatrix * gl_Position;
	EmitVertex();

	gl_Position = vec4(1,1,1,1);
	P_Tex = ViewProjectionInverseMatrix * gl_Position;
	EmitVertex();

    EndPrimitive();
}

