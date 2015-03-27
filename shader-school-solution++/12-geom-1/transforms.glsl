precision highp float;

attribute vec3 position;

uniform mat4 model, view, projection;

void main() {

  //Apply the model-view-projection matrix to `position`

  gl_Position = projection * view * model * vec4(position, 1);
}

/*
The model-view-projection factorization
Many 3D graphical applications make use of 4 different coordinate systems:

* Data coordinates: Which are the coordinates of the vertices in the model
* World coordinates: Which are the coordinates of objects in the scene
* View coordinates: Which are the unprojected coordinates of the camera
* Clip coordinates: Which are the coordinates used by the GPU to render all primitives

The relationship between these coordinate systems is usually specified using 3 different transformations:

* model: Which transforms the object from data coordinates to world coordinates. This controls the location of the object in the world.
* view: Which transforms world coordinate system to a viewing coordinate system. This controls the position and orientation of the camera.
* projection: Which transforms the view coordinate system into device clip coordinates. This controls whether the view is orthographic or perspective, and also controls the aspect ratio of the camera.

*/