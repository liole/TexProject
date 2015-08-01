#version 330 core


uniform int face;


layout (points) in;
layout (triangle_strip, max_vertices = 4) out;


out vec3	P_Tex;


void main()
{

	gl_Position = vec4(-1,-1,0,1);
	if(face == 0) P_Tex = vec3(1,-1,-1);
	if(face == 1) P_Tex = vec3(-1,-1,-1);
	if(face == 2) P_Tex = vec3(-1,1,-1);
	if(face == 3) P_Tex = vec3(-1,-1,-1);
	if(face == 4) P_Tex = vec3(-1,-1,1);
	if(face == 5) P_Tex = vec3(-1,-1,-1);
	EmitVertex();

	gl_Position = vec4(1,-1,0,1);
	if(face == 0) P_Tex = vec3(1,1,-1);
	if(face == 1) P_Tex = vec3(-1,1,-1);
	if(face == 2) P_Tex = vec3(1,1,-1);
	if(face == 3) P_Tex = vec3(1,-1,-1);
	if(face == 4) P_Tex = vec3(1,-1,1);
	if(face == 5) P_Tex = vec3(1,-1,-1);
	EmitVertex();

	gl_Position = vec4(-1,1,0,1);
	if(face == 0) P_Tex = vec3(1,-1,1);
	if(face == 1) P_Tex = vec3(-1,-1,1);
	if(face == 2) P_Tex = vec3(-1,1,1);
	if(face == 3) P_Tex = vec3(-1,-1,1);
	if(face == 4) P_Tex = vec3(-1,1,1);
	if(face == 5) P_Tex = vec3(-1,1,-1);
	EmitVertex();

	gl_Position = vec4(1,1,0,1);
	if(face == 0) P_Tex = vec3(1,1,1);
	if(face == 1) P_Tex = vec3(-1,1,1);
	if(face == 2) P_Tex = vec3(1,1,1);
	if(face == 3) P_Tex = vec3(1,-1,1);
	if(face == 4) P_Tex = vec3(1,1,1);
	if(face == 5) P_Tex = vec3(1,1,-1);
	EmitVertex();

    EndPrimitive();
}

