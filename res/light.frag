#ifdef GL_ES
varying lowp vec4 v_fragmentColor
varying mediump vec2 v_texCoord;
varying lowp vec4 v_alpha;
#else
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;
varying float v_alpha;
#endif

void main(){
    
    vec4 color;
    color = v_fragmentColor * texture2D(CC_Texture0, v_texCoord);
    color.a = v_alpha * color.a;
    gl_FragColor = color;
    
}