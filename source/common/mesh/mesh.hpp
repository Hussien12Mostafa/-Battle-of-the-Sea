#pragma once

#include <glad/gl.h>
#include <iostream>
#include "vertex.hpp"

namespace our {

    #define ATTRIB_LOC_POSITION 0
    #define ATTRIB_LOC_COLOR    1
    #define ATTRIB_LOC_TEXCOORD 2
    #define ATTRIB_LOC_NORMAL   3

    class Mesh {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex array object, A vertex buffer and an element buffer
        unsigned int VBO, EBO;
        unsigned int VAO;
        // We need to remember the number of elements that will be draw by glDrawElements 
        GLsizei elementCount;
    public:

        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each rectangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering 
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& elements)
        {
            //TODO: (Req 1) Write this function
            // remember to store the number of elements in "elementCount" since you will need it for drawing
            // For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc
            
            //the number of elements present in the element array
            elementCount = elements.size();

            //generate the vertix array VAO and bind it to the program
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);

            //generate and bind the buffer VBO to the program           
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);

            //fill the buffer data with the verticies data
            //the function takes the whole size of the content of the buffer , the address of the first vertix
            glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Vertex),  &vertices[0] , GL_STATIC_DRAW);

            
            //how the gpu will read the content of the buffer

            //first the possition -> 3 positions x,y,z - floats - not normalized - jump the size of a vertex to get the next possition - starts at the begining 
            glEnableVertexAttribArray(ATTRIB_LOC_POSITION);
            glVertexAttribPointer(ATTRIB_LOC_POSITION, 3, GL_FLOAT, false, sizeof(Vertex), (void*)0);
            
            //second the color -> 4 channelss r,g,b,a - bytess - normalized - jump the size of a vertex to get the next possition - starts at the offset of color in the vertex
            glEnableVertexAttribArray(ATTRIB_LOC_COLOR);
            glVertexAttribPointer(ATTRIB_LOC_COLOR, 4, GL_UNSIGNED_BYTE, true, sizeof(Vertex), (void*) offsetof(Vertex, color));

            //third the teture coordinates -> 2 positions - floats - not normalized - jump the size of a vertex to get the next possition - starts at the offset of tex_coord in the vertex
            glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORD);
            glVertexAttribPointer(ATTRIB_LOC_TEXCOORD, 2, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));
        
            //fourth the normal -> 3 positions - floats - not normalized - jump the size of a vertex to get the next possition - starts at the offset of normal in the vertex
            glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);
            glVertexAttribPointer(ATTRIB_LOC_NORMAL, 3, GL_FLOAT, false, sizeof(Vertex), (void*)offsetof(Vertex, normal));

            //generate and bind element buffer EBO
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

            //fill the element buffer data
            //the function takes the whole size of the content of the buffer , the address of the first element
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementCount*sizeof(unsigned int), &elements[0], GL_STATIC_DRAW);




        }

        // this function should render the mesh
        void draw() 
        {
            //TODO: (Req 1) Write this function
            //bind the vertix array then draw the elements "triangles in our case"
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES,elementCount,GL_UNSIGNED_INT,(void*)0);
        }

        // this function should delete the vertex & element buffers and the vertex array object
        ~Mesh(){
            //TODO: (Req 1) Write this function
            glDeleteVertexArrays(1,&VAO);
            glDeleteBuffers(1,&VBO);
            glDeleteBuffers(1,&EBO);
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };

}