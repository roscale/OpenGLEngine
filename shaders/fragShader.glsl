#version 330 core

out vec4 outColor;

in vec2 pass_textureCoords;
in vec3 surfaceNormal;
in vec3 toLightSource;
in vec3 toCameraVector;

uniform sampler2D textureSampler;
uniform vec3 lightColor;
uniform float shineDamper;
uniform float reflectivity;

in float visibility;
uniform vec3 skyColor;


void main() {
    vec4 pixelColor = texture(textureSampler, pass_textureCoords);

    if (pixelColor.a == 0.0)
        discard;

    vec3 unitNormal = normalize(surfaceNormal);
    vec3 unitLightVector = normalize(toLightSource);

    // Diffuse lighting
    float nDot1 = dot(unitNormal, unitLightVector);
    float brightness = max(nDot1, 0.2);
    vec3 diffuse = brightness * lightColor;

    // Specular lighting
    vec3 unitVectorToCamera = normalize(toCameraVector);
    vec3 lightDirection = -unitLightVector;
    vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);

    float specularFactor = dot(reflectedLightDirection, unitVectorToCamera);
    specularFactor = max(specularFactor, 0.0);
    float dampedFactor = pow(specularFactor, shineDamper);
    vec3 finalSpecular = dampedFactor * reflectivity * lightColor;

    outColor = vec4(diffuse, 1.0) * pixelColor + vec4(finalSpecular, 1.0);
    outColor = mix(vec4(skyColor, 1.0), outColor, visibility);
}
