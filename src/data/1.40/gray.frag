#version 140
uniform sampler2D sampler;
uniform vec4 modulation;
uniform float saturation;
in vec2 texcoord0;

out vec4 fragColor;

void main()
{
    vec4 tex = texture2D(sampler, texcoord0);
    if (saturation != 1.0) {
        vec3 desaturated = tex.rgb * vec3( 0.30, 0.59, 0.11 );
        desaturated = vec3( dot( desaturated, tex.rgb ));
        tex.rgb = tex.rgb * vec3( saturation ) + desaturated * vec3( 1.0 - saturation );
    }
    tex = vec4(vec3(dot(tex.rgb, vec3(0.2126, 0.7152, 0.0722))), tex.a);
    tex *= modulation;
    tex.rgb *= tex.a;
    fragColor = tex;
}
