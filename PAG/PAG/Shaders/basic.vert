#version 440 core
layout (location = 0) in vec3 position; // zmienna position ma lokalizacjê 0
layout (location = 1) in vec3 color;  // zmienna color ma lokalizacjê 1
  
out vec3 ourColor; // przeka¿ kolor do FS
void main()
{
    gl_Position = vec4(position, 1.0);
    ourColor = color; // ustaw ourColor na kolor wejœciowy z atrybutu wierzcho³ka
}