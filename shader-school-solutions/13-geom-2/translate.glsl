highp mat4 translate(highp vec3 p) {

  //Construct a matrix, m, which translates all points so that p is at the origin.
  // Proof: result.x = p.x - p.x = p.x * 1 + p.y * 0 + p.z * 0 + p.w * (-p.x)

  return mat4(1, 0, 0, 0,
              0, 1, 0, 0, 
              0, 0, 1, 0,
              -p.x, -p.y, -p.z, 1);
}

//Do not remove this line
#pragma glslify: export(translate)