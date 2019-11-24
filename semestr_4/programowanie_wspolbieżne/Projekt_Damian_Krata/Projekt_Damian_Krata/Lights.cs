using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;
using System.Threading.Tasks;

namespace Projekt_Damian_Krata
{
    class Lights
    {
        private Brush brush;
        public int id;
        public int x;
        public int y;
        public int radius;

        private Brush redBrush = new SolidBrush(Color.FromArgb(255, 255, 0, 0));
        private Brush greenBrush = new SolidBrush(Color.FromArgb(255, 0, 255, 0));

        public Lights(int x, int y, int id)
        {
            this.x = x;
            this.y = y;
            this.radius = 25;
            this.id = id;
            this.brush = redBrush;
        }

        public void change_color()
        {
           if(this.brush == redBrush)
           {
               this.brush = greenBrush;
           }
           else
           {
               this.brush = redBrush;
           }
        }

        public bool is_green()
        {
            return this.brush == greenBrush;
        }

        public void set_red()
        {
            this.brush = redBrush;
        }

        public void set_green()
        {
            this.brush = greenBrush;
        }

        public void draw_light(Graphics g)
        {
            g.FillEllipse(this.brush, this.x, this.y, this.radius, this.radius);
        }
    }


}
