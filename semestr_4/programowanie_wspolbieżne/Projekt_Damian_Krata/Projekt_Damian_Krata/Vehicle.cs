using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Projekt_Damian_Krata
{
    public class Vehicle
    {
        public int x;
        public int y;
        protected int width;
        protected int height;
        protected Brush brush;
        protected Random random;
        protected bool is_rotated = false;

        public Vehicle(int x, int y)
        {
            this.x = x;
            this.y = y;
            this.random = new Random();
        }


        public void rotate()
        {
            if(!is_rotated)
            {
                int temp = this.width;
                this.width = this.height;
                this.height = temp;
                is_rotated=true;
            }
        }

                
        public void draw_vehicle(Graphics g)
        {
            g.FillRectangle(this.brush, this.x, this.y, this.width, this.height);
        }
    }
}
