using System;
using System.Drawing;
using System.Windows.Forms;

namespace LabWork_1
{
    public partial class MainForm : Form
    {
        public MainForm()
        {
            InitializeComponent();
        }

        // заданый sin
        private const double Sin60 = 0.86602540378443864676372317075294;
        
        // параметры для рисовки
        private static readonly Color BackgroundColor = Color.White;
        private readonly Pen mainPen = new Pen(Color.Red, 3);
        private readonly Pen secondPen = new Pen(BackgroundColor, 3);

        // размеры фигур фигуры
        private const int FigureSize = 80;

        // сдвиги по X и Y
        private double[,] offsets = new double[6, 2];

        private PointF[] currentPoints = new PointF[5];

        private int stepNumber = 0;
        private const int StepsCount = 30;

        private Bitmap canvas;

        private Graphics graphics;

        private void goButton_Click(object sender, EventArgs e)
        {
            Draw();
        }

        private void Draw()
        {
            canvas = new Bitmap(canvasBox.Width, canvasBox.Height);  // buffer
            graphics = Graphics.FromImage(canvas);                       // создание холста
            graphics.Clear(BackgroundColor);
            stepNumber = 0;
            DoAnimation(graphics);                                      // анимация
            canvasBox.Image = canvas;                                  // ???
        }

        // анимировать
        private void DoAnimation(Graphics graphics)
        {
            SetFirstPosition(graphics);                                 // 
            WriteFigure(currentPoints, graphics, mainPen);              //
            timer1.Enabled = true;                                      
        }

        private void SetFirstPosition(Graphics graphics)
        {
            Tuple<Point, Point> positions = GetSourceAndTargetPosition();    // создаём кортеж начальных и конечных точек
            var fisrtFigurePoints = GetFirstFigurePoints(positions.Item1);    // получение точек исходной фигуры
            var pentagonVertexes = GetPentagonVertexes(fisrtFigurePoints);            // получение начальных точек промежуточной фигуры
            pentagonVertexes.CopyTo(currentPoints, 0);                       // задание промежуточных точек промежуточной фигуры
            CalculateOffset(currentPoints, GeеIntermediatePoints());                // ????
        }

        // возвращает массив с промежуточными точками
        private PointF[] GeеIntermediatePoints()
        {
            float x = (float)canvasBox.Width / 2;
            float midY = (float)canvasBox.Height / 2;

            return new PointF[]
            {
                new PointF(x, midY - FigureSize/2),
                new PointF(x, midY),
                new PointF(x, midY),
                new PointF(x, midY),
                new PointF(x, midY + FigureSize/2)
            };
        }


        // возвращает кортеж с (начальные, конечные) координаты
        private Tuple<Point, Point> GetSourceAndTargetPosition()
        {
            return new Tuple<Point, Point>(new Point(FigureSize/2 + 20, FigureSize/2 + 20),
                new Point(canvasBox.Width - FigureSize - 20, canvasBox.Height - FigureSize - 20));
        }

        // получение координат итоговой фигуры
        /**           1 |--------\ 2
         *              |         \ 
         *              |          \ 3
         *              |          /
         *              |         /
         *            5 |--------/ 4
         */
        private PointF[] GetSecondFigurePoints(Point startPosition)
        {
            return new PointF[]
            {
                new PointF(startPosition.X - FigureSize/2, startPosition.Y - FigureSize/2),
                new PointF(startPosition.X + FigureSize/2, startPosition.Y - FigureSize/2),
                new PointF(startPosition.X + FigureSize/2, startPosition.Y + FigureSize/2),
                new PointF(startPosition.X - FigureSize/2, startPosition.Y + FigureSize/2)
            };
        }


        // получение координат исходной фигуры
        // создание координат квадрата
        /*
              1 |--------|
                |        |
                |        |
                |        |
                |--------|
         */
        private PointF[] GetFirstFigurePoints(Point centerPosition)
        {
            double angle = 2 * Math.PI / 5;
            return new PointF[]
            {
                new PointF(centerPosition.X + (float)(FigureSize / 2 * Math.Cos(0 * angle)), centerPosition.Y + (float)(FigureSize / 2 * Math.Sin(0 * angle))),
                new PointF(centerPosition.X + (float)(FigureSize / 2 * Math.Cos(1 * angle)), centerPosition.Y + (float)(FigureSize / 2 * Math.Sin(1 * angle))),
                new PointF(centerPosition.X + (float)(FigureSize / 2 * Math.Cos(2 * angle)), centerPosition.Y + (float)(FigureSize / 2 * Math.Sin(2 * angle))),
                new PointF(centerPosition.X + (float)(FigureSize / 2 * Math.Cos(3 * angle)), centerPosition.Y + (float)(FigureSize / 2 * Math.Sin(3 * angle))),
                new PointF(centerPosition.X + (float)(FigureSize / 2 * Math.Cos(4 * angle)), centerPosition.Y + (float)(FigureSize / 2 * Math.Sin(4 * angle)))
            };
        }



        // рисование фигуры в буфер
        private void WriteFigure(PointF[] points, Graphics gr, Pen pen)
        {
            for (int i = 0; i < points.Length; i++)
            {
                gr.DrawLine(pen, points[i], points[(i+1) % points.Length]);
            }
        }

        // задание начальных точек промежуточной фигуры
        private PointF[] GetPentagonVertexes(PointF[] fisrtFigurePoints)
        {
            return new PointF[] { fisrtFigurePoints[0], fisrtFigurePoints[1], fisrtFigurePoints[2], fisrtFigurePoints[3], fisrtFigurePoints[4]};
        }

        // вычисление сдвига координат
        private void CalculateOffset(PointF[] firstFigurePoints, PointF[] secondFigurePoints)
        {
            for (int i = 0; i < firstFigurePoints.Length; i++)
            {
                // обьеденение позиций точек при 6 -> 4
                // кочечная точка - первичная / шаги/2
                offsets[i, 0] = (double)(secondFigurePoints[(i + 1) % secondFigurePoints.Length].X - firstFigurePoints[i].X) /
                                (StepsCount/2);
                offsets[i, 1] = (double)(secondFigurePoints[(i + 1) % secondFigurePoints.Length].Y - firstFigurePoints[i].Y) /
                                (StepsCount/2);
            }
        }

        // обработка таймера
        private void Tick(object sender, EventArgs e)
        {
            stepNumber++;
            if (stepNumber == StepsCount)
            {
                timer1.Enabled = false;
            }
            else
            {
                DrawNextFigure();
            }
        }

        // ??????
        private void DrawNextFigure()
        {
            // рисовать ли шлейф (да - нет)
            if (tailCheckBox.Checked)
            {
                WriteFigure(currentPoints, graphics, secondPen);
            }
            if (figureCheckBox.Checked)
            {
                var positions = GetSourceAndTargetPosition();
                var initialFigure = GetFirstFigurePoints(positions.Item1);
                var targetFigure = GetSecondFigurePoints(positions.Item2);
                WriteFigure(initialFigure, graphics, mainPen);
                WriteFigure(targetFigure, graphics, mainPen);
            }
            // изменение этапа с центрального на конечный
            if (stepNumber == StepsCount/2)
            {
                var positions = GetSourceAndTargetPosition();
                CalculateOffset(currentPoints, GetSecondFigurePoints(positions.Item2));
            }
            SetNextPosition();
            WriteFigure(currentPoints, graphics, mainPen);
            canvasBox.Image = canvas;              // ???
        }

        // применить сдвиги координат
        private void SetNextPosition()
        {
            for (int j = 0; j < currentPoints.Length; j++)
            {
                currentPoints[j].X += (float) offsets[j, 0];
                currentPoints[j].Y += (float) offsets[j, 1];
            }
        }
    }
}
