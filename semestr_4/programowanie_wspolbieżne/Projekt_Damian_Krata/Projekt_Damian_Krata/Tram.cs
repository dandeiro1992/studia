using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Projekt_Damian_Krata
{
    class Tram : Vehicle
    {
        public Tram(int x, int y)
            : base(x, y)
        {
            this.x = x;
            this.y = y;
            this.width = 25;
            this.height = 60;
            this.random = new Random();
            this.brush = new SolidBrush(Color.Black);
        }

        public void tram_drive()
        {
            this.y -= 10;
        }
    }
}