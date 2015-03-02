
attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 TextureCoord;

varying vec4 DestinationColor;
varying vec2 v_texCoord;

void main(){
    
    DestinationColor = a_color;
    v_texCoord = TextureCoord;
    gl_Position = CC_MVPMatrix * a_position;

}