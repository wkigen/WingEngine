uniform sampler2D u_texture0;
uniform sampler2D u_texture1;

uniform vec3 u_viewPosition;

uniform int u_lightNum = 0;
uniform int u_lightType[5];
uniform vec3 u_lightPosition[5];
uniform vec3 u_lightDirection[5];
uniform vec4 u_lightColor[5];
uniform mat4 u_lightMVPMatrtix[5];
uniform float u_shiness[5];

uniform vec3 u_ambient;
uniform vec3 u_diffuse;
uniform vec3 u_specular;

uniform int u_isShadow;

varying vec4 v_worldPos;
varying vec3 v_normal;
varying vec2 v_textureCoordinate;

vec3 lightdir = vec3(0,0,0);
vec3 normal= vec3(0,0,0);

float amb = 0.3;
float diff = 0.4;
float spec = 0.3;

float diffusefract = 1.0;
float specularfract = 0.0;

float factorShadow = 0.0;  

//光源到物体的方向
vec3 getLightDirection(int lightType,vec3 lightPos,vec3 lightDir,vec3 desPos)
{
    if(lightType == 1)//点光源
    {
        return normalize(lightPos - desPos);
    }
    else if(lightType == 2) //平行光
    {
        return normalize(lightDir);
    }
    else
    {
        return normalize(lightDir);
    }
}

void init()
{
    vec4 pos = v_worldPos / v_worldPos.w;
    lightdir = getLightDirection(u_lightType[0],u_lightPosition[0],u_lightDirection[0],pos.xyz);

    normal = v_normal;

    lightdir = normalize(lightdir);
    normal = normalize(normal);
}

void calLight()
{
    if(u_lightNum == 0)
        return;

    vec4 pos = v_worldPos / v_worldPos.w;

    //开始计算光照
    vec3 eyedir = normalize(u_viewPosition - pos.xyz);
    vec3 halfvec = normalize(lightdir + eyedir);

    diffusefract = max(dot(lightdir, normal), 0.0);
    if (diffusefract > 0.0)
    {
        halfvec = normalize(halfvec);
        specularfract = max(dot(halfvec, normal), 0.0);
        specularfract = pow(specularfract, u_shiness[0]);
    }

}

void calShadow()
{
    vec4 light0pos = u_lightMVPMatrtix[0] * v_worldPos;
    float bias = max(0.05 * (1.0 - dot(normal, lightdir)), 0.005); 
    vec3 projCoords = light0pos.xyz / light0pos.w ;
    projCoords = projCoords * 0.5 + 0.5;
    float closestDepth = texture2D(u_texture1, projCoords.xy).r; 
    float currentDepth = projCoords.z ;
    factorShadow = currentDepth - bias > closestDepth ? 1.0 : 0.0;
}

void main()
{
    init();
    calLight();
    calShadow();
    vec3 text = texture2D(u_texture0, v_textureCoordinate).rgb;

    vec3 lighting = (amb * text * u_ambient + (1.0 - factorShadow) * (diff * text * diffusefract *u_diffuse + spec * text * specularfract * u_specular)) * text;
    gl_FragColor = vec4(lighting, 1.0); 
}