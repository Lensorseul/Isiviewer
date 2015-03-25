#include "cubecorner.h"

Cubecorner::Cubecorner()
  : TriMesh()
{
  _name = "Cubecorner";

  // vertex coordinate
  static const GLfloat v[10][3] = {
    {-1,-1,-1},{-1,1,-1},{1,1,-1},{1,-1,-1},
    {-1,-1, 1},{-1,1, 1},{0,1, 1},{1, 1, 0},{1, 0, 1},{1,-1, 1}
  };

  // triangles vertex indices
  static const GLint t[16][3] = {
    {1,2,0},{3,0,2},  // bottom triangles
      {3,9,0},{0,9,4},{0,4,1},{1,4,5},{1,5,6},{6,7,1},{7,2,1},{2,7,3},{7,8,3},{8,9,3},{4,6,5},{8,6,4},{9,8,4},{8,7,6}
  };
/*
  // triangle normals
  static const GLint nt[12][3] = {
    {0,0,-1},{0,0,-1}, // bottom triangle normals
    {0,1,0},{0,1,0},{1,0,0},{1,0,0},{0,-1,0},{0,-1,0},{-1,0,0},{-1,0,0}, // side triangle normals
    {0,0,1},{0,0,1}    // top triangle normals
  };

  // triangle vertex normals
  static const GLint nv[36][3] = {
    {0,0,-1},{0,0,-1},{0,0,-1},{0,0,-1},{0,0,-1},{0,0,-1}, // bottom triangle vertex normals

    {0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},{0,1,0},       // side triangle vertex normals
    {1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},{1,0,0},
    {0,-1,0},{0,-1,0},{0,-1,0},{0,-1,0},{0,-1,0},{0,-1,0},
    {-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},{-1,0,0},

    {0,0,1},{0,0,1},{0,0,1},{0,0,1},{0,0,1},{0,0,1}        // top triangle vertex normals
  };
*/

  //--- Fill vertices and triangles vectors

  // Fill vertices vector
  for (int i=0; i<10 ; ++i)
    this->addVertex(v[i][0], v[i][1], v[i][2]);

  // Fill triangles vector
  for (int i=0; i<16; ++i)
    this->addTriangle(t[i][0], t[i][1], t[i][2]);

  // Fill normals vectors
  bool use_computed_normals = true; /// a modifier ici

  if (use_computed_normals) {

      computeNormalsT();  // to be fixed
      computeNormalsV();  // to be fixed

    } else { // use manually defined normals
/*
      // set triangle normals
      for (int i=0; i<12; ++i) {
          Normal nT(nt[i][0], nt[i][1], nt[i][2]);
          this->addNormalT(nT);
        }
      // set triangle vertex normals
      for (int i=0; i<36; ++i) {
          Normal nV(nv[i][0], nv[i][1], nv[i][2]);
          this->addNormalV(nV);
        }*/
    }

}

