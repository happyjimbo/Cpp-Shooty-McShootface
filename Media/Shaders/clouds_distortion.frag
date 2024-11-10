#version 120

uniform sampler2D texture;
uniform sampler2D noiseTexture;
uniform float time;

vec2 applyDistortion(vec2 uv, float time, sampler2D noiseTexture)
{
    float looptime = sin(time * 0.628);

    vec2 noiseUV = uv * 3.0 + looptime * 0.5;
    vec3 noise = texture2D(noiseTexture, noiseUV).rgb;
    vec2 displacedUV = uv + (noise.rg - 0.1) * 0.01;
    return displacedUV;
}

void main()
{
    vec2 uv = gl_TexCoord[0].xy;
    vec2 displacedUV = applyDistortion(uv, time, noiseTexture);
    vec4 color = texture2D(texture, displacedUV);

    gl_FragColor = color;
}