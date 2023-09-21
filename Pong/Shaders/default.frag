#version 460 core
out vec4 FragColor;

in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
   vec4 texColor = texture(tex0, texCoord);
   if (texColor.a < 0.5){
		discard;
   }
   else{
		FragColor = texColor;
   }
   //FragColor = vec4(color, 1.0f);
   //FragColor = vec4(1.0f);
}