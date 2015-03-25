/**
 * @author Bruno Jobard
 * @date   Oct 2012
 *
 *  Defines a 3D cube
 *
 */
#ifndef  _OFFLOADER_H_
#define  _OFFLOADER_H_

#include "objects/triMesh.h"
#include "fstream"
#include "../my_object3d.h"
#include <glm/gtc/type_ptr.hpp>


/**
 * Lecture fichier
 *
 */
class Offloader : public TriMesh {
    string nomfichier;
    fstream fichier;

    string name;
    int nbpoint;
    int nbtriangle;
    int nbarrete;

    vector<vector<GLfloat> > points;
    vector<GLfloat> atp;

    vector<vector<GLint> > triangles;
    vector<GLint> att;

    vector<vector<float> > tcouleur;
    vector<float> couleur;

    void recupPoint();
    void recupEntete();
    void recupPoly();
    void recupCouleur();

    void affichEntete();
    void affichPoints();
    void affichTriangles();
    void affichCol();
public:
  Offloader(string nomfic);
  virtual ~Offloader(){};
  void charger();
  void draw(bool flipnormals=false);
};

#endif
