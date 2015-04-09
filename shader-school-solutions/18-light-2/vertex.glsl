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

varying vec3 fragNormal;

/**
Normals vectors are transformed in different way as vertices do.

Let's say vertices are transformed by matrix M. We cannot simply multiply M and normal.

A normal to the surface at a point P is a vector that is perpendicular to the tangent plane to that surface at P.
So normal is just a way to represent the plane, we just need to transform the normal in a way that the surface 
will be properly transformed.

Any point Q on that plane satisfies the following equation:

dot(n, P - Q) = 0

that's simply the same as saying the tangent plane is perpendicular to normal.

dot(n, P - Q) can be written as dot(n, P) - dot(n, Q) = 0

It would be convinient to choose a Q that satisfies dot(n, Q), then the equation
above would be simplified to:

dot(n, P) = 0 

Rewrite the above to matrix multiplication:

n^T P = 0 i.e. n^T M^-1 M P = 0             1)

The transformed P (mark it as P') and tranformed n (mark it as n') should satisfy:

n'^T P' = 0                                 2)

P'= MP                                      3)

Incorporat 1, 2 and 3, we have:

n'^T = n^T M^-1
   
See also 

  * http://www.songho.ca/opengl/gl_normaltransform.html
  * http://en.wikipedia.org/wiki/Normal_(geometry)

*/
void main() {
  gl_Position = projection * view * model * vec4(position, 1.0);
   // Note: don't multiply inverseProjection
  fragNormal = (vec4(normal, 0.0) * inverseModel * inverseView).xyz;
}
