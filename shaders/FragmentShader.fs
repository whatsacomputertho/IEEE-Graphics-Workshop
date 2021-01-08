#version 120

uniform vec2 resolution;

void main()
{
	vec2 st = gl_FragCoord.xy/resolution;
	gl_FragColor = vec4(0.25, st.y * gl_FragCoord.w, st.x * gl_FragCoord.w, 1.0);
}