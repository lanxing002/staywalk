#version 330 core

// input data layout
in vec3 norm;
in vec2 texcoord;
in vec3 tangent;
in vec3 bitangent;
in vec3 light_pos;


// output data layout
out vec4 frag_color;  
// uniform sampler2D height;
uniform sampler2D height;
uniform sampler2D shadow;
uniform vec4 light;

// shader code  


#define NUM_SAMPLES 100
#define NUM_RINGS 10

#define EPS 1e-3
#define PI 3.141592653589793
#define PI2 6.283185307179586

highp float rand_1to1(highp float x ) { 
  // -1 -1
  return fract(sin(x)*10000.0);
}

highp float rand_2to1(vec2 uv ) { 
  // 0 - 1
	const highp float a = 12.9898, b = 78.233, c = 43758.5453;
	highp float dt = dot( uv.xy, vec2( a,b ) ), sn = mod( dt, PI );
	return fract(sin(sn) * c);
}

vec2 possion_disk[NUM_SAMPLES];
void poisson_sample( const in vec2 seed ) {

  float ANGLE_STEP = PI2 * float( NUM_RINGS ) / float( NUM_SAMPLES );
  float INV_NUM_SAMPLES = 1.0 / float( NUM_SAMPLES );

  float angle = rand_2to1( seed ) * PI2;
  float radius = INV_NUM_SAMPLES;
  float radius_step = radius;

  for( int i = 0; i < NUM_SAMPLES; i ++ ) {
    possion_disk[i] = vec2( cos( angle ), sin( angle ) ) * pow( radius, 0.75 );
    radius += radius_step;
    angle += ANGLE_STEP;
  }
}


float query_shaodw(){
    vec3 n = normalize(norm); 
    float bias = mix(0.0008, 0.0002, dot(n, light.xyz));
    ivec2 tex_size = textureSize(shadow, 0);
    vec2 inv_tex_size = 1.0 / vec2(tex_size);
    float sum = 0.0;
    for(int i = 0; i < NUM_SAMPLES; i++){
        vec2 sample_pos = possion_disk[i] * 4.0 * inv_tex_size + light_pos.xy;
        float d = texture(shadow, sample_pos).x;
        sum += (d + bias) < light_pos.z ? 0.0 : 1.0;
    }
    return sum / NUM_SAMPLES;
}

void main(){
    vec3 color = texture(height, texcoord).rrr;
    poisson_sample(texcoord);

    vec2 tsize = textureSize(height, 0);
    float step = 1.0 / tsize.x ;
    float hx1 = texture(height, texcoord + vec2(-step, .0)).x;
    float hx2 = texture(height, texcoord + vec2(step, .0)).x;
    float hy1 = texture(height, texcoord + vec2(.0, -step)).x;
    float hy2 = texture(height, texcoord + vec2(.0, +step)).x;

    vec3 vx = vec3((hx2 - hx1)/ (step * 2.0), 0.0, 1.0);
    vec3 vy = vec3(0.0, (hy2 - hy1)/ (step * 2.0), 1.0);
    vec3 n = normalize(vx + vy);
    float f = dot(n, light.xyz);
    frag_color.z = 1.0; 
    frag_color.xyz = vec3(f) * vec3(0.8, 0.6, 0.4);
    frag_color.xyz *= query_shaodw();
    frag_color.w = 1.0;
}