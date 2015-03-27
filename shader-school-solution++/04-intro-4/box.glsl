bool inBox(highp vec2 lo, highp vec2 hi, highp vec2 p) {

  //Test if the point p is inside the box bounded by [lo, hi]

  return all(lessThanEqual(lo, p)) && all(lessThanEqual(p, hi));
}


//Do not change this line or the name of the above function
#pragma glslify: export(inBox)
