void sideLengths(
  highp float hypotenuse, 
  highp float angleInDegrees, 
  out highp float opposite, 
  out highp float adjacent) {

  //Calculate side lengths here

  highp float angle = radians(angleInDegrees);

  opposite = hypotenuse * sin(angle);
  adjacent = hypotenuse * cos(angle);
}

//Do not change this line
#pragma glslify: export(sideLengths)