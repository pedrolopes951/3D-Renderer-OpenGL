#pragma once
#include <vector>


//  EBOs are used to optimize rendering by reusing vertex data in VBOs. Instead of specifying each vertex's attributes multiple times for shared vertices in complex models,
// EBOs allow you to define a list of indices that refer to the vertices in the VBO.
class ElementBuffer
{
private:
    unsigned int m_RendererID;
    unsigned int m_Count;
    const std::vector<unsigned int>& m_indices;

public:
    ElementBuffer(const std::vector<unsigned int>& indices);
    ~ElementBuffer();

    void Bind() const;
    void Unbind() const;

    inline unsigned int GetCount() const { return m_Count; }
};
