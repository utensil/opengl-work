precision highp float;

uniform float theta;

attribute vec2 position;

void main() {

  //rotate position by theta radians about the origin

  float c = cos(theta);
  float s = sin(theta);

  //  rotatation_matrx is | c    -s|
  //                      | s    c|
  // but glsl matrix constructor is column-major

  mat2 rotatation_matrx = mat2(c, s, -s, c);

  gl_Position = vec4(rotatation_matrx * position, 0, 1.0);
}
