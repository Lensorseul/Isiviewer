/**
 * @author Bruno Jobard
 * @date   Oct 2012
 *
 *  Defines a 3D sphere
 *
 */
#ifndef  _SPHERE_H_
#define  _SPHERE_H_

#include "triMesh.h"

/**
 * Sphere Object
 *
 */
class Sphere : public TriMesh {
    int nbcercle;
public:
  Sphere(int nbpoint);
  virtual ~Sphere(){};

};

#endif
