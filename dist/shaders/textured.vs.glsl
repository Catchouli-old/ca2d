precision mediump float;

uniform float in_time;

attribute vec3 in_vertex_position;
attribute vec2 in_texture_coords;

varying vec2 texture_coords;

void main()
{
	gl_Position = vec4(in_vertex_position, 1.0);
	
	gl_Position.x += 0.5 * sin(gl_Position.y + in_time);

    // Pass texture coords to fragment shader
    texture_coords = in_texture_coords;
}