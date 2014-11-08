precision mediump float;

uniform sampler2D sampler;

varying vec2 texture_coords;

void main()
{
    gl_FragColor = texture2D(sampler, texture_coords);
}