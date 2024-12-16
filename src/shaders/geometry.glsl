#version 330 core

layout(lines) in;  // Входные линии (по две вершины)
layout(triangle_strip, max_vertices = 4) out;  // Выход — 4 вершины на прямоугольник

uniform float lineWidth;  // Толщина линии в пикселях

void main() {
    // Получаем входные вершины
    vec4 p0 = gl_in[0].gl_Position;  // Первая вершина линии
    vec4 p1 = gl_in[1].gl_Position;  // Вторая вершина линии

    // Вычисляем направление линии и нормаль
    vec2 dir = normalize(p1.xy - p0.xy);  // Направление линии
    vec2 normal = vec2(-dir.y, dir.x);                 // Перпендикуляр к линии

    // Увеличиваем нормаль на половину ширины линии
    normal *= lineWidth * 0.5;

    // Генерируем вершины прямоугольника
    vec4 offset0 = vec4(normal, 0.0, 0.0);
    vec4 offset1 = vec4(-normal, 0.0, 0.0);

    gl_Position = p0 + offset0;  // Верхняя левая вершина
    EmitVertex();

    gl_Position = p0 + offset1;  // Нижняя левая вершина
    EmitVertex();

    gl_Position = p1 + offset0;  // Верхняя правая вершина
    EmitVertex();

    gl_Position = p1 + offset1;  // Нижняя правая вершина
    EmitVertex();

    EndPrimitive();
}