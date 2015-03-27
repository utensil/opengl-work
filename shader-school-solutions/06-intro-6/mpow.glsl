mat2 matrixPower(highp mat2 m, int n) {
  
  //Raise the matrix m to nth power

  // For example:
  //
  //  matrixPower(m, 2) = m * m
  //

  highp mat2 r = mat2(m);

  for(int i = 0; i < 16 - 1 ; ++i) {
    if(i < n - 1) {
      r = r * m;
    } else {
      break;
    }
  }

  return r;  
}

//Do not change this line or the name of the above function
#pragma glslify: export(matrixPower)