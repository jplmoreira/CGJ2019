#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "../include.hpp"

namespace engine {
    namespace geometry {
        class mesh {
            bool elements;
            unsigned int num_indexes;
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
            GLuint vao_id = 0;
            std::vector<math::vec3> vertices;
            std::vector<math::vec3> normals;
            std::vector<math::vec2> texcoords;

            template<std::size_t SIZE_V, std::size_t SIZE_I>
            mesh(float(&vertices)[SIZE_V][3], GLushort(&indices)[SIZE_I]);
            mesh(std::string filename);
            ~mesh();

            void draw();
        };

        template<std::size_t SIZE_V, std::size_t SIZE_I>
        inline mesh::mesh(float(&vertices)[SIZE_V][3], GLushort(&indices)[SIZE_I]) :
            elements(true) {
            GLuint vbo[2];
            num_indexes = SIZE_I;
            glGenVertexArrays(1, &vao_id);
            glBindVertexArray(vao_id);
            {
                glGenBuffers(2, vbo);

                glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
                {
                    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
                    glEnableVertexAttribArray(ATTR::VERTICES);
                    glVertexAttribPointer(ATTR::VERTICES, 3, GL_FLOAT, GL_FALSE, 0, 0);
                }
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
                {
                    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
                }
            }
            glBindVertexArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    }
}