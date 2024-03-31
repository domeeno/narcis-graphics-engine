#ifndef SHADERS_H
#define SHADERS_H

unsigned int init_vertex_shader();
unsigned int init_fragment_shader();
unsigned int init_shader_program(unsigned int vertexShaderId,
                         unsigned int fragmentShaderId);

#endif // SHADERS_H
