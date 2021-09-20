#version 400

#define PI 3.1415926535897932384626433832795
#define DIRECTIONAL 0.0

#define PHONG 0.0
#define GOURAUD 1.0
#define FLAT 2.0

struct LightSource{
        vec3 ambient, diffuse, specular;
        vec4 position; //if position[3] = 0 => light is directional
        vec3 spotDirection;
        float spotExponent, spotCutoff;
};

struct MaterialLighting{
        vec3 ambient, diffuse, specular;
        float shineness;
};

in LightSource o_transformedLightSource;
//in MaterialLighting o_glyphVertexColor;
uniform MaterialLighting u_materialLighting;

uniform float u_shadingModel;

//Expectator for Phong Model
in vec4 o_expectatorPosition;

//vertices characteristics
in vec4 o_transformedNormal;
in vec4 fragPos;

in vec4 o_gouraudColor;
flat in vec4 o_flatColor;

void setLighting(in float shadingModel, in LightSource source, in MaterialLighting material,
        in vec3 specularExpectator, in vec3 normal, in vec3 vertice,
        in vec4 gouraudColor, in vec4 flatColor,
        out vec4 resultColor);

out vec4 fragColor;
/*flat*/ in vec4 o_positionColorMap;

void main (void)
{
        /*setLighting(u_shadingModel, o_transformedLightSource, u_materialLighting/*o_glyphVertexColor,
        o_expectatorPosition.xyz, o_transformedNormal.xyz, fragPos.xyz,
        o_gouraudColor, o_flatColor,
        fragColor);*/

        fragColor = o_positionColorMap;
//        fragColor = vec4(0.0,0.0,0.0,1.0);
}


void setAmbientLight(in vec3 materialAmbientColor, in vec3 sourceAmbientColor, out vec3 resultAmbientColor);

void setDiffuseLight(in vec3 materialDiffuseColor, in vec3 sourceDiffuseColor, in float lightCategory,
                                     in vec3 lightLocation, in float spotExponent, in float spotCutoff, in vec3 normal, in vec3 vertice,
                                     out vec3 resultDiffuseColor, out vec3 lightDirection);

void setSpecularLight(in vec3 materialSpecularColor, in vec3 sourceSpecularColor, in vec3 lightDirection, in vec3 vertice,
                                          in vec3 expectatorPosition, in vec3 normal, in float shineness, out vec3 resultSpecularColor);

void setLighting(in float shadingModel, in LightSource source, in MaterialLighting material,
        in vec3 specularExpectator, in vec3 normal, in vec3 vertice,
        in vec4 gouraudColor, in vec4 flatColor,
        out vec4 resultColor)
{
        if (shadingModel == PHONG)
        {
                vec3 ambient, diffuse, specular;
                vec3 lightDirection; //variable calculated in diffuse color computation and needed in specular
                setAmbientLight(material.ambient, source.ambient, ambient);
                setDiffuseLight(material.diffuse, source.diffuse, source.position[3], source.position.xyz, source.spotExponent, source.spotCutoff, normal, vertice,
                        diffuse, lightDirection);
                setSpecularLight(material.specular, source.specular, lightDirection, vertice, specularExpectator, normal, material.shineness, specular);

                resultColor = vec4(ambient + diffuse + specular, 1.0);
        }
        else if (shadingModel == GOURAUD)
                resultColor = gouraudColor;
        else if (shadingModel == FLAT)
                resultColor = flatColor;
        else
                resultColor = vec4(1.0);
}

void setAmbientLight(in vec3 materialAmbientColor, in vec3 sourceAmbientColor, out vec3 resultAmbientColor)
{
        resultAmbientColor = materialAmbientColor*sourceAmbientColor;
}

void setDiffuseLight(in vec3 materialDiffuseColor, in vec3 sourceDiffuseColor, in float lightCategory,
                                     in vec3 lightLocation, in float spotExponent, in float spotCutoff, in vec3 normal, in vec3 vertice,
                                     out vec3 resultDiffuseColor, out vec3 lightDirection)
{
        float maxOpen = cos(PI*spotCutoff/180);
        lightDirection = vec3(0.0);
        if (lightCategory == DIRECTIONAL) //Is directional?
        {
                lightDirection = normalize(-lightLocation);
                resultDiffuseColor = max(dot(lightDirection, normal), 0.0)*materialDiffuseColor*sourceDiffuseColor;
        }
        else if (spotCutoff >= 0.0 && spotCutoff <= 90.0) // is spot?
        {
                lightDirection = normalize( lightLocation-vertice);

                if((dot(lightDirection, normal)) > maxOpen){
                        resultDiffuseColor = pow(max(dot(lightDirection, normal), 0.0), spotExponent)*materialDiffuseColor*sourceDiffuseColor;
                }
                else{
                        resultDiffuseColor = vec3(0.0);
                        lightDirection = vec3(0.0);
                }
        }
        else if (spotCutoff == 180.0) //is this punctual?
        {
                lightDirection = normalize(lightLocation - vertice);
                if(dot(lightDirection, normal) > 0.0)
                        resultDiffuseColor = dot(lightDirection, normal)*materialDiffuseColor*sourceDiffuseColor;
                else{
                        resultDiffuseColor = vec3(0.0);

                }
        }
}

void setSpecularLight(in vec3 materialSpecularColor, in vec3 sourceSpecularColor, in vec3 lightDirection, in vec3 vertice,
                                          in vec3 expectatorPosition, in vec3 normal, in float shineness, out vec3 resultSpecularColor)
{
        vec3 R = -lightDirection + 2*(dot(lightDirection, normal))*normal;
        vec3 V = normalize(expectatorPosition - vertice);

        if(dot(lightDirection, normal) > 0){
                resultSpecularColor = pow(max(dot(R,V), 0.0), shineness)*sourceSpecularColor*materialSpecularColor;
        }
        else
                resultSpecularColor = vec3(0.0);
}
