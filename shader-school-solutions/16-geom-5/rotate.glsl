vec3 rotatePoint(vec3 p, vec3 n, float theta) {
  return (
    cos(theta) * p + sin(theta) * cross(n, p) + (1.0 - cos(theta)) * n * dot(n, p)
    // = c p.x +  s (n.z p.y z^y + n.y p.z y^z) + _c n.x (n.x p.x + n.y p.y + n.z p.z)
    // = (c + _c n.x n.x) p.x + (s n.z (-1) + _c n.x n.y) p.y + (s n.y 1 + _c n.x n.z) p.z
    // = (c + _c n[i] * n[i]) p[i] + s n[k] sgn(k, j) + _c n[i] * n[j]  + s n[j] sgn(j, k) + _c n[i] * n[k]
  );
}

highp mat4 rotation(highp vec3 n, highp float theta) {
  //Using Rodrigues' formula, find a matrix which performs a rotation about the axis n by theta radians

  highp float c = cos(theta);
  highp float _c = 1. - c;
  highp float s = sin(theta);

  return mat4(  c + _c * n.x * n.x,         s * n.z + _c * n.x * n.y,  - s * n.y + _c * n.x * n.z, 0,
              - s * n.z + _c * n.x * n.y,   c + _c * n.y * n.y,          s * n.x + _c * n.y * n.z, 0,
                s * n.y + _c * n.x * n.z, - s * n.x + _c * n.y * n.z,    c + _c * n.z * n.z,       0,
                                      0,                           0,                     0,       1);
}

#pragma glslify: export(rotation)