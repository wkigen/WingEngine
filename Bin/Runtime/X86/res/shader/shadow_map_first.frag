varying float v_depth;

void main()
{
    gl_FragColor = vec4(v_depth,v_depth/255,v_depth/65535,1.0);
}