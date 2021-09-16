using NUnit.Framework;
using Coordinates;
using System;
using System.Collections;

namespace TestCoordinates
{
	[TestFixture]
	public class Tests
	{
		[SetUp]
		public void Setup()
		{
		}

		[Test]
		public void TestPoint()
		{
			Random rng = new();
			Point p1 = new(rng.Next(), rng.Next());
			Point p2 = new(p1.x, p1.y);
			Point p3 = new(p1.x - 1, p1.y + 1);
			Assert.That(p1, Is.EqualTo(p2));
			Assert.That(p1, Is.Not.EqualTo(p3));
		}

		// Also tests InvSlope
		[TestCaseSource(typeof(TestData), nameof(TestData.GenericLineTestCases))]
		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineSlope(Line line)
		{
			double dx = line.end.x - line.start.x;
			double dy = line.end.y - line.start.y;
			if (dx == 0.0d || dy == 0.0d) {
				if (dx == 0.0d) {
					Assert.That(
						delegate { _ = line.Slope; },
						Throws.Exception);
				}
				if (dy == 0.0d) {
					Assert.That(
						delegate { _ = line.InvSlope; },
						Throws.Exception);
				}
				if (dx == 0.0d && dy != 0.0d) {
					Assert.That(line.InvSlope, Is.EqualTo(0.0d));
				}
				if (dx != 0.0d && dy == 0.0d)
				{
					Assert.That(line.Slope, Is.EqualTo(0.0d));
				}
				return;
			}
			Assert.That(line.Slope, Is.EqualTo(dy / dx));
			Assert.That(line.InvSlope, Is.EqualTo(dx / dy));
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.GenericLineTestCases))]
		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIncludes(Line line)
		{
			double dx = line.end.x - line.start.x;
			double dy = line.end.y - line.start.y;
			
			// When dx is odd, we can get wierd rounding errors if slope of Line has an unfortunate value,
			// when calculating Line.y at p.x.
			// But the midpoint calculated below should be guaranteed to be on the line,
			// so at that Point rounding errors are not forgivable.
			Point midPoint;

            if ( dx != 0 ) {
				double slope = dy/dx;
				double halfWay = Math.Round(dx*0.5d, 0);
				midPoint = new(
					line.start.x + (int)halfWay,
					line.start.y + (int)Math.Round(halfWay*slope, 0));
			} else if ( dy != 0) {
				double invSlope = dx / dy;
				double halfWay = Math.Round(dy*0.5d, 0);
				midPoint = new(
					line.start.x + (int)Math.Round(halfWay*invSlope, 0),
					line.start.y + (int)halfWay);
			} else {
				// dx == dy == 0, so start == end
				midPoint = line.start;
			}

			Assert.That(
				line.Includes(midPoint), Is.True,
				line.ToString() + ",\n\t" + midPoint.ToString()
				+ "\nMidpoint should always be included.");
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.GenericLineTestCases))]
		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIncludesStartAndEnd(Line line)
		{
			Assert.That(
				line.Includes(line.start), Is.True,
				"Line.start should be included.");
			Assert.That(
				line.Includes(line.end), Is.True,
				"Line.end should be included.");
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.GenericLineTestCases))]
		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineDoesNotIncludePointNotOnLine(Line line)
		{
			int dx = line.end.x - line.start.x;
			int dy = line.end.y - line.start.y;
			Point notOnLine;
			if (!(dx == 0 && dy == 0)) {
				// I think this should work unless dx and dy are both 0?
				// Since line.end.x == line.start.x + dx and line.end.y == line.start.y + dy
				notOnLine = new(
					line.start.x - dx,
					line.start.y - dy);
			} else {
				// The line is either vertical or horizontal, so a point diagonally up and right can't be on the line
				notOnLine = new(
					line.start.x + 1,
					line.start.y + 1);
			}
			Assert.That(
				line.Includes(notOnLine), Is.Not.True,
				line.ToString() + ",\n\t" + notOnLine.ToString()
				+ "\nAngled line, point should never be on the line.");
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIntersectsPointToLeft(Line line)
		{
			int minX = Math.Min(line.start.x, line.end.x);

			Point farLeftAtStart = new(minX - 1, line.start.y);
			Point farLeftAtEnd = new(minX - 1, line.end.y);

			Assert.That(line.Intersects(farLeftAtStart), Is.True );
			Assert.That(line.Intersects(farLeftAtEnd), Is.True);
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIntersectsPointToRight(Line line)
		{
			int maxX = Math.Max(line.start.x, line.end.x);

			Point farRightAtStart = new(maxX + 1, line.start.y);
			Point farRightAtEnd = new(maxX + 1, line.end.y);

			Assert.That(line.Intersects(farRightAtStart), Is.Not.True);
			Assert.That(line.Intersects(farRightAtEnd), Is.Not.True);
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIntersectsPointBelowLine(Line line)
		{
			int minY = Math.Min(line.start.y, line.end.y);

			Point farBelowAtStart = new(line.start.x, minY - 1);
			Point farBelowAtEnd = new(line.end.x, minY - 1);

			Assert.That(line.Intersects(farBelowAtStart), Is.Not.True,
				"A point below lowest point of line should never intersect");
			Assert.That(line.Intersects(farBelowAtEnd), Is.Not.True,
				"A point below lowest point of line should never intersect");
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIntersectsPointAboveLine(Line line)
		{
			int maxY = Math.Max(line.start.y, line.end.y);
			
			Point farAboveAtStart = new(line.start.x, maxY + 1);
			Point farAboveAtEnd = new(line.end.x, maxY + 1);

			Assert.That(line.Intersects(farAboveAtStart), Is.Not.True,
				"A point above highest point of line should never intersect");
			Assert.That(line.Intersects(farAboveAtEnd), Is.Not.True,
				"A point above highest point of line should never intersect");
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.LineIntersectsPointLeftOfMidpoint))]
		public bool TestLineIntersectsPointLeftOfMidpoint(Line line, Point p)
		{
			TestContext.WriteLine(line.ToString() + "\n\t" + p.ToString());
			return line.Intersects(p);
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.LineIntersectsPointRightOfMidpoint))]
		public bool TestLineIntersectsPointRightOfMidpoint(Line line, Point p)
		{
			TestContext.WriteLine(line.ToString() + "\n\t" + p.ToString());
			return line.Intersects(p);
		}

		[Test]
		public void TestPolygonGetLines()
		{
		}

		[Test]
		public void TestPolygonContains()
		{
		}

		[Test]
		public void TestPolygonPerimiterContains()
		{
		}

		[Test]
		public void TestPolygonClassify()
		{
		}

		[Test]
		public void TestPolygonClassifyPoint()
		{
		}
	}

	public class TestData
	{
		private static readonly int numGenCases = 1000;
		// The likelyhood of encountering rounding errors goes up with range of RandomPoint
		private static readonly int rngPointMin = -10000;
		private static readonly int rngPointMax = 10000;

		private static Point RandomPoint
		{
			get
			{
				return new Point(
					TestContext.CurrentContext.Random.Next(rngPointMin, rngPointMax),
					TestContext.CurrentContext.Random.Next(rngPointMin, rngPointMax));
			}
		}
		private static Line RandomLine
        {
			get
            {
				return new Line( RandomPoint, RandomPoint );
            }
        }
		private static IEnumerable RandGenLines
		{
			get
			{
				for (int i = 0; i < numGenCases; ++i) {
					yield return RandomLine;
				}
			}
		}

		public static IEnumerable GenericLineTestCases
		{
			get
			{
				yield return new TestCaseData(
					new Line(new Point(-10, 0), new Point(10, 0)))
					.SetName("{m}(Horizontal Line)");
				yield return new TestCaseData(
					new Line(new Point(0, -10), new Point(0, 10)))
					.SetName("{m}(Vertical Line)");
				yield return new TestCaseData(
					new Line(new Point(-10, -10), new Point(10, 10)))
					.SetName("{m}(Diagonal Line up right)");
				yield return new TestCaseData(
					new Line(new Point(10, 10), new Point(-10, -10)))
					.SetName("{m}(Diagonal Line down left)");
				yield return new TestCaseData(
					new Line(new Point(-10, 10), new Point(10, -10)))
					.SetName("{m}(Diagonal Line down right)");
				yield return new TestCaseData(
					new Line(new Point(10, -10), new Point(-10, 10)))
					.SetName("{m}(Diagonal Line up left)");
			}
		}
		public static IEnumerable RandGenLineTestCases {
			get {
				foreach (Line line in RandGenLines) {
					yield return new TestCaseData(line)
						.SetName("{m}(Randomly generated Line)");
					// ".SetName" is a workaround for random generation of testdata in conjunction with VS nUnit test adapter
				}
			}
		}
		public static IEnumerable LineIntersectsPointLeftOfMidpoint
		{
			get
			{
				foreach (Line line in RandGenLines)
				{
					int dy = line.end.y - line.start.y;
					int dx = line.end.x - line.start.x;

                    if ( Math.Abs(dx) < 3 ) {
						// Bounding box too small, it will be a pain in the butt to find a point guaranteed
						// To be within the bounding box but still to the left of the line.
						//TODO: Might be possible with some fancy math transformations
						continue;
                    }
					if (dy != 0 && dx != 0)
					{
						int halfwayUp;
						if (line.Slope > 0) {
							halfwayUp = line.start.y + (int)Math.Ceiling(dy * 0.5d);
						} else {
							halfwayUp = line.start.y + (int)Math.Floor(dy * 0.5d);
						}
						int slightlyLeftOfHMidpoint =
								line.MinX + Math.Abs((int)Math.Floor(dx * 0.5d)) - 1;
					
						Point leftOfMidpoint = new( slightlyLeftOfHMidpoint, halfwayUp );

						yield return new TestCaseData(line, leftOfMidpoint)
							.Returns(true)
							.SetName("{m}(Randomly generated Line, Point left of Lines midpoint)");
					}
				}
			}
		}
		public static IEnumerable LineIntersectsPointRightOfMidpoint
		{
			get
			{
				foreach (Line line in RandGenLines)
				{
					int dy = line.end.y - line.start.y;
					int dx = line.end.x - line.start.x;
                    if ( Math.Abs(dx) < 3 ) {
						continue;
					}
					if (dy != 0 && dx != 0) {
						int halfwayUp;
                        if ( line.Slope > 0 ) {
							halfwayUp = line.start.y + (int)Math.Floor(dy * 0.5d);
						} else {
							halfwayUp = line.start.y + (int)Math.Ceiling(dy * 0.5d);
						}
						int slightlyRightOfMidpoint =
							line.MinX + Math.Abs((int)Math.Ceiling(dx * 0.5d)) + 1;

						Point rightOfMidpoint = new( slightlyRightOfMidpoint, halfwayUp );

						yield return new TestCaseData( line, rightOfMidpoint )
							.Returns(false)
							.SetName("{m}(Randomly generated Line, Point right of Lines midpoint)");
					}
				}
			}
		}
	}
}