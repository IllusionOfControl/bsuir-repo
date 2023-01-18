namespace prakt_work_4
{
    partial class Form1
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
            this.bitmap = new System.Windows.Forms.PictureBox();
            this.goButton = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            ((System.ComponentModel.ISupportInitialize)(this.bitmap)).BeginInit();
            this.SuspendLayout();
            // 
            // bitmap
            // 
            this.bitmap.Anchor = ((System.Windows.Forms.AnchorStyles)((((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Bottom) 
            | System.Windows.Forms.AnchorStyles.Left) 
            | System.Windows.Forms.AnchorStyles.Right)));
            this.bitmap.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.bitmap.Location = new System.Drawing.Point(12, 12);
            this.bitmap.Name = "bitmap";
            this.bitmap.Size = new System.Drawing.Size(970, 406);
            this.bitmap.TabIndex = 0;
            this.bitmap.TabStop = false;
            this.bitmap.MouseDown += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseDown);
            this.bitmap.MouseMove += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseMove);
            this.bitmap.MouseUp += new System.Windows.Forms.MouseEventHandler(this.pictureBox1_MouseUp);
            // 
            // goButton
            // 
            this.goButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.goButton.Location = new System.Drawing.Point(878, 424);
            this.goButton.Name = "goButton";
            this.goButton.Size = new System.Drawing.Size(104, 50);
            this.goButton.TabIndex = 1;
            this.goButton.Text = "Старт!";
            this.goButton.UseVisualStyleBackColor = true;
            this.goButton.Click += new System.EventHandler(this.GoButton);
            // 
            // timer1
            // 
            this.timer1.Interval = 10;
            this.timer1.Tick += new System.EventHandler(this.Tick);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(994, 486);
            this.Controls.Add(this.goButton);
            this.Controls.Add(this.bitmap);
            this.Name = "Form1";
            this.Text = "prakt_work_4_Skorokhod";
            ((System.ComponentModel.ISupportInitialize)(this.bitmap)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox bitmap;
        private System.Windows.Forms.Button goButton;
        private System.Windows.Forms.Timer timer1;
    }
}

