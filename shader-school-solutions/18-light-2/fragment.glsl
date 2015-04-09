precision mediump float;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 inverseModel;
uniform mat4 inverseView;
uniform mat4 inverseProjection;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 lightDirection;

varying vec3 fragNormal;

// all incoming light is traveling in the same direction, d. Then Lambert's cosine law 
// says that the amount of diffuse light emitted from a point the surface with a normal
// vector n is proportional to the following weight:
float lambertWeight(vec3 n, vec3 d) {
  return max(dot(n, d), 0.0);
}

// the light reflected at a point on the surface:
vec3 reflectedLight(
  vec3 normal,
  vec3 lightDirection,
  vec3 ambient,
  vec3 diffuse
) {
  float brightness = lambertWeight(normal, lightDirection);
  return ambient + diffuse * brightness;
}

void main() {
  gl_FragColor = vec4(reflectedLight(fragNormal, lightDirection, ambient, diffuse), 1);
}