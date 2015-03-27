precision mediump float;

bool inTile(vec2 p, float tileSize) {
  // 
  vec2 ptile = step(0.5, fract(p / (tileSize * 2.0)));
  return ptile.x == ptile.y;
}

void main() {

  //draws a checkerboard
  
  if(!inTile(gl_FragCoord.xy, 16.0)) {
    discard;
  } else {
    gl_FragColor = vec4(1.0, 1.0, 1.0, 1.0);
  }
}