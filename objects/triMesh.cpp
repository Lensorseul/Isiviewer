#include "triMesh.h"
using namespace std;
#include <map>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/vector_angle.hpp>
TriMesh::TriMesh() 
  : Object3D()
{
  _name="TriMesh";
}

void TriMesh::addVertex(Vertex v){
  extendBoundingBox(v);
  _vertices.push_back(v);
}
void TriMesh::addVertex(double x, double y, double z){
  addVertex(Vertex(x,y,z));
}
void TriMesh::addTriangle(Triangle t){
  _triangles.push_back(t);
}
void TriMesh::addTriangle(int v1, int v2, int v3){
  Triangle t;
  t.push_back(v1);
  t.push_back(v2);
  t.push_back(v3);
  addTriangle(t);
}

void TriMesh::addNormalT(Normal n){
  _normalsT.push_back(n);
}
void TriMesh::addNormalV(Normal n){
  _normalsV.push_back(n);
}


Vertex TriMesh::getVertex(int i){
  return _vertices[i];
}


void TriMesh::computeBoundingBox(){
  if(_vertices.size()<1) return;

  _bBoxMax=_vertices[0];
  _bBoxMin=_vertices[0];
  for(unsigned int i=0; i<_vertices.size(); ++i)
    extendBoundingBox(_vertices[i]);
}

void TriMesh::computeNormalsT(){
  _normalsT.empty();

  // Compute a normal for each triangle
  // and put it in normalsT vector.

  // Replace code below

  for(unsigned int t=0; t<_triangles.size(); ++t) {
     glm::vec3 const & a = _vertices[_triangles[t][0]];
     glm::vec3 const & b = _vertices[_triangles[t][1]];
     glm::vec3 const & c = _vertices[_triangles[t][2]];
     Normal n = glm::normalize(glm::cross(b - a, c - a));
     addNormalT(n);
    }

}


void TriMesh::computeNormalsV(float angle_threshold){
    glm::vec3 n,m,sum;
    map <int, vector<int> > adjacenceList;
    map<int, vector<int> >::iterator pos;
    vector<int>::iterator it;
    int vertex;
    int i;
    int j;
    _normalsV.clear();

    for(i=0; i<_triangles.size(); ++i){
        for(j=0; j<_triangles[i].size(); ++j){
            vertex = _triangles[i][j];
            pos = adjacenceList.find(vertex);
            if( pos == adjacenceList.end() )
                pos = adjacenceList.insert( std::pair<int,std::vector<int> >(vertex, std::vector<int>()) ).first;
            pos->second.push_back(i);
            }
    }
    for(i=0; i<_triangles.size(); ++i){
        n = _normalsT[i];
        for(j=0; j<_triangles[i].size(); ++j){
            sum = n;
            vertex = _triangles[i][j];
            std::vector<int> & adjacentTriangles = adjacenceList[vertex];
            for(it=adjacentTriangles.begin(); it != adjacentTriangles.end(); ++it){
                    m = _normalsT[*it];
                    if( *it != i && glm::angle(n,m) < angle_threshold ){
                    sum += m;
                    }
            }
            addNormalV(glm::normalize(sum));
        }
    }
}


double TriMesh::normalize(){
  glm::vec3 size=_bBoxMax-_bBoxMin;
  glm::vec3 c=getBoundingBoxCenter();
  double scale=2/max(size.x, max(size.y,size.z));

  for(unsigned int i=0; i<_vertices.size(); ++i){
      _vertices[i]+=c;
      _vertices[i]*=scale;
    }

  _bBoxMin+=c;
  _bBoxMin*=scale;
  _bBoxMax+=c;
  _bBoxMax*=scale;

  return scale;
}


std::string TriMesh::toString(){
  ostringstream oss;
  oss<< "["<< _name <<" v:"<< _vertices.size() <<", t:"<< _triangles.size() <<"]";
  return oss.str();
}

void TriMesh::toOStream(std::ostream& out) const{
  Object3D::toOStream(out);
  out << "   v: " << _vertices.size()  << std::endl;
  out << "   t: " << _triangles.size() << std::endl;
}



void TriMesh::draw(bool flipnormals){
  unsigned int i,t;
  bool smooth;
  Normal n;

  GLint mode[1];
  glGetIntegerv(GL_SHADE_MODEL, mode);
  smooth= mode[0]==GL_SMOOTH && _normalsV.size()==_triangles.size()*3;

  if(smooth){
      glBegin(GL_TRIANGLES);
      for(t=0; t<_triangles.size(); ++t)
        for(i=0; i<3; i++){
            n=_normalsV[3*t+i];
            if(flipnormals) n*=-1;
            //        glNormal3fv(&n[0]);
            glNormal3fv(glm::value_ptr(n));
            glVertex3fv(glm::value_ptr(_vertices[_triangles[t][i]]));
          }
      glEnd();
    }else{
      glBegin(GL_TRIANGLES);
      for(t=0; t<_triangles.size(); ++t){
          n=_normalsT[t];
          if(flipnormals) n*=-1;
          glNormal3fv(glm::value_ptr(n));
          for(i=0; i<3; i++)
            glVertex3fv(glm::value_ptr(_vertices[_triangles[t][i]]));
        }
      glEnd();
    }

}


void TriMesh::drawNormals(bool flipnormals){
  unsigned int i,t;
  bool smooth;
  glm::vec3 p,n;

  GLint mode[1];
  glGetIntegerv(GL_SHADE_MODEL, mode);
  smooth= mode[0]==GL_SMOOTH && _normalsV.size()==_triangles.size()*3;

  glColor3f(1,1,1);
  if(smooth){
      for(i=0; i<_normalsV.size(); ++i){
          n=_normalsV[i];
          if(flipnormals) n*=-1;
          glNormal3fv(glm::value_ptr(n));
          n/=10;
          glBegin(GL_LINES);
          glVertex3fv(glm::value_ptr(_vertices[_triangles[i/3][i%3]]));
          glVertex3fv(glm::value_ptr(_vertices[_triangles[i/3][i%3]]+n));
          glEnd();
        }
    }else{
      for(t=0; t<_triangles.size(); ++t){
          p=  _vertices[_triangles[t][0]]
              +_vertices[_triangles[t][1]]
              +_vertices[_triangles[t][2]];
          p/=3;
          n=_normalsT[t];
          if(flipnormals) n*=-1;
          glNormal3fv(glm::value_ptr(n));
          n/=10;
          glBegin(GL_LINES);
          glVertex3fv(glm::value_ptr(p));
          glVertex3fv(glm::value_ptr(p+n));
          glEnd();
        }
    }
}

void TriMesh::drawVertices(){
  glPointSize(3.);
  glBegin(GL_POINTS);
  for(unsigned int i=0; i<_vertices.size(); ++i )
    glVertex3fv(glm::value_ptr(_vertices[i]));
  glEnd();
}
