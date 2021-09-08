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
			float dx = line.end.x - line.start.x;
			float dy = line.end.y - line.start.y;
			if (dx == 0.0f || dy == 0.0f) {
				if (dx == 0.0f) {
					Assert.That(
						delegate { _ = line.Slope; },
						Throws.Exception);
				}
				if (dy == 0.0f) {
					Assert.That(
						delegate { _ = line.InvSlope; },
						Throws.Exception);
				}
				if (dx == 0.0f && dy != 0.0f) {
					Assert.That(line.InvSlope, Is.EqualTo(0.0f));
				}
				if (dx != 0.0f && dy == 0.0f)
				{
					Assert.That(line.Slope, Is.EqualTo(0.0f));
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
			float dx = line.end.x - line.start.x;
			float dy = line.end.y - line.start.y;

			Point midPoint = new(
				line.start.x + (int)Math.Round(dx * 0.5f),
				line.start.y + (int)Math.Round(dy * 0.5f));
			Assert.That(
				line.Includes(midPoint), Is.True,
				line.ToString() + ",\n\t" + midPoint.ToString()
				+ "\nMidpoint should be included.");
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
			if (!(dx == 0.0f && dy == 0.0f)) {
				// I think this should work unless dx and dy are both 0?
				// Since line.end.x == line.start.x + dx and line.end.y == line.start.y + dy
				Point notOnLine = new(
					line.start.x - dx,
					line.start.y - dy);
				Assert.That(
					line.Includes(notOnLine), Is.Not.True,
					line.ToString() + ",\n\t" + notOnLine.ToString()
					+ "\nAngled line, point should never be on the line.");
			} else {
				// The line is either vertical or horizontal, so a point diagonally up and right can't be on the line
				Point notOnLine = new(
					line.start.x + 1,
					line.start.y + 1);
				Assert.That(
					line.Includes(notOnLine), Is.Not.True,
					line.ToString() + ",\n\t" + notOnLine.ToString()
					+ "\nVertical or Horizontal line,"
					+ "\nA point diagonally up and to the right should never be on the line.");
			}
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIntersectsPointLeftOfLineStart(Line line)
		{
			int minX = Math.Min(line.start.x, line.end.x);
			Point farLeftAtStart = new(minX - 1, line.start.y);
			Assert.That( line.Intersects(farLeftAtStart), Is.True );
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIntersectsPointRightOfLineStart(Line line)
		{
			int maxX = Math.Max(line.start.x, line.end.x);
			Point farRightAtStart = new(maxX + 1, line.start.y);
			Assert.That(line.Intersects(farRightAtStart), Is.Not.True);
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIntersectsPointLeftOfLineEnd(Line line)
		{
			int minX = Math.Min(line.start.x, line.end.x);
			Point farLeftAtEnd = new(minX - 1, line.end.y);
			Assert.That(line.Intersects(farLeftAtEnd), Is.True );
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIntersectsPointRightOfLineEnd(Line line)
		{
			int maxX = Math.Max(line.start.x, line.end.x);
			Point farRightAtEnd = new(maxX + 1, line.end.y);
			Assert.That(line.Intersects(farRightAtEnd), Is.Not.True );
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIntersectsPointBelowLineStart(Line line)
		{
			int minY = Math.Min(line.start.y, line.end.y);
			Point farBelowAtStart = new(line.start.x, minY - 1);
			Assert.That(line.Intersects(farBelowAtStart), Is.Not.True);
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIntersectsPointAboveLineStart(Line line)
		{
			int maxY = Math.Max(line.start.y, line.end.y);
			Point farAboveAtStart = new(line.start.x, maxY + 1);
			Assert.That(line.Intersects(farAboveAtStart), Is.Not.True );
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIntersectsPointBelowLineEnd(Line line)
		{
			int minY = Math.Min(line.start.y, line.end.y);
			Point farBelowAtEnd = new(line.end.x, minY - 1);
			Assert.That( line.Intersects(farBelowAtEnd), Is.Not.True );
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.RandGenLineTestCases))]
		public void TestLineIntersectsPointAboveLineEnd(Line line)
		{
			int maxY = Math.Max(line.start.y, line.end.y);
			Point farAboveAtEnd = new(line.end.x, maxY + 1);
			Assert.That(line.Intersects(farAboveAtEnd), Is.Not.True );
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.LineIntersectsPointLeftOfMidpoint))]
		public bool TestLineIntersectsPointLeftOfMidpoint(Line line, Point p)
		{
			return line.Intersects(p);
		}

		[TestCaseSource(typeof(TestData), nameof(TestData.LineIntersectsPointRightOfMidpoint))]
		public bool TestLineIntersectsPointRightOfMidpoint(Line line, Point p)
		{
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
		private static readonly int numGenCases = 100;
		private static IEnumerable RandGenLines
		{
			get
			{
				for (int i = 0; i < numGenCases; ++i) {
					Random rng = new(i);
					yield return new Line(
						new Point(
							rng.Next(-10000, 10000),
							rng.Next(-10000, 10000)),
						new Point(
							rng.Next(-10000, 10000),
							rng.Next(-10000, 10000)));
					/*
					yield return new Line(
						new Point(
							rng.Next(int.MinValue, int.MaxValue),
							rng.Next(int.MinValue, int.MaxValue)),
						new Point(
							rng.Next(int.MinValue, int.MaxValue),
							rng.Next(int.MinValue, int.MaxValue)));
					*/
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
					// Workaround for random generation of testdata in conjunction with VS nUnit test adapter
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
					if (dy != 0) {
						int dx = line.end.x - line.start.x;
						Point leftOfMidpoint = new(
							line.start.x + (int)Math.Round((float)dx / 2) - 1,
							line.start.y + (int)Math.Round((float)dy / 2));

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
					if (dy != 0 ) {
						int dx = line.end.x - line.start.x;
						Point rightOfMidpoint = new(
							line.start.x + (int)Math.Round((float)dx/2) + 1,
							line.start.y + (int)Math.Round((float)dy/2) );

						yield return new TestCaseData( line, rightOfMidpoint )
							.Returns(false)
							.SetName("{m}(Randomly generated Line, Point right of Lines midpoint)");
					}
				}
			}
		}
	}
}