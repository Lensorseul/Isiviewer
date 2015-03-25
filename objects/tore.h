/**
 * @author Bruno Jobard
 * @date   Oct 2012
 *
 *  Defines a disk
 *
 */
#ifndef  _TORE_H_
#define  _TORE_H_

#include "triMesh.h"

/**
 * Tore Object
 *
 */
class Tore : public TriMesh {
    int nbcercle;
public:
  Tore(int nbpoint);
  virtual ~Tore(){};

};

#endif

