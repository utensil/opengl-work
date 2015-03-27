highp vec2 func(highp vec2 a, highp vec2 b) {

  return normalize(normalize(a) + normalize(b));
}

//Do not change this line
#pragma glslify: export(func)