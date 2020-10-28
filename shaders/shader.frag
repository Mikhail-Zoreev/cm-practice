float func(float x)
{
    float result = 0.25 * x * x;
    return result;
}

void main(void)
{
    if ((func(gl_FragCoord.x - 1.0) < gl_FragCoord.y) && (gl_FragCoord.y< func(gl_FragCoord.x + 1.0)))
        {
            gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
        }
        else
        {
            gl_FragColor= vec4(1.0, 1.0, 1.0, 1.0);
        }
}

