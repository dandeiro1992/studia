using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Projekt_Damian_Krata
{
    public class Car : Vehicle
    {
        public Paths path;

        public Car(int x, int y, Paths path)
            : base(x, y)
        {
            this.x = x;
            this.y = y;
            this.width = 25;
            this.height = 35;
            this.path = path;
            this.random = new Random();
            this.brush = new SolidBrush(Color.FromArgb(255, random.Next(0, 255), random.Next(0, 255), random.Next(0, 255)));
        }

        public void move(int x, int y)
        {
            this.x += x;
            this.y += y;
        }
    }
}
