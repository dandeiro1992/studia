using System.Threading;
using System.Diagnostics;
namespace Graf_kom
{
    partial class f_graf_kom
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
            Process.GetCurrentProcess().Kill();
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.picbx_ekran = new System.Windows.Forms.PictureBox();
            this.picbx_pamiec_obrazu = new System.Windows.Forms.PictureBox();
            this.lb_obraz_w_pamieci_opis = new System.Windows.Forms.Label();
            this.lb_obraz_na_ekranie_opis = new System.Windows.Forms.Label();
            this.b_load = new System.Windows.Forms.Button();
            this.lb_roz_obrazu_opis = new System.Windows.Forms.Label();
            this.lb_roz_obrazu = new System.Windows.Forms.Label();
            this.b_kolejna_klatka = new System.Windows.Forms.Button();
            this.b_reset = new System.Windows.Forms.Button();
            this.lb_nr_klatki = new System.Windows.Forms.Label();
            this.b_start = new System.Windows.Forms.Button();
            this.b_stop = new System.Windows.Forms.Button();
            this.rb_zsuwanie = new System.Windows.Forms.RadioButton();
            this.rb_przewijanie = new System.Windows.Forms.RadioButton();
            this.rb_rozsuwanie = new System.Windows.Forms.RadioButton();
            this.lb_efekty_opis = new System.Windows.Forms.Label();
            this.lb_wykonywanie_opis = new System.Windows.Forms.Label();
            this.lb_samoczynne_opis = new System.Windows.Forms.Label();
            this.lb_po_klatce_opis = new System.Windows.Forms.Label();
            this.timer_automat = new System.Windows.Forms.Timer(this.components);
            this.b_zmien_obraz = new System.Windows.Forms.Button();
            this.richTextBox1 = new System.Windows.Forms.RichTextBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.hScrollBar1 = new System.Windows.Forms.HScrollBar();
            this.radioButton1 = new System.Windows.Forms.RadioButton();
            this.radioButton2 = new System.Windows.Forms.RadioButton();
            this.radioButton3 = new System.Windows.Forms.RadioButton();
            this.radioButton4 = new System.Windows.Forms.RadioButton();
            this.jasnoscLabel = new System.Windows.Forms.Label();
            this.kontrastLabel = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.picbx_ekran)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picbx_pamiec_obrazu)).BeginInit();
            this.SuspendLayout();
            // 
            // picbx_ekran
            // 
            this.picbx_ekran.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.picbx_ekran.Location = new System.Drawing.Point(566, 56);
            this.picbx_ekran.Name = "picbx_ekran";
            this.picbx_ekran.Size = new System.Drawing.Size(300, 300);
            this.picbx_ekran.TabIndex = 0;
            this.picbx_ekran.TabStop = false;
            this.picbx_ekran.Click += new System.EventHandler(this.picbx_ekran_Click);
            // 
            // picbx_pamiec_obrazu
            // 
            this.picbx_pamiec_obrazu.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.picbx_pamiec_obrazu.Location = new System.Drawing.Point(60, 56);
            this.picbx_pamiec_obrazu.Name = "picbx_pamiec_obrazu";
            this.picbx_pamiec_obrazu.Size = new System.Drawing.Size(300, 300);
            this.picbx_pamiec_obrazu.TabIndex = 2;
            this.picbx_pamiec_obrazu.TabStop = false;
            this.picbx_pamiec_obrazu.Click += new System.EventHandler(this.picbx_pamiec_obrazu_Click);
            // 
            // lb_obraz_w_pamieci_opis
            // 
            this.lb_obraz_w_pamieci_opis.AutoSize = true;
            this.lb_obraz_w_pamieci_opis.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lb_obraz_w_pamieci_opis.Location = new System.Drawing.Point(182, 24);
            this.lb_obraz_w_pamieci_opis.Name = "lb_obraz_w_pamieci_opis";
            this.lb_obraz_w_pamieci_opis.Size = new System.Drawing.Size(107, 16);
            this.lb_obraz_w_pamieci_opis.TabIndex = 3;
            this.lb_obraz_w_pamieci_opis.Text = "Obraz w pamiêci";
            // 
            // lb_obraz_na_ekranie_opis
            // 
            this.lb_obraz_na_ekranie_opis.AutoSize = true;
            this.lb_obraz_na_ekranie_opis.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lb_obraz_na_ekranie_opis.Location = new System.Drawing.Point(680, 24);
            this.lb_obraz_na_ekranie_opis.Name = "lb_obraz_na_ekranie_opis";
            this.lb_obraz_na_ekranie_opis.Size = new System.Drawing.Size(110, 16);
            this.lb_obraz_na_ekranie_opis.TabIndex = 4;
            this.lb_obraz_na_ekranie_opis.Text = "Obraz na ekranie";
            // 
            // b_load
            // 
            this.b_load.Location = new System.Drawing.Point(421, 73);
            this.b_load.Name = "b_load";
            this.b_load.Size = new System.Drawing.Size(75, 23);
            this.b_load.TabIndex = 5;
            this.b_load.Text = "LOAD";
            this.b_load.UseVisualStyleBackColor = true;
            this.b_load.Click += new System.EventHandler(this.b_load_Click);
            // 
            // lb_roz_obrazu_opis
            // 
            this.lb_roz_obrazu_opis.AutoSize = true;
            this.lb_roz_obrazu_opis.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lb_roz_obrazu_opis.Location = new System.Drawing.Point(295, 24);
            this.lb_roz_obrazu_opis.Name = "lb_roz_obrazu_opis";
            this.lb_roz_obrazu_opis.Size = new System.Drawing.Size(45, 16);
            this.lb_roz_obrazu_opis.TabIndex = 6;
            this.lb_roz_obrazu_opis.Text = "L x K =";
            // 
            // lb_roz_obrazu
            // 
            this.lb_roz_obrazu.AutoSize = true;
            this.lb_roz_obrazu.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lb_roz_obrazu.Location = new System.Drawing.Point(336, 24);
            this.lb_roz_obrazu.Name = "lb_roz_obrazu";
            this.lb_roz_obrazu.Size = new System.Drawing.Size(34, 16);
            this.lb_roz_obrazu.TabIndex = 7;
            this.lb_roz_obrazu.Text = "0 x 0";
            this.lb_roz_obrazu.Click += new System.EventHandler(this.lb_roz_obrazu_Click);
            // 
            // b_kolejna_klatka
            // 
            this.b_kolejna_klatka.Enabled = false;
            this.b_kolejna_klatka.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.b_kolejna_klatka.Location = new System.Drawing.Point(975, 331);
            this.b_kolejna_klatka.Name = "b_kolejna_klatka";
            this.b_kolejna_klatka.Size = new System.Drawing.Size(108, 23);
            this.b_kolejna_klatka.TabIndex = 10;
            this.b_kolejna_klatka.Text = "Kolejna klatka";
            this.b_kolejna_klatka.UseVisualStyleBackColor = true;
            this.b_kolejna_klatka.Click += new System.EventHandler(this.b_kolejna_klatka_Click);
            // 
            // b_reset
            // 
            this.b_reset.Enabled = false;
            this.b_reset.Location = new System.Drawing.Point(421, 263);
            this.b_reset.Name = "b_reset";
            this.b_reset.Size = new System.Drawing.Size(75, 23);
            this.b_reset.TabIndex = 17;
            this.b_reset.Text = "RESET";
            this.b_reset.UseVisualStyleBackColor = true;
            this.b_reset.Click += new System.EventHandler(this.b_reset_Click);
            // 
            // lb_nr_klatki
            // 
            this.lb_nr_klatki.AutoSize = true;
            this.lb_nr_klatki.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lb_nr_klatki.Location = new System.Drawing.Point(981, 371);
            this.lb_nr_klatki.Name = "lb_nr_klatki";
            this.lb_nr_klatki.Size = new System.Drawing.Size(64, 16);
            this.lb_nr_klatki.TabIndex = 20;
            this.lb_nr_klatki.Text = "klatka = 0";
            this.lb_nr_klatki.Click += new System.EventHandler(this.lb_nr_klatki_Click);
            // 
            // b_start
            // 
            this.b_start.Enabled = false;
            this.b_start.Location = new System.Drawing.Point(975, 263);
            this.b_start.Name = "b_start";
            this.b_start.Size = new System.Drawing.Size(51, 23);
            this.b_start.TabIndex = 21;
            this.b_start.Text = "START";
            this.b_start.UseVisualStyleBackColor = true;
            this.b_start.Click += new System.EventHandler(this.b_start_Click);
            // 
            // b_stop
            // 
            this.b_stop.Enabled = false;
            this.b_stop.Location = new System.Drawing.Point(1032, 263);
            this.b_stop.Name = "b_stop";
            this.b_stop.Size = new System.Drawing.Size(51, 23);
            this.b_stop.TabIndex = 22;
            this.b_stop.Text = "STOP";
            this.b_stop.UseVisualStyleBackColor = true;
            this.b_stop.Click += new System.EventHandler(this.b_stop_Click);
            // 
            // rb_zsuwanie
            // 
            this.rb_zsuwanie.AutoSize = true;
            this.rb_zsuwanie.Checked = true;
            this.rb_zsuwanie.Location = new System.Drawing.Point(970, 117);
            this.rb_zsuwanie.Name = "rb_zsuwanie";
            this.rb_zsuwanie.Size = new System.Drawing.Size(194, 17);
            this.rb_zsuwanie.TabIndex = 23;
            this.rb_zsuwanie.TabStop = true;
            this.rb_zsuwanie.Text = "efekt przewijania poziomego w lewo";
            this.rb_zsuwanie.UseVisualStyleBackColor = true;
            this.rb_zsuwanie.CheckedChanged += new System.EventHandler(this.rb_zsuwanie_CheckedChanged);
            // 
            // rb_przewijanie
            // 
            this.rb_przewijanie.AutoSize = true;
            this.rb_przewijanie.Location = new System.Drawing.Point(970, 140);
            this.rb_przewijanie.Name = "rb_przewijanie";
            this.rb_przewijanie.Size = new System.Drawing.Size(166, 17);
            this.rb_przewijanie.TabIndex = 24;
            this.rb_przewijanie.Text = "efekt przesuwania pionowego";
            this.rb_przewijanie.UseVisualStyleBackColor = true;
            this.rb_przewijanie.CheckedChanged += new System.EventHandler(this.rb_przewijanie_CheckedChanged);
            // 
            // rb_rozsuwanie
            // 
            this.rb_rozsuwanie.AutoSize = true;
            this.rb_rozsuwanie.Location = new System.Drawing.Point(970, 163);
            this.rb_rozsuwanie.Name = "rb_rozsuwanie";
            this.rb_rozsuwanie.Size = new System.Drawing.Size(198, 17);
            this.rb_rozsuwanie.TabIndex = 25;
            this.rb_rozsuwanie.Text = "efekt przesuwania wzdluz przekatnej";
            this.rb_rozsuwanie.UseVisualStyleBackColor = true;
            this.rb_rozsuwanie.CheckedChanged += new System.EventHandler(this.rb_rozsuwanie_CheckedChanged);
            // 
            // lb_efekty_opis
            // 
            this.lb_efekty_opis.AutoSize = true;
            this.lb_efekty_opis.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lb_efekty_opis.Location = new System.Drawing.Point(981, 42);
            this.lb_efekty_opis.Name = "lb_efekty_opis";
            this.lb_efekty_opis.Size = new System.Drawing.Size(45, 16);
            this.lb_efekty_opis.TabIndex = 26;
            this.lb_efekty_opis.Text = "Efekty";
            // 
            // lb_wykonywanie_opis
            // 
            this.lb_wykonywanie_opis.AutoSize = true;
            this.lb_wykonywanie_opis.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lb_wykonywanie_opis.Location = new System.Drawing.Point(972, 200);
            this.lb_wykonywanie_opis.Name = "lb_wykonywanie_opis";
            this.lb_wykonywanie_opis.Size = new System.Drawing.Size(95, 16);
            this.lb_wykonywanie_opis.TabIndex = 27;
            this.lb_wykonywanie_opis.Text = "Wykonywanie:";
            // 
            // lb_samoczynne_opis
            // 
            this.lb_samoczynne_opis.AutoSize = true;
            this.lb_samoczynne_opis.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lb_samoczynne_opis.Location = new System.Drawing.Point(972, 227);
            this.lb_samoczynne_opis.Name = "lb_samoczynne_opis";
            this.lb_samoczynne_opis.Size = new System.Drawing.Size(84, 16);
            this.lb_samoczynne_opis.TabIndex = 28;
            this.lb_samoczynne_opis.Text = "samoczynne";
            // 
            // lb_po_klatce_opis
            // 
            this.lb_po_klatce_opis.AutoSize = true;
            this.lb_po_klatce_opis.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.lb_po_klatce_opis.Location = new System.Drawing.Point(972, 298);
            this.lb_po_klatce_opis.Name = "lb_po_klatce_opis";
            this.lb_po_klatce_opis.Size = new System.Drawing.Size(103, 16);
            this.lb_po_klatce_opis.TabIndex = 29;
            this.lb_po_klatce_opis.Text = "po jednej klatce";
            // 
            // timer_automat
            // 
            this.timer_automat.Tick += new System.EventHandler(this.timer_automat_Tick);
            // 
            // b_zmien_obraz
            // 
            this.b_zmien_obraz.Enabled = false;
            this.b_zmien_obraz.Font = new System.Drawing.Font("Microsoft Sans Serif", 9F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.b_zmien_obraz.Location = new System.Drawing.Point(975, 405);
            this.b_zmien_obraz.Name = "b_zmien_obraz";
            this.b_zmien_obraz.Size = new System.Drawing.Size(108, 32);
            this.b_zmien_obraz.TabIndex = 30;
            this.b_zmien_obraz.Text = "Zmieñ obraz";
            this.b_zmien_obraz.UseVisualStyleBackColor = true;
            this.b_zmien_obraz.Click += new System.EventHandler(this.button1_Click);
            // 
            // richTextBox1
            // 
            this.richTextBox1.Location = new System.Drawing.Point(406, 175);
            this.richTextBox1.Name = "richTextBox1";
            this.richTextBox1.Size = new System.Drawing.Size(100, 42);
            this.richTextBox1.TabIndex = 31;
            this.richTextBox1.Text = "     Damian Krata  I4X3S1 22.10.15";
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(46, 376);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(397, 36);
            this.progressBar1.Step = 1;
            this.progressBar1.TabIndex = 32;
            this.progressBar1.Click += new System.EventHandler(this.progressBar1_Click);
            // 
            // hScrollBar1
            // 
            this.hScrollBar1.Location = new System.Drawing.Point(73, 446);
            this.hScrollBar1.Name = "hScrollBar1";
            this.hScrollBar1.Size = new System.Drawing.Size(370, 28);
            this.hScrollBar1.TabIndex = 33;
            this.hScrollBar1.Scroll += new System.Windows.Forms.ScrollEventHandler(this.hScrollBar1_Scroll);
            // 
            // radioButton1
            // 
            this.radioButton1.AutoSize = true;
            this.radioButton1.Location = new System.Drawing.Point(527, 385);
            this.radioButton1.Name = "radioButton1";
            this.radioButton1.Size = new System.Drawing.Size(48, 17);
            this.radioButton1.TabIndex = 34;
            this.radioButton1.TabStop = true;
            this.radioButton1.Text = "RGB";
            this.radioButton1.UseVisualStyleBackColor = true;
            this.radioButton1.CheckedChanged += new System.EventHandler(this.radioButton1_CheckedChanged);
            // 
            // radioButton2
            // 
            this.radioButton2.AutoSize = true;
            this.radioButton2.Location = new System.Drawing.Point(527, 419);
            this.radioButton2.Name = "radioButton2";
            this.radioButton2.Size = new System.Drawing.Size(46, 17);
            this.radioButton2.TabIndex = 35;
            this.radioButton2.TabStop = true;
            this.radioButton2.Text = "HLS";
            this.radioButton2.UseVisualStyleBackColor = true;
            // 
            // radioButton3
            // 
            this.radioButton3.AutoSize = true;
            this.radioButton3.Location = new System.Drawing.Point(527, 457);
            this.radioButton3.Name = "radioButton3";
            this.radioButton3.Size = new System.Drawing.Size(60, 17);
            this.radioButton3.TabIndex = 36;
            this.radioButton3.TabStop = true;
            this.radioButton3.Text = "HSV(B)";
            this.radioButton3.UseVisualStyleBackColor = true;
            // 
            // radioButton4
            // 
            this.radioButton4.AutoSize = true;
            this.radioButton4.Location = new System.Drawing.Point(527, 491);
            this.radioButton4.Name = "radioButton4";
            this.radioButton4.Size = new System.Drawing.Size(47, 17);
            this.radioButton4.TabIndex = 37;
            this.radioButton4.TabStop = true;
            this.radioButton4.Text = "AVG";
            this.radioButton4.UseVisualStyleBackColor = true;
            // 
            // jasnoscLabel
            // 
            this.jasnoscLabel.AutoSize = true;
            this.jasnoscLabel.Location = new System.Drawing.Point(755, 530);
            this.jasnoscLabel.Name = "jasnoscLabel";
            this.jasnoscLabel.Size = new System.Drawing.Size(13, 13);
            this.jasnoscLabel.TabIndex = 38;
            this.jasnoscLabel.Text = "0";
            // 
            // kontrastLabel
            // 
            this.kontrastLabel.AutoSize = true;
            this.kontrastLabel.Location = new System.Drawing.Point(755, 564);
            this.kontrastLabel.Name = "kontrastLabel";
            this.kontrastLabel.Size = new System.Drawing.Size(13, 13);
            this.kontrastLabel.TabIndex = 39;
            this.kontrastLabel.Text = "0";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(540, 530);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(46, 13);
            this.label3.TabIndex = 40;
            this.label3.Text = "Jasnoœæ";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(543, 563);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(46, 13);
            this.label4.TabIndex = 41;
            this.label4.Text = "Kontrast";
            // 
            // f_graf_kom
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1279, 610);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.kontrastLabel);
            this.Controls.Add(this.jasnoscLabel);
            this.Controls.Add(this.radioButton4);
            this.Controls.Add(this.radioButton3);
            this.Controls.Add(this.radioButton2);
            this.Controls.Add(this.radioButton1);
            this.Controls.Add(this.hScrollBar1);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.richTextBox1);
            this.Controls.Add(this.b_zmien_obraz);
            this.Controls.Add(this.lb_po_klatce_opis);
            this.Controls.Add(this.lb_samoczynne_opis);
            this.Controls.Add(this.lb_wykonywanie_opis);
            this.Controls.Add(this.lb_efekty_opis);
            this.Controls.Add(this.rb_rozsuwanie);
            this.Controls.Add(this.rb_przewijanie);
            this.Controls.Add(this.rb_zsuwanie);
            this.Controls.Add(this.b_stop);
            this.Controls.Add(this.b_start);
            this.Controls.Add(this.lb_nr_klatki);
            this.Controls.Add(this.b_reset);
            this.Controls.Add(this.b_kolejna_klatka);
            this.Controls.Add(this.lb_roz_obrazu);
            this.Controls.Add(this.lb_roz_obrazu_opis);
            this.Controls.Add(this.b_load);
            this.Controls.Add(this.lb_obraz_na_ekranie_opis);
            this.Controls.Add(this.lb_obraz_w_pamieci_opis);
            this.Controls.Add(this.picbx_pamiec_obrazu);
            this.Controls.Add(this.picbx_ekran);
            this.Location = new System.Drawing.Point(200, 100);
            this.MaximizeBox = false;
            this.Name = "f_graf_kom";
            this.StartPosition = System.Windows.Forms.FormStartPosition.Manual;
            this.Text = "Kontrast";
            this.Load += new System.EventHandler(this.f_graf_kom_Load);
            ((System.ComponentModel.ISupportInitialize)(this.picbx_ekran)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picbx_pamiec_obrazu)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox picbx_ekran;
        private System.Windows.Forms.PictureBox picbx_pamiec_obrazu;
        private System.Windows.Forms.Label lb_obraz_w_pamieci_opis;
        private System.Windows.Forms.Label lb_obraz_na_ekranie_opis;
        private System.Windows.Forms.Button b_load;
        private System.Windows.Forms.Label lb_roz_obrazu_opis;
        private System.Windows.Forms.Label lb_roz_obrazu;
        private System.Windows.Forms.Button b_kolejna_klatka;
        private System.Windows.Forms.Button b_reset;
        private System.Windows.Forms.Label lb_nr_klatki;
        private System.Windows.Forms.Button b_start;
        private System.Windows.Forms.Button b_stop;
        private System.Windows.Forms.RadioButton rb_zsuwanie;
        private System.Windows.Forms.RadioButton rb_przewijanie;
        private System.Windows.Forms.RadioButton rb_rozsuwanie;
        private System.Windows.Forms.Label lb_efekty_opis;
        private System.Windows.Forms.Label lb_wykonywanie_opis;
        private System.Windows.Forms.Label lb_samoczynne_opis;
        private System.Windows.Forms.Label lb_po_klatce_opis;
        private System.Windows.Forms.Timer timer_automat;
        private System.Windows.Forms.Button b_zmien_obraz;
        private System.Windows.Forms.RichTextBox richTextBox1;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.HScrollBar hScrollBar1;
        private System.Windows.Forms.RadioButton radioButton1;
        private System.Windows.Forms.RadioButton radioButton2;
        private System.Windows.Forms.RadioButton radioButton3;
        private System.Windows.Forms.RadioButton radioButton4;
        private System.Windows.Forms.Label jasnoscLabel;
        private System.Windows.Forms.Label kontrastLabel;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label4;

    }
}

