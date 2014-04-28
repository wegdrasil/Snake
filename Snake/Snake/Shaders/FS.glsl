#version 420

in vec2 texcoord;
out vec4 fragColor;

uniform sampler2D uTexture;

uniform vec4 uColor;

void main(void)
{
	vec4 texColor = texture(uTexture, texcoord);
	
	if(texColor.a < 0.05 )
		discard;
	else
		fragColor = uColor + texColor; 
}
