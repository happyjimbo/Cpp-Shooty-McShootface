#version 120

uniform sampler2D texture;
uniform sampler2D noiseTexture;
uniform float time;

void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    vec2 noiseUV = uv * 3.0 + time * 0.1;
    vec3 noise = texture2D(noiseTexture, noiseUV).rgb;
    vec2 displacedUV = uv + (noise.rg - 0.5) * 0.05;
    vec4 color = texture2D(texture, displacedUV);

    gl_FragColor = color;
}