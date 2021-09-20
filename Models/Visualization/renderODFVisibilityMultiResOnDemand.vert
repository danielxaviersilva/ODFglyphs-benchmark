#version 400

in vec3 vertex;
uniform float u_scale;


uniform sampler2D u_ODFMap;
uniform uint u_cols;
//in vec3 instance_displacement;
in uint instance_index;


uniform float u_shadingModel;




uniform mat4 u_projectionMatrix;
uniform mat4 u_modelViewMatrix;

out vec4 fragPos;

/*flat*/ out vec4 o_positionColorMap;



void main(void)
{
    uvec2 gridPosition = uvec2(instance_index%u_cols, instance_index/u_cols);
    vec3 displacement = vec3(2.f*gridPosition.x/(float(u_cols)) -1.f + 1.f/(float(u_cols)),
                             -2.f*gridPosition.y/(float(u_cols)) +1.f - 1.f/(float(u_cols)),
                              0.f);



    float vertexODFMap = texelFetch(u_ODFMap,ivec2((gl_VertexID)/8, gl_InstanceID), 0)[(gl_VertexID%8)/2];
    vec3 normalizedvertex = normalize(vec3(vertex));
    o_positionColorMap = vec4(abs(normalizedvertex.x), abs(normalizedvertex.y), abs(normalizedvertex.z), 1.0);
//    vec4 instanceVertex = vec4((vertexODFMap*u_scale*vertex).xyz + instance_displacement, 1.0);
    vec4 instanceVertex = vec4((vertexODFMap*u_scale*vertex).xyz + displacement, 1.0);
    fragPos = u_projectionMatrix*u_modelViewMatrix*instanceVertex;
    gl_Position = fragPos;
}
