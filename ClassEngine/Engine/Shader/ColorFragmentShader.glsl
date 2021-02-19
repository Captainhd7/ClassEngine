#version 450 core

in vec3 Normal;
in vec2 TexCoords;
in vec3 Color;

out vec4 fColor;

void main(){
	fColor = vec3(Color, 1.0f);
}