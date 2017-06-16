#include "harmonic.hpp"

void ReadObj (const string filename, vector<int> &face,  vector<double> &vertex, vector<double> &color) {

  ifstream objfile(filename);
  assert(objfile.is_open() == true);

  string line;
  type_size vertex_size, face_size;
  type_size idx_face = 0, idx_vertex = 0;
  while( getline(objfile, line) ) {
    if( line[0] == '#' ) {  
      type_size space1, space2;
      space1 = line.find_first_of(" ");
      space2 = line.find_last_of(" ");

      if( line.substr(space2 + 1, 6) == "vertex" ) {
        vertex_size = stoi(line.substr(space1+1, space2 - space1 - 1));
        vertex.resize(3 * vertex_size);
        color.resize(3 * vertex_size);
      } else if( line.substr(space2 + 1, 5) == "faces" ) {
        face_size = stoi(line.substr(space1+1, space2));
        face.resize(3 * vertex_size);
      }

    } else if( line[0] == 'v' ) {
      type_size space1, space2, space3, space4;
      space1 = line.find_first_of(" ");
      space2 = line.find_first_of(" ", space1 + 1);
      space3 = line.find_first_of(" ", space2 + 1);
      space4 = line.find_first_of(" \n", space3 + 1);

      vertex[idx_vertex]                 = stod(line.substr(space1+1, space2 - space1 - 1));
      vertex[idx_vertex + vertex_size]   = stod(line.substr(space2+1, space3 - space2 - 1));
      vertex[idx_vertex + 2*vertex_size] = stod(line.substr(space3+1, space4 - space3 - 1));

      if( line.find_first_of(" ", space4 + 1) != string::npos ) {
        type_size space5, space6, space7;
        space5 = line.find_first_of(" ", space4 + 1);
        space6 = line.find_first_of(" ", space5 + 1);
        space7 = line.find_first_of(" \n", space6 + 1);

        color[idx_vertex]                 = stod(line.substr(space4+1, space5 - space4 - 1));
        color[idx_vertex + vertex_size]   = stod(line.substr(space5+1, space6 - space5 - 1));
        color[idx_vertex + 2*vertex_size] = stod(line.substr(space6+1, space7 - space6 - 1));
      }

    } else if( line[0] == 'f' ) {
      type_size space1, space2, space3, space4;
      space1 = line.find_first_of(" ");
      space2 = line.find_first_of(" ", space1 + 1);
      space3 = line.find_first_of(" ", space2 + 1);
      space4 = line.find_first_of(" \n", space3 + 1);

      face[idx_face]               = stod(line.substr(space1+1, space2 - space1 - 1));
      face[idx_face + face_size]   = stod(line.substr(space2+1, space3 - space2 - 1));
      face[idx_face + 2*face_size] = stod(line.substr(space3+1, space4 - space3 - 1));

    }
  }

}