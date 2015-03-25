/**
 * @author Bruno Jobard
 * @date   Oct 2012
 *
 *  Defines a disk
 *
 */
#ifndef  _FUNCSURFACE_H_
#define  _FUNCSURFACE_H_

#include "triMesh.h"

/**
 * Funcsurface Object
 *
 */
class FuncSurface : public TriMesh {
public:
  virtual ~FuncSurface(){};
  FuncSurface(int nbx, int nby, float minx, float maxx, float miny, float maxy, float (*pointer1)(float,float)=NULL);
  static float func_expcos(float x, float y);
  static float func_expsin(float x, float y);
};

#endif

