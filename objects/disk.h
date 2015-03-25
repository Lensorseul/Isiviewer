/**
 * @author Bruno Jobard
 * @date   Oct 2012
 *
 *  Defines a disk
 *
 */
#ifndef  _DISK_H_
#define  _DISK_H_

#include "triMesh.h"

/**
 * Disk Object
 *
 */
class Disk : public TriMesh {
public:
  Disk(int nbpoint);
  virtual ~Disk(){};

};

#endif

