using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows;


namespace LabWork_1
{
    class Line
    {
        public PointF Start { get; set; }

        public PointF End { get; set; }
    }

    class CyrusBeck
    {
        private static PointF[] window;

        private static Line GetInsidePart(Line line)
        {
            double tin = 0;
            double tout = 1;

            for (int i = 0; i < window.Length; i++)
            {
                var edge = new Line { Start = window[i], End = window[(i + 1) % window.Length] };
                Vector n = GetN(edge, window[(i + 2) % window.Length]);
                var d = new Vector(line.End.X - line.Start.X, line.End.Y - line.Start.Y);
                var w = new Vector(line.Start.X - edge.End.X, line.Start.Y - edge.End.Y);
                if (Math.Abs(d * n) < 0.0001)
                {
                    if (w * n < 0)
                    {
                        return null;
                    }
                    else
                    {
                        continue;
                    }
                }
                double t = -(w * n) / (d * n);
                if (d * n >= 0) //Фронтальное ребро
                {
                    tin = t > tin ? t : tin;
                }
                else      //Тыльное ребро
                {
                    tout = t < tout ? t : tout;
                }
            }

            if (tin < tout)
            {
                return new Line { Start = GetPointF(line, tin), End = GetPointF(line, tout) };
            }
            return null;
        }

        private static Line GetOutsidePart(Line line)
        {
            double tin = 0;
            double tout = 1;

            for (int i = 0; i < window.Length; i++)
            {
                var edge = new Line { Start = window[i], End = window[(i + 1) % window.Length] };
                Vector n = GetN(edge, window[(i + 2) % window.Length]);
                var d = new Vector(line.End.X - line.Start.X, line.End.Y - line.Start.Y);
                var w = new Vector(line.Start.X - edge.End.X, line.Start.Y - edge.End.Y);
                if (Math.Abs(d * n) < 0.0001)
                {
                    if (w * n < 0)
                    {
                        return null;
                    }
                    else
                    {
                        continue;
                    }
                }
                double t = -(w * n) / (d * n);
                if (d * n >= 0) //Фронтальное ребро
                {
                    tin = t > tin ? t : tin;
                }
                else      //Тыльное ребро
                {
                    tout = t < tout ? t : tout;
                }
            }

            if (tin < tout)
            {
                return new Line { Start = GetPointF(line, tin), End = GetPointF(line, tout) };
            }
            return null;
        }

        private static PointF GetPointF(Line line, double t)
        {
            return new PointF(line.Start.X + (float)t * (line.End.X - line.Start.X),
                line.Start.Y + (float)t * (line.End.Y - line.Start.Y));
        }

        private static Vector GetN(Line edgeLine, PointF nextPoint)
        {
            var edge = new Vector(edgeLine.End.X - edgeLine.Start.X, edgeLine.End.Y - edgeLine.Start.Y);
            var n = Math.Abs(edge.Y) < 0.001 ? new Vector(0, 1) : new Vector(1, -edge.X / edge.Y);
            var nextEdge = new Vector(nextPoint.X - edgeLine.End.X, nextPoint.Y - edgeLine.End.Y);
            if (nextEdge * n < 0)
            {
                n *= -1;
            }
            return n;
        }

        private static void SwapPointF(ref Line line)
        {
            PointF buf = line.Start;
            line.Start = line.End;
            line.End = buf;
        }

        public static List<Line> Work(List<Line> lines, PointF[] windowCoords)
        {
            List<Line> result = new List<Line>();
            window = windowCoords;
            foreach (var line in lines)
            {
                Line insidePart = GetInsidePart(line);
                if (insidePart != null)
                    result.Add(insidePart);
            }
            return result;
        }
    }
}
