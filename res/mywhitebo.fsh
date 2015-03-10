
#ifdef GL_ES
precision mediump float;
#endif

uniform float time;
vec2 resolution;
float c;
vec2 position;

varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
//uniform sampler2D CC_Texture0;

void main(){
    resolution=vec2(1024.0,768.0);
    vec2 flame;
    flame.x=sin(CC_Time[1])*1.0;
    flame.y=sin(CC_Time[1])*1.0;
	

    position = ( gl_FragCoord.xy / resolution.xy );
	//position = position - 0.5;  //here I minus 0.5 because CCzero point on iPad is left courner.
	position.x *= resolution.x/resolution.y;
    position.x *= flame.x;
    position.y *= flame.y;
    c = sqrt(position.x*position.x+position.y*position.y);
    
    // pixel size
    vec2 onePixel2 = vec2(1.0 / 480.0, 1.0 / 320.0);
    
    // get v_texCoordate
    vec2 texCoord = v_texCoord;
    
    // exactly step follow the idea
    vec4 color;
    color.rgb = vec3(0.5);
    color -= texture2D(CC_Texture0, texCoord - onePixel2) * 5.0;
    color += texture2D(CC_Texture0, texCoord + onePixel2) * 5.0;
    // grayscale
    color.rgb = vec3((color.r + color.g + color.b) / 3.0);
    
    
    gl_FragColor = vec4(vec3(1.0 - c*4.0), 1.0 )* vec4(color.rgb, 1.0);
    
    
}

