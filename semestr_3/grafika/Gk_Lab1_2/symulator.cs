//-----------------------------------------------//
//Program do symulowania efektów graficznych     //
//uzyskiwanych na ekranie urz¹dzenia rastrowego  //                 
//poprzez odpowiednie adresowanie pamiêci obrazu //
//                                               // 
//Do wykorzystania w ramach przedmiotu           //
//Grafika komputerowa                            //
//                                               // 
//Autor: Wojciech Sulej                          //
//Copyright: ITA WAT                             //
//Wersja: 1.10                                   //
//-----------------------------------------------//

using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Text;
using System.Windows.Forms;

namespace Graf_kom
{
    public partial class f_graf_kom : Form
    {
        readonly Bitmap m_obraz_w_pamieci;
        Bitmap m_ekran;

        int L;
        int K;

        int rasterX;
        int rasterY;
        
        int p;

        Color N;
        
        public f_graf_kom()
        {
            InitializeComponent();

            N = Color.Black;
            
            Bitmap im = new Bitmap("lew.bmp");

            m_obraz_w_pamieci = (Bitmap)im.Clone();

            L = m_obraz_w_pamieci.Height;
            K = m_obraz_w_pamieci.Width;

            m_ekran = (Bitmap)im.Clone();
        }

        private void MoveRaster()
        {
            if (rasterX == m_ekran.Width - 1)
            {
                rasterX = 0;
                if (rasterY == m_ekran.Height - 1)
                {                    
                    rasterY = 0;

                }
                else
                    rasterY++;
            }
            else
                rasterX++;
        }

        public void ReadPixel(int i, int j)
        {
            m_ekran.SetPixel(rasterX, rasterY, m_obraz_w_pamieci.GetPixel(i - 1, j - 1));
            
            MoveRaster();
        }

        public void ReadTlo(Color kolor_tla)
        {
            m_ekran.SetPixel(rasterX, rasterY, kolor_tla);

            MoveRaster();
        }

        public void SetBitMap(ref Bitmap image)
        {
            picbx_ekran.Image = image;
            picbx_ekran.Refresh();
            
            lb_nr_klatki.Text = "klatka = " + p;
        }
        
        private void Work()
        {
            if (rb_zsuwanie.Checked) Efekt1();
            if (rb_przewijanie.Checked) Efekt2();
            if (rb_rozsuwanie.Checked) Efekt3();
            
            p++;
                                
            SetBitMap(ref m_ekran);
        }

        private void b_load_Click(object sender, EventArgs e)
        {
            p = 0;
            progressBar1.Value = 0;

            rasterX = 0;
            rasterY = 0;

            picbx_pamiec_obrazu.Image = m_obraz_w_pamieci;

            lb_roz_obrazu.Text = m_obraz_w_pamieci.Height.ToString() + " x " + m_obraz_w_pamieci.Width.ToString();

            for (int j = 1; j <= L; j++)
                for (int i = 1; i <= K; i++)
                    ReadTlo(N);

            picbx_ekran.Image = m_ekran;

            b_load.Enabled = false;
            b_reset.Enabled = true;

            b_start.Enabled = true;
            b_stop.Enabled = false;
            b_kolejna_klatka.Enabled = true;

            b_zmien_obraz.Enabled = true;
        }
        
        private void b_reset_Click(object sender, EventArgs e)
        {
            progressBar1.Value = 0;
            picbx_pamiec_obrazu.Image = null;
            lb_roz_obrazu.Text = "0 x 0";
            
            picbx_ekran.Image = null;
            lb_nr_klatki.Text = "klatka = 0";

            b_load.Enabled = true;
            b_reset.Enabled = false;

            b_start.Enabled = false;
            b_stop.Enabled = false;
            b_kolejna_klatka.Enabled = false;

            b_zmien_obraz.Enabled = false;
        }

        private void timer_automat_Tick(object sender, EventArgs e)
        {
            Work();
        }

        private void b_start_Click(object sender, EventArgs e)
        {
            timer_automat.Enabled = true;
            
            b_start.Enabled = false;
            b_stop.Enabled = true;
            b_kolejna_klatka.Enabled = false;

            b_reset.Enabled = false;
        }

        private void b_stop_Click(object sender, EventArgs e)
        {
            timer_automat.Enabled = false;

            b_start.Enabled = true;
            b_stop.Enabled = false;
            b_kolejna_klatka.Enabled = true;

            b_reset.Enabled = true;
           
        }

        private void b_kolejna_klatka_Click(object sender, EventArgs e)
        {
            Work();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Zmien_obraz();            
        }

        private void f_graf_kom_Load(object sender, EventArgs e)
        {

        }

        private void rb_zsuwanie_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void rb_rozsuwanie_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void picbx_ekran_Click(object sender, EventArgs e)
        {

        }

        private void lb_roz_obrazu_Click(object sender, EventArgs e)
        {

        }

        private void picbx_pamiec_obrazu_Click(object sender, EventArgs e)
        {

        }

        private void progressBar1_Click(object sender, EventArgs e)
        {
         
        }

        private void lb_nr_klatki_Click(object sender, EventArgs e)
        {

        }

        private void rb_przewijanie_CheckedChanged(object sender, EventArgs e)
        {

        }

        private void radioButton1_CheckedChanged(object sender, EventArgs e)
        {

        }

        public int zmien_jasnosc(int y) 
        { 
            y = y + hScrollBar1.Value - 255; 
            if (y < 0) 
                return 0; 
            else if (y > 255) 
                return 255;
            else return y;
        }

        public void tonacja(int mode)
        {
        double jasnosc = 0;
        double kontrast = 0;
        int f;
        for (int j = 1; j <= L; j++)
        {
        for (int i = 1; i <= K; i++)
        {
        System.Drawing.Color pixel = m_ekran.GetPixel(i - 1, j - 1);
        if (mode == 0)
            f = ((max(pixel.R, pixel.G, pixel.B) + min(pixel.R, pixel.G, pixel.B)) / 2);
        else if (mode == 1)
            f = (max(pixel.R, pixel.G, pixel.B));
        else if (mode == 2)
            f = ((pixel.R + pixel.G + pixel.B) / 3);
        else f = (pixel.R + pixel.G + pixel.B);
        jasnosc = jasnosc + f;
        }
        }
        jasnosc = jasnosc / (L * K);

        for (int j = 1; j <= L; j++)
        {
            for (int i = 1; i <= K; i++)
            {
                System.Drawing.Color pixel = m_ekran.GetPixel(i - 1, j - 1);
                if (mode == 0)
                    f = ((max(pixel.R, pixel.G, pixel.B) + min(pixel.R, pixel.G, pixel.B)) / 2);
                else if (mode == 1)
                    f = (max(pixel.R, pixel.G, pixel.B));
                else if (mode == 2)
                    f = ((pixel.R + pixel.G + pixel.B) / 3);
                else f = (pixel.R + pixel.G + pixel.B);

                kontrast = kontrast + (f - jasnosc) * (f - jasnosc);
            }
        }
        kontrast = System.Math.Sqrt((double)kontrast / (double)(L * K));
        kontrast = kontrast * 100 / 300;
        jasnosc = jasnosc * 100 / 300;
        jasnoscLabel.Text = Convert.ToString(jasnosc);
        kontrastLabel.Text = Convert.ToString(kontrast);
        }

        public int max(int a, int b, int c) 
        { if (a >= b && a >= c) 
            return a; 
        else if (b >= a && b >= c) 
            return b; 
        else if (c >= b && c >= a) 
            return c; else return 0; 
        }

        public int min(int a, int b, int c) 
        {
        if (a <= b && a <= c) return a; 
        else if (b <= a && b <= c) return b;
        else if (c <= b && c <= a) return c;
        else return 0; 
        }

        private void hScrollBar1_Scroll(object sender, ScrollEventArgs e)
        {

        }

        private void scroll_update(object sender, EventArgs e)
        {
            if (!timer_automat.Enabled)
                Zmien_obraz();
        }

        private void button_update(object sender, EventArgs e)
        {
            if (!timer_automat.Enabled)
                Zmien_obraz();
            hScrollBar1.Value = 255;
        }
    }
}
