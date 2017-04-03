#include "wing.h"
#include "part.h"
#include "QVector2D"
#include "vector"

using namespace std;

Wing::Wing()
{
    bool reflect = false;

    PositionBuffer  m_VertexBuffer;
    IndexBuffer     m_IndexBuffer;

    vector<QVector2D> sketch;
    sketch.push_back(QVector2D(0,0));
    sketch.push_back(QVector2D(1,0));
    sketch.push_back(QVector2D(l,b/2));
    sketch.push_back(QVector2D(0,b/2));


    sketch.push_back(QVector2D(0,b/2-ao));
    sketch.push_back(QVector2D(aw,b/2-ao));
    sketch.push_back(QVector2D(aw,b/2-ao-al));
    sketch.push_back(QVector2D(0,b/2-ao-al));

    sketch.push_back(QVector2D(l,0));
    sketch.push_back(QVector2D(l,b/2-ao));
    sketch.push_back(QVector2D(l,b/2-ao-al));

    for (std::vector<QVector2D>::iterator it = sketch.begin(); it != sketch.end(); ++it)
    {
        if (reflect)
        {
            m_VertexBuffer.push_back ( Vertex(QVector3D(it->x(), -it->y(), 0), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(0, 0, 1), QVector2D(-1,1) ));
        }
        else
        {
            m_VertexBuffer.push_back ( Vertex(QVector3D(*it, 0), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(0, 0, 1), QVector2D(-1,1) ));
        }
    }
    m_IndexBuffer.push_back (1);
    m_IndexBuffer.push_back (2);
    m_IndexBuffer.push_back (8);

    m_IndexBuffer.push_back (9);
    m_IndexBuffer.push_back (2);
    m_IndexBuffer.push_back (3);

    m_IndexBuffer.push_back (9);
    m_IndexBuffer.push_back (3);
    m_IndexBuffer.push_back (4);

    m_IndexBuffer.push_back (10);
    m_IndexBuffer.push_back (9);
    m_IndexBuffer.push_back (5);

    m_IndexBuffer.push_back (10);
    m_IndexBuffer.push_back (5);
    m_IndexBuffer.push_back (6);

    m_IndexBuffer.push_back (8);
    m_IndexBuffer.push_back (10);
    m_IndexBuffer.push_back (7);

    m_IndexBuffer.push_back (8);
    m_IndexBuffer.push_back (7);
    m_IndexBuffer.push_back (0);


    for (std::vector<QVector2D>::iterator it = sketch.begin(); it != sketch.end(); ++it) {
        if (reflect)
        {
            m_VertexBuffer.push_back ( Vertex(QVector3D(it->x(), -it->y(), 0), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(0, 0, 1), QVector2D(-1,1) ));
        }
        else
        {
            m_VertexBuffer.push_back ( Vertex(QVector3D(*it, -0), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(0, 0, 1), QVector2D(-1,1) ));
        }
    }

    for (int i = m_IndexBuffer.size()-1; i >= 0; --i)
    {
        m_IndexBuffer.push_back (m_IndexBuffer[i]+11);
    }

    for (int i=0; i < 7; ++i)
    {
        m_IndexBuffer.push_back(i+11);
        m_IndexBuffer.push_back(i+1);
        m_IndexBuffer.push_back(i);

        m_IndexBuffer.push_back(i+11);
        m_IndexBuffer.push_back(i+12);
        m_IndexBuffer.push_back(i+1);
    }

    m_IndexBuffer.push_back(18);
    m_IndexBuffer.push_back(0);
    m_IndexBuffer.push_back(7);

    m_IndexBuffer.push_back(18);
    m_IndexBuffer.push_back(11);
    m_IndexBuffer.push_back(0);

    mainPart.setupMesh(m_VertexBuffer, m_IndexBuffer);

    PositionBuffer  m_VertexBuffer2;
    IndexBuffer     m_IndexBuffer2;

    sketch.clear();
    sketch.push_back(QVector2D(0,b/2-ao-al));
    sketch.push_back(QVector2D(aw,b/2-ao-al));
    sketch.push_back(QVector2D(aw,b/2-ao));
    sketch.push_back(QVector2D(0,b/2-ao));


    for (std::vector<QVector2D>::iterator it = sketch.begin(); it != sketch.end(); ++it) {
        if (reflect)
        {
            m_VertexBuffer2.push_back ( Vertex(QVector3D(it->x(), -it->y(), 0), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(0, 0, 1), QVector2D(-1,1) ));
        }
        else
        {
            m_VertexBuffer2.push_back ( Vertex(QVector3D(*it, 0), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(0, 0, 1), QVector2D(-1,1) ));
        }
    }
    m_IndexBuffer2.push_back (0);
    m_IndexBuffer2.push_back (3);
    m_IndexBuffer2.push_back (2);

    m_IndexBuffer2.push_back (2);
    m_IndexBuffer2.push_back (1);
    m_IndexBuffer2.push_back (0);


    for (std::vector<QVector2D>::iterator it = sketch.begin(); it != sketch.end(); ++it) {
        if (reflect)
        {
            m_VertexBuffer2.push_back ( Vertex(QVector3D(it->x(), -it->y(), 0), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(0, 0, 1), QVector2D(-1,1) ));
        }
        else
        {
            m_VertexBuffer2.push_back ( Vertex(QVector3D(*it, 0), QVector3D( 1.0f, 0.0f, 0.0f ), QVector3D(0, 0, 1), QVector2D(-1,1) ));
        }
    }

    for (int i = m_IndexBuffer2.size()-1; i >= 0; --i)
    {
        m_IndexBuffer2.push_back (m_IndexBuffer2[i]+4);
    }

    m_IndexBuffer2.push_back(4);
    m_IndexBuffer2.push_back(3);
    m_IndexBuffer2.push_back(0);

    m_IndexBuffer2.push_back(7);
    m_IndexBuffer2.push_back(3);
    m_IndexBuffer2.push_back(4);


    aileron.setupMesh(m_VertexBuffer2, m_IndexBuffer2);


}


void Wing::initializeControls()
{
    aileronAngleControl = new Control(controlLayout, drawingWidget);
    aileronAngleControl->setValue(20);
    SBody::initializeControls();
    sizeControl->setValue(4);
    aileron.sizeControl = sizeControl;
}

void Wing::updateControls()
{
    SBody::updateControls();
    aileron.setTranslation(translation());
    aileron.toPosRotMatrix = toPosRotMatrix;

    if (aileronAngleControl != nullptr) // && (aileronAngleControl->m_value != aileronAngleControl->old_value))
    {
        aileron.translate(0.1, 0, 0);
        aileron.rotate(aileronAngleControl->m_value, 0,1,0);
        aileron.translate(-0.1, 0, 0);
    }

}

void Wing::setDimensions(float l, float b, float ao, float aw, float al)
{
    this->l = l;
    this->b = b;
    this->ao = ao;
    this->aw = aw;
    this->al = al;
}
