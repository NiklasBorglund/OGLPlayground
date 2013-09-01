#version 330

layout (location = 0) in vec3 position;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 cameraPosition;

uniform vec4 quadOffset;	 // .y holds the center of the AABB
uniform vec4 quadScale;		// .y holds the current LOD level
uniform vec2 quadWorldMax;	// .xz max used to clamp triangles outside of world range

uniform vec3 gridDim;		 // .x = gridDim, .y = gridDimHalf, .z = oneOverGridDimHalf
uniform vec4 terrainScale;
uniform vec4 terrainOffset;
uniform vec2 samplerWorldToTextureScale;
uniform vec4 heightMapTextureInfo;
uniform vec3 lightDirection;

uniform vec4 morphConsts;

uniform sampler2D diffuseTexture;
out vec2 texCoordOut;
out float lightingFactor;

// returns baseVertexPos where: xy are true values, z is g_quadOffset.z which is z ce18:55 2013-08-24nter of the AABB
vec4 getBaseVertexPos( vec4 inPosition )
{
   vec4 returnValue = inPosition * quadScale + quadOffset;
   returnValue.xz = min(returnValue.xz, quadWorldMax );
   return returnValue;
}

//morphs vertex .xy from high to low detailed mesh position
vec2 morphVertex(vec4 inPosition, vec2 vertex, float morphLerpValue)
{
  vec2 decimals = (fract(inPosition.xz * vec2(gridDim.y, gridDim.y)) * vec2(gridDim.z, gridDim.z)) * quadScale.xz;
  return vertex.xy - decimals * morphLerpValue;
  //vec2 decimals = (fract(inPosition.xz * vec2(gridDim.x, gridDim.x) * 0.5) * 1.0 / vec2(gridDim.x, gridDim.x)); 
  //return vertex.xy - decimals * quadScale.xz * morphLerpValue;
}

//Calculate the global texture coordinates
vec2 calculateGlobalUV(vec2 vertex)
{
  vec2 globalUV = (vertex.xy - terrainOffset.xz) / terrainScale.xz;
  globalUV *= samplerWorldToTextureScale;
  globalUV += heightMapTextureInfo.zw * 0.5;
  return globalUV;
}

float sampleHeightmap(vec2 uv, float mipLevel)
{
   vec2 textureSize = heightMapTextureInfo.xy;
   vec2 texelSize = heightMapTextureInfo.zw;

   uv = uv.xy * textureSize - vec2(0.5,0.5);
   vec2 uvf = floor(uv.xy);
   vec2 f = uv - uvf;
   uv = (uvf + vec2(0.5, 0.5)) * texelSize;

   float t00 = textureLod(diffuseTexture, uv, mipLevel).x;
   float t10 = textureLod(diffuseTexture, vec2(uv.x + texelSize.x, uv.y), mipLevel).x;

   float tA = mix(t00, t10, f.x);

   float t01 = textureLod(diffuseTexture, vec2(uv.x, uv.y + texelSize.y), mipLevel).x;
   float t11 = textureLod(diffuseTexture, vec2(uv.x + texelSize.x, uv.y + texelSize.y), mipLevel).x;

   float tB = mix(t01, t11, f.x);

   return mix(tA, tB, f.y);
}

vec3 GetNormal(vec2 uv)
{
    vec2 texelSize = heightMapTextureInfo.zw;
    float n = sampleHeightmap(uv + vec2(0, -texelSize.x),0) * 0.2;
    float s = sampleHeightmap(uv + vec2(0, texelSize.x),0) * 0.2;
    float e = sampleHeightmap(uv + vec2(-texelSize.y, 0),0) * 0.2;
    float w = sampleHeightmap(uv + vec2(texelSize.y, 0),0) * 0.2;

    //vec3 ew = normalize(vec3(2*texelSize.x, e-w, 0));
   // vec3 ns = normalize(vec3(0,n-s, 2* texelSize.y));
    //vec3 result = cross(ew, ns);

    vec3 sn = vec3(0,(s-n), -(texelSize.y * 2.0));
    vec3 ew = vec3(-(texelSize.x * 2.0), (e - w), 0);
    sn *= (texelSize.y * 2.0);
    ew *= (texelSize.x * 2.0);
    
    sn = normalize(sn);
    ew = normalize(ew);

    vec3 result = normalize(cross(sn, ew));

    return result;
}

void main()
{
  vec4 unmorphedWorldPosition;
  vec4 worldPosition;
  vec2 globalUV;
  float eyeDistance;

  vec4 vertex = getBaseVertexPos(vec4(position,1.0));
  vec2 preGlobalUV = calculateGlobalUV(vertex.xz);
  vertex.y = sampleHeightmap(preGlobalUV, 0) * terrainScale.y + terrainOffset.y;
 
  unmorphedWorldPosition = vertex;
  unmorphedWorldPosition.w = 1;

  eyeDistance = distance(vertex.xyz,cameraPosition);
  float morphLerpValue = 1.0 - clamp(morphConsts.z - eyeDistance * morphConsts.w, 0.0, 1.0);

  vertex.xz = morphVertex(vec4(position,1.0), vertex.xz, morphLerpValue);

  globalUV = calculateGlobalUV(vertex.xz);
  vertex.y = sampleHeightmap(globalUV, 0) * terrainScale.y + terrainOffset.y; 
  vertex.w = 1.0;

 // vec3 eyeDirection = normalize(cameraPosition - vertex.xyz);
	
  gl_Position = projectionMatrix * viewMatrix * vertex;
  texCoordOut = globalUV;

  vec3 normal = GetNormal(globalUV);
  normal = normalize(normal * terrainScale.xyz);
  lightingFactor = clamp(dot(normal, lightDirection), 0.0, 1.0);
  //if(morphLerpValue > 0.0)
  {
    //lightingFactor = morphLerpValue;
  }
}

