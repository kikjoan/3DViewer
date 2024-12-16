#version 330 core
out vec4 FragColor;

uniform vec4 vertexColor;          // Цвет точки
uniform bool isCircle;

void main() {
    FragColor = vertexColor;
    if (isCircle) {
        vec2 coord = gl_PointCoord - vec2(0.5);
        if(length(coord) > 0.5)
            discard;
    }
}