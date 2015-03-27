highp mat4 reflection(highp vec3 n) {

  // Proof: 
  // `.` p + p' = 2 * (p . n(k)) * n(k) where . is dot and n is normalize
  // so p' = 2 * (p . n(k)) * n(x) - p


  //TODO: Return a matrix that reflects all points about the plane passing through the origin with normal n

  return mat4(1, 0, 0, 0,
              0, 1, 0, 0, 
              0, 0, 1, 0,
              0, 0, 0, 1);
}

#pragma glslify: export(reflection)