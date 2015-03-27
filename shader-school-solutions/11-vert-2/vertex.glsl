precision highp float;

attribute vec4 position;
attribute vec3 color;
varying vec4 fragColor;

void main() {
  gl_Position = position;
  fragColor = vec4(color, 1.0);
}
