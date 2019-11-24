//-----------------------------------------------//
namespace Graf_kom
{
    public partial class f_graf_kom
    {

        //------------------
        //------------------
        public void Efekt1()
        {
            //efekt: przewijanie poziome obrazu w kierunku lewej strony ekranu

            if (p >= L) p = 0;
            progressBar1.Value = ((p+1) * 100) / L;
            for (int j = 1; j <= L; j++)
            {
                for (int i = 1 + p; i <= K; i++)
                    ReadPixel(i, j);
                for (int i = 1; i <= p; i++)
                    ReadPixel(i, j);
            }
        }
           
        //------------------
        //------------------
        public void Efekt2()
        {
            //efekt: przesuwanie pionowe obrazu w kierunku gornej krawedzi ekranu

            if (p >= L) p = 0;
            progressBar1.Value = ((p+1)*100)/L;
            for (int j = p+1; j <= L; j++)
                for (int i = 1 ; i <= K; i++)
                    ReadPixel(i, j);

            for (int j=1; j<=p;j++)
                for (int i = 1; i <= K; i++)
                    ReadTlo(N);
        }

        //------------------
        //------------------
        public void Efekt3()
        {
            //efekt: przesuwanie obrazu wzdluz przekatnej ekranu w kierunku dolnego prawego wierzcholka

            if (p >= L) p = 0;
            progressBar1.Value = ((p + 1) * 100) / L;
            for (int j = L - p; j < K; j++)
                for (int i = 1; i <= K; i++)
                    ReadTlo(N);

            for (int j = 1; j <= L - p; j++)
            {
                for (int i = 1; i <= p; i++)
                    ReadTlo(N);
                for (int i = 1; i <= K - p; i++)
                    ReadPixel(i, j);
            }
        }


        //------------------
        //------------------
        public void Zmien_obraz()
        {
            System.Drawing.Color pixel;
            if (radioButton1.Checked)
            {
            for (int j = 1; j <= L; j++)
                for (int i = 1; i <= K; i++)
                {
                    pixel = m_obraz_w_pamieci.GetPixel(i - 1, j - 1);

                    //--------------------------------------//
                    //miejsce na kod dokonuj¹cy zmianê obrazu
        
                    pixel = System.Drawing.Color.FromArgb(pixel.R, pixel.G, pixel.B);

                    //--------------------------------------//
                    
                    m_ekran.SetPixel(i - 1, j - 1, pixel);
                }

            SetBitMap(ref m_ekran);
            tonacja(3);
                }
            else if(radioButton2.Checked)
                {
                for (int j = 1; j <= L; j++)
                for (int i = 1; i <= K; i++)
                {
                pixel = m_obraz_w_pamieci.GetPixel(i - 1, j - 1);
                int jasnosc2 = (max(pixel.R,pixel.G,pixel.B)+min(pixel.R,pixel.G,pixel.B))/2;
                pixel = System.Drawing.Color.FromArgb(jasnosc2, jasnosc2, jasnosc2);
                m_ekran.SetPixel(i - 1, j - 1, pixel);
                }
                SetBitMap(ref m_ekran);
                tonacja(0);
                }
            else if (radioButton3.Checked)
                {
                for (int j = 1; j <= L; j++)
                for (int i = 1; i <= K; i++)
                {
                pixel = m_obraz_w_pamieci.GetPixel(i - 1, j - 1);
                int jasnosc2 = max(pixel.R, pixel.B, pixel.G);
                pixel = System.Drawing.Color.FromArgb(jasnosc2, jasnosc2, jasnosc2);
                m_ekran.SetPixel(i - 1, j - 1, pixel);
                }
                SetBitMap(ref m_ekran);
                tonacja(1);
                }
            else if (radioButton4.Checked)
                {
                for (int j = 1; j <= L; j++)
                for (int i = 1; i <= K; i++)
                {
                pixel = m_obraz_w_pamieci.GetPixel(i - 1, j - 1);
                int jasnosc2 = (pixel.R + pixel.G + pixel.B) / 3;
                pixel = System.Drawing.Color.FromArgb(jasnosc2, jasnosc2, jasnosc2);
                m_ekran.SetPixel(i - 1, j - 1, pixel);
                }
                SetBitMap(ref m_ekran);
                tonacja(2);
                }
         }
      }
}
