#include "mesh.hpp"

void engine::geometry::mesh::parse_vertex(std::stringstream& in) {
    math::vec3 v;
    in >> v.x >> v.y >> v.z;
    vertices_data.push_back(v);
}

void engine::geometry::mesh::parse_normal(std::stringstream& in) {
    math::vec3 n;
    in >> n.x >> n.y >> n.z;
    normals_data.push_back(n);
}

void engine::geometry::mesh::parse_texcoord(std::stringstream& in) {
    math::vec2 t;
    in >> t.x >> t.y;
    texcoord_data.push_back(t);
}

void engine::geometry::mesh::parse_face(std::stringstream& in) {
    std::string token;
    if(normals_data.empty() && texcoord_data.empty()) {
        for(int i = 0; i < 3; i++) {
            in >> token;
            vert_ind.push_back(std::stoi(token));
        }
    } else {
        for(int i = 0; i < 3; i++) {
            std::getline(in, token, '/');
            if(token.size() > 0) vert_ind.push_back(std::stoi(token));
            std::getline(in, token, '/');
            if(token.size() > 0) tex_ind.push_back(std::stoi(token));
            std::getline(in, token, ' ');
            if(token.size() > 0) norm_ind.push_back(std::stoi(token));
        }
    }
}

void engine::geometry::mesh::parse_line(std::stringstream& in) {
    std::string s;
    in >> s;
    if(s.compare("v") == 0) parse_vertex(in);
    else if(s.compare("vt") == 0) parse_texcoord(in);
    else if(s.compare("vn") == 0) parse_normal(in);
    else if(s.compare("f") == 0) parse_face(in);
}

void engine::geometry::mesh::load_mesh_data(std::string filename) {
    std::ifstream ifile(filename);
    std::string line;
    while(std::getline(ifile, line)) {
        std::stringstream sline(line);
        parse_line(sline);
    }
}

void engine::geometry::mesh::process_mesh_data() {
    for(unsigned int i = 0; i < vert_ind.size(); i++) {
        unsigned int vi = vert_ind[i];
        math::vec3 v = vertices_data[vi - 1];
        vertices.push_back(v);
        if(norm_ind.size() > 0) {
            unsigned int ni = norm_ind[i];
            math::vec3 n = normals_data[ni - 1];
            normals.push_back(n);
        }
        if(tex_ind.size() > 0) {
            unsigned int ti = tex_ind[i];
            math::vec2 t = texcoord_data[ti - 1];
            texcoords.push_back(t);
        }
    }

}

void engine::geometry::mesh::free_mesh_data() {
    vertices_data.clear();
    normals_data.clear();
    texcoord_data.clear();
    vert_ind.clear();
    norm_ind.clear();
    tex_ind.clear();
}

void engine::geometry::mesh::create_buffer_objects() {
    std::vector<math::vec4> colors(vertices.size());
    for(int i = 0; i < colors.size(); i++)
        colors[i] = color;
    GLuint v_vbo, c_vbo, n_vbo, t_vbo;
    glGenVertexArrays(1, &vao_id);
    glBindVertexArray(vao_id);
    {
        glGenBuffers(1, &v_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, v_vbo);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(math::vec3), &vertices[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(ATTR::VERTICES);
        glVertexAttribPointer(ATTR::VERTICES, 3, GL_FLOAT, GL_FALSE, sizeof(math::vec3), 0);
        glGenBuffers(1, &c_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, c_vbo);
        glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(math::vec4), &colors[0], GL_STATIC_DRAW);
        glEnableVertexAttribArray(ATTR::COLORS);
        glVertexAttribPointer(ATTR::COLORS, 4, GL_FLOAT, GL_FALSE, sizeof(math::vec4), 0);
        if(normals.size() > 0) {
            glGenBuffers(1, &n_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, n_vbo);
            glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(math::vec3), &normals[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(ATTR::NORMALS);
            glVertexAttribPointer(ATTR::NORMALS, 3, GL_FLOAT, GL_FALSE, sizeof(math::vec3), 0);
        }
        if(texcoords.size() > 0) {
            glGenBuffers(1, &t_vbo);
            glBindBuffer(GL_ARRAY_BUFFER, t_vbo);
            glBufferData(GL_ARRAY_BUFFER, texcoords.size() * sizeof(math::vec2), &texcoords[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(ATTR::TEXCOORDS);
            glVertexAttribPointer(ATTR::TEXCOORDS, 2, GL_FLOAT, GL_FALSE, sizeof(math::vec2), 0);
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}

engine::geometry::mesh::mesh() : vao_id(0) {}

engine::geometry::mesh::mesh(std::string filename) {
    load_mesh_data(filename);
    process_mesh_data();
    free_mesh_data();
}

engine::geometry::mesh::~mesh() {
    if(vao_id > 0) {
        GLuint vbo;
        glBindVertexArray(vao_id);
        glDisableVertexAttribArray(ATTR::VERTICES);
        glDeleteBuffers(1, &vbo);
        glDisableVertexAttribArray(ATTR::COLORS);
        glDeleteBuffers(1, &vbo);
        if(normals.size() > 0) {
            glDisableVertexAttribArray(ATTR::NORMALS);
            glDeleteBuffers(1, &vbo);
        }
        if(texcoords.size() > 0) {
            glDisableVertexAttribArray(ATTR::TEXCOORDS);
            glDeleteBuffers(1, &vbo);
        }
        glDeleteVertexArrays(1, &vao_id);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }
}

void engine::geometry::mesh::draw() {
    glBindVertexArray(vao_id);
    glDrawArrays(GL_TRIANGLES, 0, (GLsizei)vertices.size());
    glBindVertexArray(0);
}
