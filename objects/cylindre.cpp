#include "cylindre.h"
#include <math.h>

Cylindre::Cylindre(int nbpoint, int nbcercle)
  : TriMesh()
{
      _name = "Cylindre";
      vector<vector<GLfloat> > points;
      vector<vector<GLint> > cercle;
      vector<GLfloat> atp;
      vector<GLint> atc;

      float y=-1;
      for(int j=0; j<nbcercle; j++)
      {
          for(int i=1; i<=nbpoint; i++)
          {
              if((y==-1 && i==1)){
                  atp.push_back(0);
                  atp.push_back(y);
                  atp.push_back(0);
                  points.push_back(atp);
                  atp.clear();
              }
              atp.push_back((cos((i*2*M_PI)/nbpoint)));
              atp.push_back(y);
              atp.push_back((sin((i*2*M_PI)/nbpoint)));
              points.push_back(atp);
              atp.clear();
              atc.push_back(points.size()-1);
          }
          cercle.push_back(atc);
          atc.clear();
          y=y+((float)2/(nbcercle-1));
      }
      atp.push_back(0);
      atp.push_back(1);
      atp.push_back(0);
      points.push_back(atp);
      atp.clear();



      vector<vector<GLint> > triangles;
      vector<GLint> att;

      for(int i=0; i<nbpoint; i++)
      {
          att.push_back(0);
          att.push_back(i+1);
          if((i+1)%nbpoint==0)
          {
            att.push_back(1);
          }else{
            att.push_back(i+2);
          }
          triangles.push_back(att);
          att.clear();
      }

      for(int i=0; i<cercle.size()-1; i++)
      {
          for(int j=0; j<nbpoint; j++)
          {
              att.push_back(cercle[i+1][j]);
              if((j+1)%nbpoint==0){
                    att.push_back(cercle[i][0]);
                }else{
                    att.push_back(cercle[i][j+1]);
                }
              att.push_back(cercle[i][j]);
              triangles.push_back(att);
              att.clear();

              att.push_back(cercle[i+1][j]);
              if((j+1)%nbpoint==0){
                    att.push_back(cercle[i+1][0]);
                }else{
                    att.push_back(cercle[i+1][j+1]);
                }
              if((j+1)%nbpoint==0){
                 att.push_back(cercle[i][0]);
              }else{
                att.push_back(cercle[i][j+1]);
              }
              triangles.push_back(att);
              att.clear();

        }
      }


      for(int j=cercle.size(); j<=cercle.size(); j++)
      {
          for(int i=0; i<nbpoint; i++)
          {

              att.push_back(cercle[j-1][i]);
              att.push_back(points.size()-1);
              if((i+1)%nbpoint==0)
              {
                att.push_back(cercle[j-1][0]);
              }else{
                att.push_back(cercle[j-1][i+1]);
              }
              triangles.push_back(att);
              att.clear();
          }

      }


      //--- Fill vertices and triangles vectors

      // Fill vertices vector
      for (int i=0; i<points.size(); ++i)
        this->addVertex(points[i][0], points[i][1], points[i][2]);


      // Fill triangles vector
      for (int i=0; i<triangles.size(); ++i)
        this->addTriangle(triangles[i][0], triangles[i][1], triangles[i][2]);

      // Fill normals vectors
          computeNormalsT();  // to be fixed
          computeNormalsV();  // to be fixed

  }
