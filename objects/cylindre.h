/**
 * @author Bruno Jobard
 * @date   Oct 2012
 *
 *  Defines a cylindre
 *
 */
#ifndef  _CYLINDRE_H_
#define  _CYLINDRE_H_

#include "triMesh.h"

/**
 * Cylindre Object
 *
 */
class Cylindre : public TriMesh {
public:
  Cylindre(int nbpoint, int nbcercle);
  virtual ~Cylindre(){};

};

#endif

