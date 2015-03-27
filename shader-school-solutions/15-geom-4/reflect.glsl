highp mat4 reflection(highp vec3 n) {

  // Proof: 
  // `.` p + p' = 2 * (p . n(k)) * n(k) where . is dot and n is normalize
  // so p' = 2 * (p . n(k)) * n(x) - p
  // so p'_x = 2 * (px * nx + ...) * n.x - px
  // i.e. p'x = [2nxnx -1 , 2nxny, 2nxnz, 0] * [px]


  //TODO: Return a matrix that reflects all points about the plane passing through the origin with normal n

  n = normalize(n);



  return mat4(2.0 * n.x * n.x - 1.0, 2.0 * n.y * n.x, 2.0 * n.z * n.x, 0.0,
              2.0 * n.x * n.y, 2.0 * n.y * n.y - 1.0, 2.0 * n.z * n.y, 0.0, 
              2.0 * n.x * n.z, 2.0 * n.y * n.z, 2.0 * n.z * n.z - 1.0, 0.0,
              0.0, 0.0, 0.0, 1.0);
}

#pragma glslify: export(reflection)