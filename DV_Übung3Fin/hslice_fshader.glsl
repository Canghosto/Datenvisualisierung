#version 330
uniform sampler2D texture;
smooth in vec2 texCoord;

void main()
{
    gl_FragColor = texture2D(texture, texCoord);
}
