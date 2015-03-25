#include "diskhole.h"
#include <math.h>


Diskhole::Diskhole(int nbpoint, float rayon)
  : TriMesh()
{
      _name = "Diskhole";

      vector<vector<GLfloat> > points;
      vector<GLfloat> atp;

      vector<vector<GLint> > triangles;
      vector<GLint> att;

      vector<vector<GLint> > cercle;
      vector<GLint> atc;



      /// Ring 2 rayon défini au dessus
      for(int i=1; i<=nbpoint; i++)
      {
          atp.push_back(cos((i*2*M_PI)/nbpoint)*rayon);
          atp.push_back(0);
          atp.push_back(sin((i*2*M_PI)/nbpoint)*rayon);
          points.push_back(atp);
          atp.clear();
          atc.push_back(points.size()-1);
      }
      cercle.push_back(atc);
      atc.clear();

      for(int i=1; i<=nbpoint; i++)
      {
          atp.push_back(cos((i*2*M_PI)/nbpoint));
          atp.push_back(0);
          atp.push_back(sin((i*2*M_PI)/nbpoint));
          points.push_back(atp);
          atp.clear();
          atc.push_back(points.size()-1);
      }
      cercle.push_back(atc);



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


      //--- Fill vertices and triangles vectors

      // Fill vertices vector
      for (int i=0; i<points.size(); ++i)
        this->addVertex(points[i][0], points[i][1], points[i][2]);


      // Fill triangles vector
      for (int i=0; i<triangles.size(); ++i)
        this->addTriangle(triangles[i][0], triangles[i][1], triangles[i][2]);

      computeNormalsT();
      computeNormalsV();

  }
