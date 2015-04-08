precision mediump float;

attribute vec3 position;
attribute vec3 normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform mat4 inverseModel;
uniform mat4 inverseView;
uniform mat4 inverseProjection;

uniform vec3 ambient;
uniform vec3 diffuse;
uniform vec3 lightDirection;

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
  float brightness = dot(normal, lightDirection);
  return ambient + diffuse * max(brightness, 0.0);
}

// given a test point p, the distance along the normal direction at a point on the surface
// is given by the following function:

float parallelDistance(
  vec3 surfacePoint,
  vec3 surfaceNormal,
  vec3 p
) {
  return dot(p - surfacePoint, surfaceNormal);
}

// if we transform the surface into world coordinates using a model transformation, model.
// Then this should be equivalent to moving the input test point by the inverse of model. 
// This means that in order for the above function to remain invariant, the surface normal 
// must transform by the inverse transpose of model.

void main() {
  gl_Position = vec4(position, 1);
}
