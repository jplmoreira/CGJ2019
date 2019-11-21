#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "../include.hpp"

namespace engine {
    namespace geometry {
        class mesh {
            std::vector<math::vec3> vertices_data;
            std::vector<math::vec3> normals_data;
            std::vector<math::vec2> texcoord_data;
            std::vector<unsigned int> vert_ind, norm_ind, tex_ind;

            void parse_vertex(std::stringstream& in);
            void parse_normal(std::stringstream& in);
            void parse_texcoord(std::stringstream& in);
            void parse_face(std::stringstream& in);
            void parse_line(std::stringstream& in);

            void load_mesh_data(std::string filename);
            void process_mesh_data();
            void free_mesh_data();
            void create_buffer_objects();

        public:
            GLuint vao_id;
            std::vector<math::vec3> vertices;
            std::vector<math::vec3> normals;
            std::vector<math::vec2> texcoords;
            math::vec4 color;

            mesh();
            mesh(std::string filename);
            ~mesh();

            void draw();
        };
    }
}