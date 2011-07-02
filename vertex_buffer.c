/*
 * =====================================================================================
 *
 *       Filename:  vertex_buffer.c
 *
 *    Description:  Vertex Buffer Object Module
 *
 *        Version:  1.0
 *        Created:  02.07.2011 16:10:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem 
 *        Company:  
 *
 * =====================================================================================
 */

#include "vertex_buffer.h"

void setup_vbo() {
    GLuint vertex_vboid;
    GLuint index_vboid;

    vertex_t vertices[3];
    test_fill_vertices(vertices, 3);
    unsigned short indices[3];
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 2;

    glGenBuffers(1, &vertex_vboid);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_vboid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * 3, &vertices[0].x, GL_STATIC_DRAW);

    glGenBuffers(1, &index_vboid);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vboid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * 3, indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_vboid);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, sizeof(vertex_t), BUFFER_OFFSET(0));
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, sizeof(vertex_t), BUFFER_OFFSET(12));
    glClientActiveTexture(GL_TEXTURE0);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, sizeof(vertex_t), BUFFER_OFFSET(24));

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_vboid);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, BUFFER_OFFSET(0));
}

void test_fill_vertices(vertex_t *vertices, unsigned short length) {
     vertices[0].x = 0.0;
     vertices[0].y = 0.0;
     vertices[0].z = 0.0;
     vertices[0].nx = 0.0;
     vertices[0].ny = 0.0;
     vertices[0].nz = 1.0;
     vertices[0].s0 = 0.0;
     vertices[0].t0 = 0.0;
     //VERTEX 1
     vertices[1].x = 1.0;
     vertices[1].y = 0.0;
     vertices[1].z = 0.0;
     vertices[1].nx = 0.0;
     vertices[1].ny = 0.0;
     vertices[1].nz = 1.0;
     vertices[1].s0 = 1.0;
     vertices[1].t0 = 0.0;
     //VERTEX 2
     vertices[2].x = 0.0;
     vertices[2].y = 0.5;
     vertices[2].z = 0.0;
     vertices[2].nx = 0.0;
     vertices[2].ny = 0.0;
     vertices[2].nz = 1.0;
     vertices[2].s0 = 0.0;
     vertices[2].t0 = 1.0;
}
