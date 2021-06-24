#version 400
in vec3 vertex;
uniform float u_scale;
in vec3 displacement;
uniform float u_shadingModel;
uniform mat4 u_projectionMatrix;
uniform mat4 u_modelViewMatrix;
/*flat*/ out vec4 o_positionColorMap;

void main(void)
{
    if( vertex.x != 0.0 || vertex.y != 0.0 || vertex.z != 0.0 ) {
        vec3 normalizedvertex = normalize(vec3(vertex));
        o_positionColorMap = vec4(abs(normalizedvertex.x), abs(normalizedvertex.y), abs(normalizedvertex.z), 1.0);
    } else {
        o_positionColorMap = vec4(1.0);
    }
    vec4 instanceVertex = vec4(u_scale*vertex.xyz + displacement.xyz, 1.0);
    gl_Position = u_projectionMatrix*u_modelViewMatrix*instanceVertex;
}
