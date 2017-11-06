#version 330 core

attribute vec3 position;
attribute vec2 textureCoords;
attribute vec3 normal;

out vec2 pass_textureCoords;
out vec3 surfaceNormal;
out vec3 toLightSource;
out vec3 toCameraVector;

uniform mat4 transformationMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 lightPosition;

uniform float fogDensity;
uniform float fogGradient;
out float visibility;

void main() {
    vec4 worldPosition = transformationMatrix * vec4(position.xyz, 1);
    vec4 positionRelativeToCam = viewMatrix * worldPosition;

    gl_Position = projectionMatrix * positionRelativeToCam;

    pass_textureCoords = textureCoords;

    surfaceNormal = (transformationMatrix * vec4(normal, 0.0f)).xyz;
    toLightSource = lightPosition - worldPosition.xyz;
    toCameraVector = (inverse(viewMatrix) * vec4(0, 0, 0, 1)).xyz - worldPosition.xyz;

    float distance = length(positionRelativeToCam.xyz);
    visibility = exp(-pow((distance * fogDensity), fogGradient));
    visibility = clamp(visibility, 0.0, 1.0);
}
