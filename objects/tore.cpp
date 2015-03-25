#include "tore.h"

using namespace glm;
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtx/transform.hpp>

Tore::Tore(int nbpoint)
  : TriMesh()
{
      _name = "Tore";
      nbcercle=nbpoint;
      vector<vector<GLfloat> > points;
      vector<vector<GLint> > cercle;
      vector<GLint> atc;
      vector<GLfloat> atp;

    for(int i=0; i<nbpoint; i++)
      {
              atp.push_back(0.6+(cos((i*2*M_PI)/nbpoint))*0.4);
              atp.push_back((sin((i*2*M_PI)/nbpoint))*0.4);
              atp.push_back(0);
              points.push_back(atp);
              atp.clear();
              atc.push_back(points.size()-1);
      }
      cercle.push_back(atc);
      atc.clear();





      float angle;
      angle=(float)360.0/nbcercle;
      for(int i=0; i<nbcercle-1; i++)
      {
          for(int j=0; j<nbpoint; j++)
          {
              vec3 vertex(points[j][0],points[j][1],points[j][2]);
              vec3 test=rotateY(vertex,angle);
              atp.push_back(test[0]);
              atp.push_back(test[1]);
              atp.push_back(test[2]);
              points.push_back(atp);
              atp.clear();
              atc.push_back(points.size()-1);
          }
          angle+=(float)360/nbcercle;
          cercle.push_back(atc);
          atc.clear();
      }
      for(int i=0; i<nbpoint; i++)
      {
          atc.push_back(i);
      }
      cercle.push_back(atc);

      vector<vector<GLint> > triangles;
      vector<GLint> att;

      //lier cercle entre eux
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



      // for (int i=0; i<triangles.size(); ++i)
      //   cout<< " triangle " << triangles[i][0]<<" "<< triangles[i][1]<<" "<<triangles[i][2]<<endl;


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
