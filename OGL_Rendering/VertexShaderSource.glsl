#version 330 core
layout(location = 0) in vec3 position; //Position variable has attribute position 0
layout(location = 1) in vec3 color; //Color variable has a ttribute position 1
layout(location = 2) in vec2 texCoord;

out vec3 ourColor; //Output a color to the fragment shader
out vec2 TexCoord;

void main()
{
	gl_Position = vec4(position.x, position.y, position.z, 1.0);
	ourColor = color; //set ourColor the input color we got from the vertex data
                    //instead of using uniform variable
	//Flip y axis of texture coordinate
	TexCoord = vec2(texCoord.x, texCoord.y * -1.0);
}
