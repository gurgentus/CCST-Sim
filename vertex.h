#ifndef VERTEX_H
#define VERTEX_H

#include <QVector2D>
#include <QVector3D>
#include <QVector4D>

class Vertex
{
public:
  // Constructors
  Q_DECL_CONSTEXPR Vertex();
  Q_DECL_CONSTEXPR explicit Vertex(const QVector3D &position);
  Q_DECL_CONSTEXPR Vertex(const QVector3D &position, const QVector4D &color);
  Q_DECL_CONSTEXPR Vertex(const QVector3D &position, const QVector4D &color, const QVector3D &normal, const QVector2D &texCoord);

  // Accessors / Mutators
  Q_DECL_CONSTEXPR const QVector3D& position() const;
  Q_DECL_CONSTEXPR const QVector4D& color() const;
  Q_DECL_CONSTEXPR const QVector3D& normal() const;
  Q_DECL_CONSTEXPR const QVector2D& texCoord() const;
  void setPosition(const QVector3D& position);
  void setColor(const QVector4D &color);
  void setNormal(const QVector3D& normal);
  void setTexCoord(const QVector2D& texCoord);

  // OpenGL Helpers
  static const int PositionTupleSize = 3;
  static const int ColorTupleSize = 4;
  static const int NormalTupleSize = 3;
  static const int TexCoordTupleSize = 2;

  static Q_DECL_CONSTEXPR int positionOffset();
  static Q_DECL_CONSTEXPR int colorOffset();
  static Q_DECL_CONSTEXPR int normalOffset();
  static Q_DECL_CONSTEXPR int texCoordOffset();
  static Q_DECL_CONSTEXPR int stride();

private:
  QVector3D m_position;
  QVector4D m_color;
  QVector3D m_normal;
  QVector2D m_texCoord;
};

/*******************************************************************************
 * Inline Implementation
 ******************************************************************************/

// Note: Q_MOVABLE_TYPE means it can be memcpy'd.
Q_DECLARE_TYPEINFO(Vertex, Q_MOVABLE_TYPE);

// Constructors
Q_DECL_CONSTEXPR inline Vertex::Vertex() {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position) : m_position(position) {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position, const QVector4D &color) : m_position(position), m_color(color) {}
Q_DECL_CONSTEXPR inline Vertex::Vertex(const QVector3D &position, const QVector4D &color, const QVector3D &normal, const QVector2D &texCoord) : m_position(position), m_color(color), m_normal(normal), m_texCoord(texCoord) {}

// Accessors / Mutators
Q_DECL_CONSTEXPR inline const QVector3D& Vertex::position() const { return m_position; }
Q_DECL_CONSTEXPR inline const QVector4D& Vertex::color() const { return m_color; }
Q_DECL_CONSTEXPR inline const QVector3D& Vertex::normal() const { return m_normal; }
Q_DECL_CONSTEXPR inline const QVector2D& Vertex::texCoord() const { return m_texCoord; }
void inline Vertex::setPosition(const QVector3D& position) { m_position = position; }
void inline Vertex::setColor(const QVector4D& color) { m_color = color; }
void inline Vertex::setNormal(const QVector3D& normal) { m_normal = normal; }
void inline Vertex::setTexCoord(const QVector2D& texCoord) { m_texCoord = texCoord; }

// OpenGL Helpers
Q_DECL_CONSTEXPR inline int Vertex::positionOffset() { return offsetof(Vertex, m_position); }
Q_DECL_CONSTEXPR inline int Vertex::colorOffset() { return offsetof(Vertex, m_color); }
Q_DECL_CONSTEXPR inline int Vertex::normalOffset() { return offsetof(Vertex, m_normal); }
Q_DECL_CONSTEXPR inline int Vertex::texCoordOffset() { return offsetof(Vertex, m_texCoord); }
Q_DECL_CONSTEXPR inline int Vertex::stride() { return sizeof(Vertex); }

#endif // VERTEX_H
