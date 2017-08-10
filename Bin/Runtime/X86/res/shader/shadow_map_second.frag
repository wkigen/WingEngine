uniform sampler2D u_texture0;
uniform sampler2D u_texture1;

uniform vec3 u_viewPosition;

uniform int u_lightNum = 0;
uniform int u_lightType[5];
uniform vec3 u_lightPosition[5];
uniform vec3 u_lightDirection[5];
uniform vec4 u_lightColor[5];
uniform mat4 u_lightMVPMatrtix[5];

uniform float u_shiness;
uniform vec3 u_ambient;
uniform vec3 u_diffuse;
uniform vec3 u_specular;

uniform int u_isShadow;

varying vec4 v_worldPos;
varying vec3 v_normal;
varying vec2 v_textureCoordinate;

float amb = 0.3;
float diff = 0.4;
float spec = 0.3;

float diffusefract = 1.0;
float specularfract = 0.0;

float factorShadow = 1.0;  

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

void calLight()
{
    if(u_lightNum == 0)
        return;

    vec3 normal = v_normal;
    vec4 pos = v_worldPos / v_worldPos.w;

    //开始计算光照
    vec3 lightdir = getLightDirection(u_lightType[0],u_lightPosition[0],u_lightDirection[0],pos.xyz);
    vec3 eyedir = normalize(u_viewPosition - pos.xyz);
    vec3 halfvec = normalize(lightdir + eyedir);

    lightdir = normalize(lightdir);
    normal = normalize(normal);
    diffusefract = max(dot(lightdir, normal), 0.0);
    if (diffusefract > 0.0)
    {
        halfvec = normalize(halfvec);
        specularfract = max(dot(halfvec, normal), 0.0);
        specularfract = pow(specularfract, u_shiness);
    }

}

void calShadow()
{
    vec4 pos = v_worldPos / v_worldPos.w;
    vec4 light0pos = u_lightMVPMatrtix[0] * pos;
    vec2 depthTexCoord = (light0pos.xy / light0pos.w + vec2(1.0,1.0))*0.5;
    float lengthToLight = distance(u_lightPosition[0].xyz,pos.xyz);
    vec4 vd = texture2D(u_texture1,depthTexCoord);
    float depth = vd.x +vd.y*255.0+vd.z*65535.0;
    if (lengthToLight > depth)//阴影判断  
        factorShadow = 0.5; 
}

void main()
{
    calLight();
    calShadow();
    vec3 text = texture2D(u_texture0, v_textureCoordinate).rgb;
    gl_FragColor = vec4(amb * text * u_ambient + diff * text * diffusefract *u_diffuse + spec * text * specularfract * u_specular, 1.0) * factorShadow;
    //gl_FragColor = texture2D(u_texture1, v_textureCoordinate);
}