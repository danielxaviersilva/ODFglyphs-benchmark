#version 400
in vec3 vertex;
uniform float u_scale;


uniform sampler2D u_ODFMap;

in vec3 instance_displacement;

uniform mat4 u_projectionMatrix;
uniform mat4 u_modelViewMatrix;

out vec4 fragPos;
/*flat*/ out vec4 o_positionColorMap;


void main(void) 
{
    float vertexODFMap = texelFetch(u_ODFMap, ivec2(gl_VertexID, gl_InstanceID), 0)[0];
    vec3 normalizedvertex = normalize(vec3(vertex));
    o_positionColorMap = vec4(abs(normalizedvertex.x), abs(normalizedvertex.y), abs(normalizedvertex.z), 1.0);
    vec4 instanceVertex = vec4((vertexODFMap*u_scale*vertex).xyz + instance_displacement, 1.0);
    fragPos = u_projectionMatrix*u_modelViewMatrix*instanceVertex;
    gl_Position = fragPos;
}

