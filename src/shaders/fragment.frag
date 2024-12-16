#version 330 core
out vec4 FragColor;

uniform float uGapSize;      // Длина пробела
uniform vec4 surfColor;          // Цвет линий и заливки

void main() {

    float factor = mod(gl_FragCoord.x + gl_FragCoord.y, uGapSize * 2);

     if (uGapSize < 0.1) {
         FragColor = surfColor;
     } else if (factor < uGapSize) {
         FragColor = surfColor;  // Цвет линии
     } else {
         discard;  // Пропускаем фрагмент для создания пробела
     }
}