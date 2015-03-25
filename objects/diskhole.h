/**
 * @author Bruno Jobard
 * @date   Oct 2012
 *
 *  Defines a disk
 *
 */
#ifndef  _DISKHOLE_H_
#define  _DISKHOLE_H_

#include "triMesh.h"

/**
 * Diskhole Object
 *
 */
class Diskhole : public TriMesh {
public:
  Diskhole(int nbpoint, float rayon);
  virtual ~Diskhole(){};

};

#endif

