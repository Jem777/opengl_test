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

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

typedef struct {
    float x,y,z;
    float nx, ny, nz;
    float s0, t0;
    float s1, t1;
    float s2, t2;
} vertex_t;

void setup_vbo();
void test_fill_vertices(vertex_t *vertices, unsigned short length);
#endif
