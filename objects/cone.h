/**
 * @author Bruno Jobard
 * @date   Oct 2012
 *
 *  Defines a disk
 *
 */
#ifndef  _CONE_H_
#define  _CONE_H_

#include "triMesh.h"

/**
 * Cone Object
 *
 */
class Cone : public TriMesh {
    int nbcercle;
public:
  Cone(int nbpoint);
  virtual ~Cone(){};

};

#endif
