#include "disk.h"
#include <math.h>


#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

Disk::Disk(int nbpoint)
  : TriMesh()
{
      _name = "Disk";
      vector<vector<GLfloat> > points;
      vector<GLfloat> atp;

      vector<vector<GLint> > triangles;
      vector<GLint> att;

      atp.push_back(0);
      atp.push_back(1);
      atp.push_back(0);
      points.push_back(atp);
      atp.clear();

      for(int i=1; i<=nbpoint; i++)
      {
          atp.push_back(cos((i*2*M_PI)/nbpoint));
          atp.push_back(1);
          atp.push_back(sin((i*2*M_PI)/nbpoint));
          points.push_back(atp);
          atp.clear();
      }

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
