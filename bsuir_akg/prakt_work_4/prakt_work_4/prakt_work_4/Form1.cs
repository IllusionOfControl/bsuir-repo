using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Drawing2D;
using System.Windows.Forms;

namespace prakt_work_4
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            transMatrix = GetTarnsMatrix();
        }

        MouseController mouseController = new MouseController();       
        private const double angle = Math.PI / 180;

        private double Alpha = -45 * angle;
        private double Betha = 45 * angle;
        private const int Ro = 25 * L;
        private const int D = 10 * L;
        private const double Sin60 = 0.86602540378443864676372317075294;

        // параметры призмы
        private const int L = 500;
        private const int X0 = 100;
        private const int Y0 = 100;
        private const int Z0 = 0;
        private const int TwoDlen = L;
        private const int Zlen =  L;
        private double currentAlpha = 0;
        private const int TriangleRad = TwoDlen / 2;
        private static readonly Color ImageBackColor = Color.White;
        
        private readonly Pen mainPen = new Pen(Color.Red, 3);
        private readonly Pen axisPen = new Pen(Color.Green, 3);
        private readonly double[,] startPrism =
       {
            {X0 - TwoDlen/2, Y0                  , Z0  , 1 },
            {X0            , Y0 + TwoDlen/2      , Z0  , 1 },
            {X0 + TwoDlen/2, Y0                  , Z0       , 1 },
            {X0 + TwoDlen/4, Y0 - TwoDlen/2*Sin60, Z0       , 1 },
            {X0 - TwoDlen/4, Y0 - TwoDlen/2*Sin60, Z0       , 1 },
            {X0 - TwoDlen/2, Y0                  , Z0 + Zlen, 1 },
            {X0            , Y0 + TwoDlen/2      , Z0 + Zlen, 1 },
            {X0 + TwoDlen/2, Y0                  , Z0 + Zlen, 1 },
            {X0 + TwoDlen/4, Y0 - TwoDlen/2*Sin60, Z0 + Zlen, 1 },
            {X0 - TwoDlen/4, Y0 - TwoDlen/2*Sin60, Z0 + Zlen, 1 },
        };

        private double[,] triangle = new double[3, 4];

        private double[,] transMatrix = new double[4, 4];

        private readonly int[,] edges =
        {
            {0, 1}, {1, 2}, {2, 3}, {3, 4}, {4, 0}, {5, 6}, {6, 7}, {7, 8}, {8, 9}, {9, 5}, {0, 5}, {1, 6}, {2, 7},
            {3, 8}, {4, 9}
        };

        private Bitmap image;

        private Graphics canvas;

        private void GoButton(object sender, EventArgs e)
        {
            Draw();
        }

        // генерация ротационной матрицы
        private double[,] GetTarnsMatrix()
        {
            double a = Math.Cos(Alpha + angle * mouseController.offset.Y);
            double b = Math.Sin(Alpha + angle * mouseController.offset.Y);
            double c = Math.Cos(Betha + angle * mouseController.offset.X);
            double d = Math.Sin(Betha + angle * mouseController.offset.X);
            return new double[,] {{-d, -a*c, -b*d,        0}, 
                                  {c,  -a*d, -b*d,        0}, 
                                  {0,  b,    -a,          0}, 
                                  {0,  0,    Ro,          1}};
        }

        // рисовние всего
        private void Draw()
        {
            currentAlpha = 0;
            image = new Bitmap(bitmap.Width, bitmap.Height);
            canvas = Graphics.FromImage(image);
            canvas.TranslateTransform(bitmap.Width / 2, bitmap.Height / 2 + 100);
            canvas.Clear(ImageBackColor);
            transMatrix = GetTarnsMatrix();
            DoAnimation(canvas);
            bitmap.Image = image;
        }


        private void DrawCoord()
        {
            int length = 550;
            Font font = new Font(Font.Name, 10f);
            double[,] xyz = new double[,] {
                {-length, 0, 0 , -1 } ,
                {0, -length, 0 , -1 } ,
                {0, 0, -length , -1 }
            };

            double[,] d = MatrixMul(xyz, transMatrix);
            List<PointF> coords = Get2DCoordinate(d);
            foreach (PointF p in coords)
            {
                canvas.DrawLine(axisPen, p, new PointF(0, 0));
            }


            canvas.DrawString("x", font, Brushes.Black, coords[0]);
            canvas.DrawString("y", font, Brushes.Black, coords[1]);
            canvas.DrawString("z", font, Brushes.Black, coords[2]);
        }

        // получение матрицы треогольника 
        private double[,] GetTriangleMatrix()
        {
           return new double[,]
            {{X0, Y0, Z0,1}, {X0, Y0, Z0,1}, {X0 + TriangleRad, Y0 + TwoDlen/4, Z0 ,1}};
            //{{X0, Y0, Z0,1}, {X0+ TwoDlen/4, Y0, Z0,1}, {X0 + TwoDlen/2, Y0, Z0,1}};
        }

        // рисование призмы
        private void DrawPrism(Graphics canvas)
        {
            double[,] viewCoords = MatrixMul(startPrism, transMatrix);
            List<PointF> twoDCoordinate = Get2DCoordinate(viewCoords);
            DrawFigure(twoDCoordinate, canvas, mainPen, 0);
        }

        // анимирование
        private void DoAnimation(Graphics canvas)
        {
            DrawPrism(canvas);
            timer1.Enabled = true;
        }

        // преобразование 3D координат в 2D
        private PointF Get2DCoordinate(double x, double y, double z)
        {
            return new PointF((float) (D*x/z), (float) (D*y/z));
        }

        // преобразование 3D координат в 2D
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

        // Рисование фигуры
        private void DrawFigure(IReadOnlyList<PointF> points, Graphics gr, Pen pen, int hidenPoint)
        {
            for (int i = 0; i < edges.GetLength(0); i++)
            {
                if ((edges[i, 0] != 4 && edges[i, 1] != 4) && (edges[i, 0] != 0 && edges[i, 1] != 0))
                {
                    pen.DashStyle = DashStyle.Solid;
                    gr.DrawLine(pen, points[edges[i, 0]], points[edges[i, 1]]);
                }
                else
                {
                    //pen.DashStyle = DashStyle.Dash;
                    gr.DrawLine(pen, points[edges[i, 0]], points[edges[i, 1]]);
                }
            }
            pen.DashStyle = DashStyle.Solid;
        }

       // Рисование треугольника
        private void DrawTriangle(Graphics canvas)
        {
            triangle[1, 0] += TriangleRad * Math.Cos(currentAlpha) + TriangleRad * Math.Sin(currentAlpha);
            triangle[1, 2] += TriangleRad * Math.Cos(currentAlpha) - TriangleRad * Math.Sin(currentAlpha);

            triangle[2, 0] += TriangleRad * Math.Cos(currentAlpha) + TriangleRad * Math.Sin(currentAlpha);
            triangle[2, 2] += TriangleRad * Math.Cos(currentAlpha) - TriangleRad * Math.Sin(currentAlpha);
            double[,] viewCoords = MatrixMul(triangle, transMatrix);

            List<PointF> twoDCoordinate = Get2DCoordinate(viewCoords);
            canvas.DrawLine(mainPen, twoDCoordinate[0], twoDCoordinate[1]);
            canvas.DrawLine(mainPen, twoDCoordinate[1], twoDCoordinate[2]);
            canvas.DrawLine(mainPen, twoDCoordinate[2], twoDCoordinate[0]);
        }

        private void Tick(object sender, EventArgs e)
        {
            currentAlpha += 0.01;
            DrawNextFigure();
        }

        // рисование Фигур
        private void DrawNextFigure()
        {
            canvas.Clear(ImageBackColor);
            transMatrix = GetTarnsMatrix();
            triangle = GetTriangleMatrix();
            DrawPrism(canvas);
            DrawTriangle(canvas);
            DrawCoord();
            bitmap.Image = image;
        }

        static double[,] MatrixMul(double[,] a, double[,] b)
        {
            if (a.GetLength(1) != b.GetLength(0)) throw new Exception();
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

         bool isTab = false;
        private void pictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            mouseController.Start(Cursor.Position);
            isTab = true;
        }

        private void pictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            mouseController.End(Cursor.Position);
            isTab = false;
        }

        private void pictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (isTab)
            {
                mouseController.Move(Cursor.Position);
            }
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
                offset = PointF.Empty;
            }
        }
    }

    public class Point3D
    {
        public double X { get; set; }

        public double Y { get; set; }

        public double Z { get; set; }
    }
}
