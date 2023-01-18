using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace lab_work4
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
            transMatrix = GetTarnsMatrix();
        }

        private const double angle = Math.PI / 180;

        private static double Alpha = 45 * angle;
        private static double Betha = -50 * angle;
        private const int Ro = 14*L;
        private const int D = 3 * L;
        
        //Prism parametrs
        private const int L = 500;
        private const int X0 = 0;
        private const int Y0 = 0;
        private const int Z0 = 0; 
        private const int Xlen = L;
        private const int Ylen = L;
        private const int Zlen =  L;

        private double currentRo = Alpha;

        private static readonly Color ImageBackColor = Color.White;

        private readonly Pen mainPen = new Pen(Color.Red, 3);
        private readonly Pen axisPen = new Pen(Color.Green, 3);
        MouseController mouseController = new MouseController();

        private static double prismAngle = 2 * Math.PI / 5;

        private double[,] startPrism =
        {
                { X0 + Xlen/2*Math.Cos(0*prismAngle), Y0 + Ylen/2*Math.Sin(0 * prismAngle), Z0, 1},
                { X0 + Xlen/2*Math.Cos(1*prismAngle), Y0 + Ylen/2*Math.Sin(1 * prismAngle), Z0, 1},
                { X0 + Xlen/2*Math.Cos(2*prismAngle), Y0 + Ylen/2*Math.Sin(2 * prismAngle), Z0, 1},
                { X0 + Xlen/2*Math.Cos(3*prismAngle), Y0 + Ylen/2*Math.Sin(3 * prismAngle), Z0, 1},
                { X0 + Xlen/2*Math.Cos(4*prismAngle), Y0 + Ylen/2*Math.Sin(4 * prismAngle), Z0, 1},
                { X0 + Xlen/2*Math.Cos(0*prismAngle), Y0 + Ylen/2*Math.Sin(0 * prismAngle), Z0 + Zlen, 1},
                { X0 + Xlen/2*Math.Cos(1*prismAngle), Y0 + Ylen/2*Math.Sin(1 * prismAngle), Z0 + Zlen, 1},
                { X0 + Xlen/2*Math.Cos(2*prismAngle), Y0 + Ylen/2*Math.Sin(2 * prismAngle), Z0 + Zlen, 1},
                { X0 + Xlen/2*Math.Cos(3*prismAngle), Y0 + Ylen/2*Math.Sin(3 * prismAngle), Z0 + Zlen, 1},
                { X0 + Xlen/2*Math.Cos(4*prismAngle), Y0 + Ylen/2*Math.Sin(4 * prismAngle), Z0 + Zlen, 1},
            };

        private readonly int[,] edges = {
            {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0},
            {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 5},
            {0,5}, {1,6}, {2,7}, {3,8}, {4,9},
        };

        private double[,] transMatrix = new double[4, 4];

        private Bitmap image;

        private Graphics graphics;

        private void goButton_Click(object sender, EventArgs e)
        {
            Draw();
        }

        private double[,] GetTarnsMatrix()
        {
            double a = Math.Cos(currentRo + angle * mouseController.offset.Y);
            double b = Math.Sin(currentRo + angle * mouseController.offset.Y);
            double c = Math.Cos(Betha + angle * mouseController.offset.X);
            double d = Math.Sin(Betha + angle * mouseController.offset.X);
            return new double[,] {{-d, -a*c, -b*d,        0},
                                  {c,  -a*d, -b*d,        0},
                                  {0,  b,    -a,          0},
                                  {0,  0,    Ro,   1}};
        }

        private void Draw()
        {
            image = new Bitmap(pictureBox1.Width, pictureBox1.Height);
            graphics = Graphics.FromImage(image);
            graphics.TranslateTransform(pictureBox1.Width / 2, pictureBox1.Height / 2);
            graphics.Clear(ImageBackColor);
            transMatrix = GetTarnsMatrix();
            DoAnimation(graphics);
            pictureBox1.Image = image;
        }

        private void DrawCoord()
        {
            int length = 550;
            Font font = new Font(Font.Name, 10f);
            double[,] xyz = new double[,] {
                {-length, 0, 0 , -1 },
                {0, -length, 0 , -1 },
                {0, 0, -length , -1 }
            };

            double[,] d = Multiplication(xyz, transMatrix);
            List<PointF> coords = Get2DCoordinate(d);
            foreach (PointF p in coords)
            {
                graphics.DrawLine(axisPen, p, new PointF(0, 0));
            }

            graphics.DrawString("x", font, Brushes.Black, coords[0]);
            graphics.DrawString("y", font, Brushes.Black, coords[1]);
            graphics.DrawString("z", font, Brushes.Black, coords[2]);
        }

        private void DrawPrism(Graphics graphics1)
        {
            double[,] viewCoords = Multiplication(startPrism, transMatrix);
            List<PointF> twoDCoordinate = Get2DCoordinate(viewCoords);
            DrawFigure(twoDCoordinate, graphics1, mainPen, GetHidenPoint(viewCoords));
        }

        private void DoAnimation(Graphics graphics1)
        {
            //DrawPrism(graphics1);
            timer1.Enabled = true;
        }

        private PointF Get2DCoordinate(double x, double y, double z)
        {
            return new PointF((float) (D*x/z), (float) (D*y/z));
        }

        private List<PointF> Get2DCoordinate(double[,] viewCoordinats)
        {
            if (viewCoordinats.GetLength(1) < 3) throw new ArgumentException("Invalid view coordinates");
            var result = new List<PointF>();
            for (int i = 0; i < viewCoordinats.GetLength(0); i++)
            {
                result.Add(Get2DCoordinate(viewCoordinats[i, 0], viewCoordinats[i, 1], viewCoordinats[i, 2]));
            }
            return result;
        }

        private int GetHidenPoint(double[,] viewCoordinats)
        {
            List<Point3D> standart = CoordList(viewCoordinats);
            List<Point3D> viewList = standart.GetRange(0, 10);

            viewList.Sort((x, y) => -(int) (x.Y - y.Y));
            viewList = viewList.GetRange(0, 5);
            viewList.Sort((x, y) => -(int)(x.X * x.X + x.Z * x.Z - (y.X * y.X + y.Z * y.Z)));
            Point3D point = viewList[0];
            return standart.FindIndex(x => Math.Abs(x.X - point.X) < 0.1 && Math.Abs(x.Y - point.Y) < 0.1 && Math.Abs(x.Z - point.Z) < 0.1);
        }

        private List<Point3D> CoordList(double[,] viewCoordinats)
        {
            var result = new List<Point3D>();
            for (int i = 0; i < viewCoordinats.GetLength(0); i++)
            {
                result.Add(new Point3D { X = viewCoordinats[i, 0], Y = viewCoordinats[i, 1], Z = viewCoordinats[i, 2] });
            }
            return result;
        }


        private void DrawFigure(IReadOnlyList<PointF> points, Graphics gr, Pen pen, int hidenPoint)
        {
            Font font = new Font(Font.Name, 18f);
            for (int i = 0; i < edges.GetLength(0); i++)
            {
                if (edges[i, 0] != hidenPoint && edges[i, 1] != hidenPoint)
                {
                    pen.DashStyle = DashStyle.Solid;
                    gr.DrawLine(pen, points[edges[i, 0]], points[edges[i, 1]]);
                }
                else
                {
                    pen.DashStyle = DashStyle.Dash;
                    gr.DrawLine(pen, points[edges[i, 0]], points[edges[i, 1]]);
                }
                gr.DrawString(edges[i, 0].ToString(), font, Brushes.Black, points[edges[i, 0]]);
            }
            pen.DashStyle = DashStyle.Solid;
        }

       
        private void Tick(object sender, EventArgs e)
        {
            currentRo += 0.01;
            DrawNextFigure();
        }

        private void DrawNextFigure()
        {
            graphics.Clear(ImageBackColor);
            transMatrix = GetTarnsMatrix();
            DrawCoord();
            DrawPrism(graphics);
            pictureBox1.Image = image;
        }

        static double[,] Multiplication(double[,] a, double[,] b)
        {
            if (a.GetLength(1) != b.GetLength(0)) throw new Exception("Матрицы нельзя перемножить");
            var r = new double[a.GetLength(0), b.GetLength(1)];
            for (int i = 0; i < a.GetLength(0); i++)
            {
                for (int j = 0; j < b.GetLength(1); j++)
                {
                    for (int k = 0; k < b.GetLength(0); k++)
                    {
                        r[i, j] += a[i, k] * b[k, j];
                    }
                }
            }
            return r;
        }

        //Point startMouse = 
        bool isTab = false;
        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            //Console.WriteLine("Down  = " + Cursor.Position);
            mouseController.Start(Cursor.Position);
            isTab = true;
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            //Console.WriteLine("Up = " + Cursor.Position);
            mouseController.End(Cursor.Position);
            isTab = false;
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (isTab)
            {
                mouseController.Move(Cursor.Position);
            }
            //Console.WriteLine("Move = " + Cursor.Position);
        }

        private class MouseController
        {
            public Point start;
            public PointF offset;

            public void Start(Point startPoint)
            {
                start = startPoint;
            }

            public void Move(Point pos)
            {
                Point res = new Point(pos.X - start.X, pos.Y - start.Y);
                offset = new PointF(res.X * 0.2f, res.Y * 0.2f);
            }

            public void End(Point endPoint)
            {
                //offset = PointF.Empty;
            }
        }

        private class Point3D
        {
            public double X { get; set; }

            public double Y { get; set; }

            public double Z { get; set; }
        }

    }
}
