
varying vec4 DestinationColor;
varying vec2 v_texCoord;

void main(){

    gl_FragColor = DestinationColor * texture2D(CC_Texture0, v_texCoord);

}