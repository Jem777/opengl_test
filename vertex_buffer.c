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

buffer_t create_vbo(unsigned short xrange, unsigned short yrange) {
    buffer_t buffer;
    unsigned short length = xrange * yrange;
    unsigned short index_length = xrange * (yrange - 1) * 2;
    buffer.length = length;
    buffer.xrange = xrange;
    buffer.yrange = yrange;

    vertex_t *vertices = malloc(sizeof(vertex_t) * length);
    unsigned short *indices = malloc(sizeof(unsigned short) * index_length);
    buffer.vertices = vertices;
    buffer.indices = indices;

    plot_function2d(buffer);

    glGenBuffers(1, &buffer.vertex_vboid);
    glBindBuffer(GL_ARRAY_BUFFER, buffer.vertex_vboid);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_t) * length, &vertices[0].x, GL_STATIC_DRAW);

    glGenBuffers(1, &buffer.index_vboid);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.index_vboid);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned short) * index_length, indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, buffer.vertex_vboid);
    glEnableVertexAttribArray(0); //We like submitting vertices on stream 0 for no special reason
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), BUFFER_OFFSET(0));   //The starting point of the VBO, for the vertices
    glEnableVertexAttribArray(1); //We like submitting normals on stream 1 for no special reason
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex_t), BUFFER_OFFSET(12));     //The starting point of normals, 12 bytes away
    glEnableVertexAttribArray(2); //We like submitting texcoords on stream 2 for no special reason
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex_t), BUFFER_OFFSET(24));   //The starting point of texcoords, 24 bytes away

    return buffer;
}

void destroy_vbo(buffer_t buffer) {
    glDeleteBuffers(1, &buffer.vertex_vboid);
    glDeleteBuffers(1, &buffer.index_vboid);
    free(buffer.vertices);
    free(buffer.indices);
}

void draw_vbo(buffer_t buffer) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer.index_vboid);
    for (int i = 0; i < buffer.yrange-1; i++) {
        glDrawElements(GL_TRIANGLE_STRIP, buffer.xrange * 2, GL_UNSIGNED_SHORT, BUFFER_OFFSET(buffer.xrange * 4 * i));
    }
}

void draw_vbo_raw(buffer_t buffer) {
    glBindBuffer(GL_ARRAY_BUFFER, buffer.vertex_vboid);
    glDrawArrays(GL_POINTS, 0, buffer.length);
}

void plot_function(vertex_t *vertices, unsigned short length, float start, float end) {
    float index = start;
    for (int i = 0; i < length; i++) {
        vertices[i].x = index;
        vertices[i].y = sin(index);
        vertices[i].z = 0;
        vertices[i].nx = 0.0;
        vertices[i].ny = 0.0;
        vertices[i].nz = 1.0;
        vertices[i].s0 = 1.0;
        vertices[i].t0 = 0.0;
        index += (end - start) / (float)length;
    }
}

void plot_function2d(buffer_t buffer) {
    float xstart = -1;
    float ystart = -1;
    float xstep = 0.2;
    float ystep = 0.2;

    float x = xstart;
    float y = ystart;
    for (int i = 0; i < buffer.length; i++) {
        setVertex(buffer.vertices, i, x, y, x*x - y*y);
        if ((i+1) % buffer.xrange == 0) {
            x = xstart;
            y += ystep;
        }
        else {
            x += xstep;
        }
        if (i < buffer.length - buffer.xrange) {
            // y coordinate is not equal to y-max
            buffer.indices[i * 2] = i;
            buffer.indices[i * 2 + 1] = i + buffer.xrange;
        }
    }
}

void setVertex(vertex_t *vertices, int i, float x, float y, float z) {
    vertices[i].x = x;
    vertices[i].y = y;
    vertices[i].z = z;
    vertices[i].nx = 0.0;
    vertices[i].ny = 0.0;
    vertices[i].nz = 1.0;
    vertices[i].s0 = 1.0;
    vertices[i].t0 = 0.0;
}
