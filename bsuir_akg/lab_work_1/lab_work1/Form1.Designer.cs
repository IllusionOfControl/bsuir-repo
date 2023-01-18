namespace LabWork_1
{
    partial class MainForm
    {
        /// <summary>
        /// Требуется переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Обязательный метод для поддержки конструктора - не изменяйте
        /// содержимое данного метода при помощи редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.canvasBox = new System.Windows.Forms.PictureBox();
            this.goButton = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.tailCheckBox = new System.Windows.Forms.CheckBox();
            this.figureCheckBox = new System.Windows.Forms.CheckBox();
            ((System.ComponentModel.ISupportInitialize)(this.canvasBox)).BeginInit();
            this.SuspendLayout();
            // 
            // canvasBox
            // 
            this.canvasBox.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.canvasBox.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.canvasBox.Location = new System.Drawing.Point(12, 12);
            this.canvasBox.Name = "canvasBox";
            this.canvasBox.Size = new System.Drawing.Size(970, 417);
            this.canvasBox.TabIndex = 0;
            this.canvasBox.TabStop = false;
            // 
            // goButton
            // 
            this.goButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.goButton.Location = new System.Drawing.Point(907, 435);
            this.goButton.Name = "goButton";
            this.goButton.Size = new System.Drawing.Size(75, 40);
            this.goButton.TabIndex = 1;
            this.goButton.Text = "Старт!";
            this.goButton.UseVisualStyleBackColor = true;
            this.goButton.Click += new System.EventHandler(this.goButton_Click);
            // 
            // timer1
            // 
            this.timer1.Interval = 200;
            this.timer1.Tick += new System.EventHandler(this.Tick);
            // 
            // tailCheckBox
            // 
            this.tailCheckBox.AutoSize = true;
            this.tailCheckBox.Location = new System.Drawing.Point(12, 458);
            this.tailCheckBox.Name = "tailCheckBox";
            this.tailCheckBox.Size = new System.Drawing.Size(150, 17);
            this.tailCheckBox.TabIndex = 4;
            this.tailCheckBox.Text = "Промежуточные фигуры";
            this.tailCheckBox.UseVisualStyleBackColor = true;
            // 
            // figureCheckBox
            // 
            this.figureCheckBox.AutoSize = true;
            this.figureCheckBox.Location = new System.Drawing.Point(12, 435);
            this.figureCheckBox.Name = "figureCheckBox";
            this.figureCheckBox.Size = new System.Drawing.Size(181, 17);
            this.figureCheckBox.TabIndex = 5;
            this.figureCheckBox.Text = "Начальная и конечная фигуры";
            this.figureCheckBox.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(994, 487);
            this.Controls.Add(this.figureCheckBox);
            this.Controls.Add(this.tailCheckBox);
            this.Controls.Add(this.goButton);
            this.Controls.Add(this.canvasBox);
            this.Name = "MainForm";
            this.Text = "Lab_work_1 Skorokhod";
            ((System.ComponentModel.ISupportInitialize)(this.canvasBox)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox canvasBox;
        private System.Windows.Forms.Button goButton;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.CheckBox tailCheckBox;
        private System.Windows.Forms.CheckBox figureCheckBox;
    }
}

