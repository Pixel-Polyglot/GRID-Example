#version 450 core

layout(local_size_x = 16, local_size_y = 16, local_size_z = 1) in;

layout(rgba32f) uniform image2D renderTexture;
layout(rgba8ui) uniform uimage2D gpuOutput;

void main() 
{
    ivec2 texelCoords = ivec2(gl_GlobalInvocationID.xy);

    uvec4 col = imageLoad(gpuOutput, ivec2(gl_GlobalInvocationID.x, gl_GlobalInvocationID.y));

    vec4 normalized = vec4(col.r / pow(2, 8), col.g / pow(2, 8), col.b / pow(2, 8), 1.0f);

    imageStore(renderTexture, texelCoords, normalized);
}