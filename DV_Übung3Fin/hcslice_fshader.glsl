#version 330
uniform sampler2D linesegment;
smooth in vec2 texCoord;

void main(void)
{
    gl_FragColor = texture2D(linesegment, texCoord);
}

