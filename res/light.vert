
attribute vec4 a_position;
attribute vec4 a_color;
attribute vec2 a_texCoord;
uniform vec2 inputposition;

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

    float distance;
    gl_Position = CC_MVPMatrix * a_position;
    v_fragmentColor = a_color;
    v_texCoord = a_texCoord;
    v_alpha = 0.0;
    if (inputposition.y < a_position.y) {
        distance = a_position.y - inputposition.y;
        v_alpha = distance * 2.0 / a_position.y;
    }else{
        distance = inputposition.y - a_position.y;
        v_alpha = (a_position.y - distance)/a_position.y;
    }
    
}
