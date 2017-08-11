uniform int u_lightNum = 0;
//uniform int u_lightType[5];
uniform vec3 u_lightPosition[5];

varying vec4 v_worldPos;

float depth = 0.0;

void calDepth()
{
    vec4 pos = v_worldPos / v_worldPos.w;
    depth = distance(u_lightPosition[0].xyz,pos.xyz);
}

void main()
{
    calDepth();
    gl_FragColor = vec4(depth,depth/255.0,depth/65535.0,1.0);
}