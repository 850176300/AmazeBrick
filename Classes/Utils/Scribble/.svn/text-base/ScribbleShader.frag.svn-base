//
//  ScribbleShader.frag
//
//
//  Created by renhong on 7/24/14.
//
//

const char* ScribbleShader_frag = STRINGIFY(
\n#ifdef GL_ES\n
precision lowp float;
\n#endif\n
                                                    
varying vec4 v_fragmentColor;
varying vec2 v_texCoord;

uniform sampler2D s_texture_brush;
uniform sampler2D s_texture_target;
uniform float f_alpha_value_brush;
uniform float f_alpha_value_target;
uniform vec2 v_texCoord_target;
uniform vec2 v_texSize_brush;
uniform vec2 v_texSize_target;
uniform int v_solid_brush;

void main()
{
    vec4 texColor = texture2D(s_texture_brush, v_texCoord);
    
	// mimic: glAlphaFunc(GL_GREATER)						
	// pass if ( incoming_pixel >= f_alpha_value_brush ) => fail if incoming_pixel < f_alpha_value_brush                  
    
	if ( texColor.a <= f_alpha_value_brush )						
        discard;
    vec2 v_texCoord2 = (v_texCoord_target + v_texCoord * v_texSize_brush) / v_texSize_target;
    vec4 texColor1 = texture2D(s_texture_target, v_texCoord2);
    
    // mimic: glAlphaFunc(GL_GREATER)
	// pass if ( incoming_pixel >= f_alpha_value_brush ) => fail if incoming_pixel < f_alpha_value_brush
    if ( texColor1.a < f_alpha_value_target )
        discard;

	vec4 lColor = v_fragmentColor * texColor1;
    if(0 != v_solid_brush)
    {
        gl_FragColor = lColor;
    }
    else
    {
        float lRate = distance(v_texCoord, vec2(0));
        lRate /= 2.0;
        gl_FragColor =  vec4(lColor.r, lColor.g, lColor.b, lColor.a * lRate);
    }
}
);
