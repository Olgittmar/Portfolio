using System;
using System.Collections.Generic;

namespace Coordinates
{
    public readonly struct Point : IEquatable<Point>
    {
        public readonly int x;
        public readonly int y;
        public Point(int _x, int _y)
            { this.x = _x; this.y = _y; }

        public bool Equals( Point other )
            { return x == other.x && y == other.y; }
        public override bool Equals(object obj)
            { return obj is Point p && Equals(p); }
        public override int GetHashCode()
        {
            return HashCode.Combine(x.GetHashCode(), y.GetHashCode());
        }

        public static bool operator ==(Point a, Point b)
            { return a.Equals(b); }
        public static bool operator !=(Point a, Point b)
            { return !a.Equals(b); }
        public override string ToString()
        {
            return base.ToString() + ": (" + x.ToString() + ", " + y.ToString() + ")";
        }

    }

    public readonly struct Line
    {
        public readonly Point start;
        public readonly Point end;
        public Line(Point _start, Point _end )
            { this.start = _start; this.end = _end; }

        public override string ToString()
        {
            return base.ToString() + ": {\n\t\t" + start.ToString() + ",\n\t\t" + end.ToString() + "\n\t}";
        }

#pragma warning disable IDE1006 // Naming Styles
// to distinguish from mathematical notation for derivative operator by x, Dx
        private readonly int dx {
            get { return end.x - start.x; } }
        private readonly int dy {
            get { return end.y - start.y; } }
#pragma warning restore IDE1006 // Naming Styles
        public readonly float Slope
        {
            get
            {
                if (dx == 0)
                {
                    throw new DivideByZeroException();
                }
                return ((float)dy)/dx;
            }
        }
        public readonly float InvSlope
        {
            get
            {
                if(dy == 0) {
                    throw new DivideByZeroException();
                }
                return ((float)dx)/dy;
            }
        }
        private float YatXof(Point p)
        {
            return start.y + (p.x - start.x) * Slope;
        }
        private float XatYof(Point p)
        {
            return start.x + (p.y - start.y) * InvSlope;
        }
        // Returns true if p is equal to start or end, or if p lies on the line between them
        // otherwise false
        public bool Includes(Point p)
        {
            if( p == start || p == end ) {
                return true;
            }

            int minY = Math.Min(start.y, end.y);
            int maxY = Math.Max(start.y, end.y);
            int minX = Math.Min(start.x, end.x);
            int maxX = Math.Max(start.x, end.x);

            if ( p.y < minY || p.y > maxY
              || p.x < minX || p.x > maxX) {
                return false;
            }

            if ( dx == 0 ) {
                return p.x == start.x &&
                       p.y >= minY && p.y <= maxY;
            }

            if ( dy == 0 ) {
                return p.y == start.y &&
                       p.x >= minX && p.x <= maxX;
            }

            return (int)Math.Round(YatXof(p)) == p.y;
        }
        // Returns true if p lies strictly on the left side of the line,
        // and min(start.y, end.y) <= p.y <= max(start.y, end.y), otherwise false 
        public bool Intersects(Point p)
        {
            if ( p.y < Math.Min(start.y, end.y)
              && p.y > Math.Max(start.y, end.y) ) {
                return false;
            }
            return this.IsToRightOf(p);
        }
        // Returns true if this line is strictly to the right of p, otherwise false.
        private bool IsToRightOf(Point p)
        {
            if (p.x > Math.Max(start.x, end.x))
            {
                return false;
            }
            if (dx == 0) {
                return p.x < start.x;
            }
            if (dy == 0) {
                return p.x < Math.Min(start.x, end.x);
            }
            // If Slope > 0 then we are either in the 1st or 3rd quadrant, eg: /
            if ( Slope > 0 ) {
                // Check if p is above the line at p.x
                return YatXof(p) < (float)p.y;
            } else {
                // We are in the 2nd or 4th quadrant, eg: \
                return XatYof(p) > (float)p.y;
            }
        }
    }

    public class Polygon
    {
        public List<Point> vertices;
        private static readonly int formatPointsPerRow = 6;
        public enum Classification { In, On, Out }

        public Polygon(List<Point> _vertices)
            { this.vertices = _vertices; }

        public override string ToString()
        {
            if (vertices.Count == 0) {
                return base.ToString() + ": Empty";
            }
            string _ret = base.ToString() + ": {\n\t\t" + vertices[0];
            for(int i = 1; i < vertices.Count; ++i) {
                _ret += ",\n\t\t";
                for(int j = 0; j < formatPointsPerRow; ++j) {
                    _ret += ", " + vertices[i].ToString();
                }
            }
            return _ret + "\n\t}";
        }

        public void AddPoint(Point p)
            { vertices.Add(p); }
        public IEnumerable<Line> Lines
        {
            // Since Line is immutable, the elements of Lines is implicitly readonly
            // So I think the IDE should warn us if we try to modify the members?
            get
                {
                for (int index = 1; index < vertices.Count; ++index) {
                    yield return new Line(vertices[index - 1], vertices[index]);
                }
                if (vertices.Count > 0) {
                    yield return new Line(vertices[^1], vertices[0]);
                }
            }
        }
        // Implements OddEven algorithm to determine if p is inside this polygon.
        // Returns true if p is fully contained, otherwise false.
        public bool Contains(Point p)
        {
            int intersections = 0;
            foreach(Line line in Lines) {
                if( line.Intersects(p) ){
                    ++intersections;
                }
            }
            return ((intersections % 2) == 0);
        }
        // Returns true if p is on the perimiter, otherwise false.
        public bool PerimiterContains(Point p)
        {
            foreach(Line line in Lines) {
                if (line.Includes(p)) {
                    return true;
                }
            }
            return false;
        }
        // Consolidates Contains and PerimiterContains into a single loop through vertices.
        public Classification Classify(Point p)
        {
            int intersections = 0;
            foreach(Line line in Lines) {
                if( line.Includes(p) ) {
                    return Classification.On;
                }
                if( line.Intersects(p) ) {
                    ++intersections;
                }
            }
            return (intersections % 2 == 0) ? Classification.Out : Classification.In;
        }
        public string ClassifyPoint(Point p)
        {
            return Classify(p) switch
            {
                Classification.In => "in",
                Classification.On => "on",
                Classification.Out => "out",
                _ => throw new NotImplementedException("Invalid classification"),
            };
        }
    }
}
