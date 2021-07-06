#pragma once

// std
#include <string>
#include <vector>
#include <ranges>

// Own
#include "Point.h"
#include "Line.h"

namespace utils {
using namespace std;

class Polygon {
  public:
    Polygon() = default;
    ~Polygon() = default;
    explicit Polygon(const string& str);
    explicit Polygon(const vector<Point>& points);

    bool operator==( const Polygon& other ) const;

    vector<Point> getVertices() const { return _vertices; }
    inline void addPoint(const Point& p) { _vertices.push_back( p ); }
    inline void clear() { _vertices.clear(); }
    inline size_t numVertices() const { return _vertices.size(); }
    inline bool empty() const { return _vertices.empty(); }

    // Classifies the point p and returns a string with the corresponding classification,
    // "out" if p is outside the polygon
    // "in" if p is inside the polygon
    // "on" if p is on one or more of the lines between _vertices
    string classify( const Point p ) const;

    static void readPolygon( istream& in, const int numLines, Polygon& out );

    struct ProxyLine {
        using pointer = Line*;

        explicit ProxyLine( Point start, Point end ) : m_line(start, end) {}
        Line* operator->() { return &m_line; }
      private:
        Line m_line;
    };
    // Struct for iterating over the lines defined by _vertices in order of appearance.
    // Note that if _vertices.size() < 2 the polygon is not well defined.
    struct _Iterator {
#ifdef __cpp_lib_concepts
        using iterator_concept = input_iterator_tag;
#endif // __cpp_lib_concepts
        using iterator_category = input_iterator_tag;
        using difference_type = ptrdiff_t;
        using value_type = Line;
        using pointer = ProxyLine;
        using reference = Line;
        
        explicit _Iterator( const vector<Point>& vertices, const vector<Point>::const_iterator& it )
            : _container( vertices ), m_it( it ) {}
        reference operator*() const;
        _Iterator& operator++() { ++m_it; return *this; }
        pointer operator->() const { return ProxyLine( *m_it, *(m_it + 1) ); }
        bool operator==(const _Iterator& other) const { return m_it == other.m_it; }
      protected:
        vector<Point>::const_iterator m_it;
        const vector<Point>& _container;
    };
    // Iterator does not allow modification of the underlying container,
    // but elements returned by value may be modified.
    // TODO: Implement an actual differentiation between 'const_iterator' and 'iterator', so we can use stuff like cbegin() intuitively
    using const_iterator = _Iterator;
    using iterator = _Iterator;

    iterator begin() { return iterator( _vertices, _vertices.cbegin() ); }
    iterator end() { return iterator( _vertices, _vertices.cend() ); }
    const_iterator begin() const { return const_iterator( _vertices, _vertices.cbegin() ); }
    const_iterator end() const { return const_iterator( _vertices, _vertices.cend() ); }
    const_iterator cbegin() const { return begin(); }
    const_iterator cend() const { return end(); }

  protected:
  private:
    // The vertices that make up this polygon, in clockwise or counter-clockwise order
    vector<Point> _vertices;
};

} // namespace utils