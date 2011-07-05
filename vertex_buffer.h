/*
 * =====================================================================================
 *
 *       Filename:  vertex_buffer.h
 *
 *    Description:  header file for the vertex buffer
 *
 *        Version:  1.0
 *        Created:  02.07.2011 16:12:22
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jem
 *        Company:  
 *
 * =====================================================================================
 */

#ifndef VERTEX_BUFFER_H_
#define VERTEX_BUFFER_H_

#include <GL/glew.h>
#include <GL/gl.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

typedef struct {
    float x,y,z;
    float nx, ny, nz;
    float s0, t0;
    float s1, t1;
    float s2, t2;
} vertex_t;

typedef struct {
    vertex_t *vertices;
    unsigned short *indices;
    unsigned short length;
    GLuint vertex_vboid;
    GLuint index_vboid;
    unsigned short xrange;
    unsigned short yrange;
} buffer_t;

buffer_t create_vbo(unsigned short, unsigned short);
void destroy_vbo(buffer_t);
void draw_vbo(buffer_t);
void draw_vbo_raw(buffer_t buffer);
void plot_function(vertex_t *vertices, unsigned short length, float start, float end);
void plot_function2d(buffer_t buffer);
void setVertex(vertex_t *vertices, int i, float x, float y, float z);
#endif
