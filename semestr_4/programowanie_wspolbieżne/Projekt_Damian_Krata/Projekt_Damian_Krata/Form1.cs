using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Timers;
using System.Threading;

namespace Projekt_Damian_Krata
{
    public partial class Form1 : Form
    {
        Semaphore carList_access = new Semaphore(1, 1);
        Task adding;
        Task moving;
        int counter = 2;
        List<Car> carList = new List<Car>();
        List<Lights> lightList = new List<Lights>();
        List<Tram> tramList = new List<Tram>();
        Random rdm = new Random();
        private double sleepTime = 333.3;
        Dictionary<Paths, Point> startPathPointDictionary = new Dictionary<Paths, Point>();
        // Dictionary<int, List<Paths>> lightPathDictionary = new Dictionary<int, List<Paths>>();
        Dictionary<Paths, int> lightPathDictionary = new Dictionary<Paths, int>();

        public Form1()
        {
            InitializeComponent();
            //carList.Add(new Car(460, 720, Paths.down_to_left));
            //carList.Add(new Car(460, 760, Paths.down_to_left));
            carList.Add(new Car(310, 10, Paths.up_to_left));
            carList.Add(new Car(360, 10, Paths.up_to_down));
            tramList.Add(new Tram(662, 760));
            lightList.Add(new Lights(360, 435, 3));//0
            lightList.Add(new Lights(360, 385, 3));//1
            lightList.Add(new Lights(360, 335, 2));//2
            lightList.Add(new Lights(310, 335, 2));//3
            lightList.Add(new Lights(410, 435, 1));//4
            lightList.Add(new Lights(460, 435, 2));//5
            lightList.Add(new Lights(460, 335, 1));//6
            lightList.Add(new Lights(710, 335, 4));//7
            lightList.Add(new Lights(610, 385, 4));//8

            initGreenLight();
            System.Timers.Timer timer_change_light = new System.Timers.Timer(sleepTime * 6);
            timer_change_light.Start();
            System.Timers.Timer timer_move_vehicles = new System.Timers.Timer(sleepTime / 10);
            timer_move_vehicles.Start();
            // System.Timers.Timer timer_add = new System.Timers.Timer(sleepTime * 3);
            // timer_add.Start();
            timer_change_light.Elapsed += new ElapsedEventHandler(change_lights);
            timer_move_vehicles.Elapsed += new ElapsedEventHandler(drive_vehicles);
            //   timer_add.Elapsed += new ElapsedEventHandler(modify_list);


            startPathPointDictionary.Add(Paths.up_to_down, new Point(360, 10));
            startPathPointDictionary.Add(Paths.up_to_left, new Point(310, 10));
            startPathPointDictionary.Add(Paths.left_to_up, new Point(10, 385));
            startPathPointDictionary.Add(Paths.left_to_down, new Point(10, 435));
            startPathPointDictionary.Add(Paths.down_to_left, new Point(410, 760));
            startPathPointDictionary.Add(Paths.down_to_up, new Point(460, 760));
            startPathPointDictionary.Add(Paths.down_to_right, new Point(460, 760));
            //startPathPointDictionary.Add(Paths.right_to_down, new Point(760, 335));
            //startPathPointDictionary.Add(Paths.right_to_left, new Point(760, 335));
            startPathPointDictionary.Add(Paths.right_to_up, new Point(760, 335));

            lightPathDictionary.Add(Paths.up_to_down, 2);
            lightPathDictionary.Add(Paths.up_to_left, 2);
            lightPathDictionary.Add(Paths.left_to_up, 3);
            lightPathDictionary.Add(Paths.left_to_down, 3);
            lightPathDictionary.Add(Paths.down_to_left, 1);
            lightPathDictionary.Add(Paths.down_to_up, 2);
            lightPathDictionary.Add(Paths.down_to_right, 2);
            //lightPathDictionary.Add(Paths.right_to_down, 1);
            //lightPathDictionary.Add(Paths.right_to_left, 1);
            lightPathDictionary.Add(Paths.right_to_up, 1);
            adding = new Task(modify_list);
            moving = new Task(car_drive);
            adding.Start();
            moving.Start();
            //lightPathDictionary.Add(0,new List<Paths>(){ Paths.left_to_down});
            //lightPathDictionary.Add(1, new List<Paths>() { Paths.left_to_up});
            //lightPathDictionary.Add(2, new List<Paths>() { Paths.up_to_down});
            //lightPathDictionary.Add(3, new List<Paths>() { Paths.up_to_left });
            //lightPathDictionary.Add(4, new List<Paths>() { Paths.down_to_left});
            //lightPathDictionary.Add(5, new List<Paths>() { Paths.down_to_up,Paths.down_to_right });
            //lightPathDictionary.Add(6, new List<Paths>() { Paths.right_to_up, Paths.right_to_down, Paths.right_to_left});

        }

        public void modify_list()
        {
            while (true)
            {
                addCar();
                Thread.Sleep(1000);
                removeOutputCars();
                Thread.Sleep(1000);
            }
        }

        private void addCar()
        {
            carList_access.WaitOne();
            var counter = 0;
            var path = getRandomPath();
            var startPoint = startPathPointDictionary
                .Where(x => x.Key == path)
                .Select(x => x.Value).First();
            carList.ForEach(car =>
            {
                switch (path)
                {
                    case Paths.up_to_left:
                        if (car.y <= startPoint.X)
                            counter++;
                        break;
                }
            });
            carList.Add(new Car(startPoint.X, startPoint.Y - (35 * counter), path));
            carList_access.Release();
        }
      
        private Paths getRandomPath()
        {
            rdm = new Random();
            var values = Enum.GetValues(typeof(Paths));
            return (Paths)values.GetValue(rdm.Next(values.Length));
        }

        private void removeOutputCars()
        {
            carList_access.WaitOne();
            carList = carList.Where(car => Math.Abs(car.x) < 1200 || Math.Abs(car.y) < 1200).ToList();
            carList_access.Release();
        }

        private void Form1_Load(object sender, EventArgs e)
        {

        }

        public void car_drive()
        {

            carList_access.WaitOne();
            carList.ForEach(car =>
            {
                switch (car.path)
                {
                    case Paths.up_to_down:
                        path_up_to_down(car);
                        break;
                    case Paths.up_to_left:
                        path_up_to_left(car);
                        break;
                    case Paths.left_to_up:
                        path_left_to_up(car);
                        break;
                    case Paths.left_to_down:
                        path_left_to_down(car);
                        break;
                    case Paths.down_to_left:
                        path_down_to_left(car);
                        break;
                    case Paths.down_to_up:
                        path_down_to_up(car);
                        break;
                    case Paths.right_to_up:
                        path_right_to_up(car);
                        break;
                    default:
                        break;

                }

            });
            Thread.Sleep(20);
            carList_access.Release();
        }

        public void drive_vehicles(object source, ElapsedEventArgs e)
        {
            car_drive();
            tram_drive();          
            this.Invalidate();
        }

        private void tram_drive()
        {
            tramList.ForEach(tram =>
            {
                tram.tram_drive();

            });
            tram_lights();
            new_tram();
        }

        public void initGreenLight()
        {
            lightList.Where(light => light.id == 1 || light.id == 4).ToList().ForEach(light =>
            {
                light.set_green();
            });
        }

        public void Jack(int i)
        {
            lightList.Where(light => light.id < 4).ToList().ForEach(light =>
            {
                if (light.id == i)
                    light.set_green();
                else
                    light.set_red();
            });
        }

        public void Jack1(int i)
        {
            lightList.Where(light => light.id < 4).ToList().ForEach(light =>
            {
                if (light.id == i)
                    light.set_red();
            });
        }
        private void change_lights(object source, ElapsedEventArgs e)
        {
            if (counter == 1)
            {
                Jack(1);
                counter++;
            }
            else if (counter == 2)
            {
                Jack1(1);
                counter++;
            }
            else if (counter == 3)
            {
                Jack(2);
                counter++;
            }
            else if (counter == 4)
            {
                Jack1(2);
                counter++;
            }
            else if (counter == 5)
            {
                Jack(3);
                counter++;
            }
            else if (counter == 6)
            {
                Jack1(3);
                counter=1;
            }
            //counter++;
            //  addCar();
            this.Invalidate();
        }

        public void tram_lights()
        {
            tramList.ForEach(tram =>
            {
                if (tram.y < 450 && tram.y > 265)
                {
                    lightList.Where(light => light.id == 4).ToList().ForEach(light =>
                    {
                        light.set_red();
                    });
                }
                else
                {
                    lightList.Where(light => light.id == 4).ToList().ForEach(light =>
                    {
                        light.set_green();
                    });
                }
            });
        }

        public void new_tram()
        {
            tramList.ForEach(tram =>
            {
                if (tram.y < -1000)
                {
                    tram.y = 800;
                }
            });
        }

        public void path_up_to_down(Car car)
        {
            var obj = lightList.Where(x => x.id == 2).First();
            if (obj.is_green() || car.y > 325)
                car.move(0, 10);
        }

        public void path_up_to_left(Car car)
        {
            var obj = lightList.Where(x => x.id == 2).First();
            if (obj.is_green() || car.y > 310)
            {
                if (car.y < 335)
                {
                    car.move(0, 10);
                }
                else
                {
                    car.rotate();
                    car.move(-10, 0);
                }
            }
        }

        public void path_left_to_up(Car car)
        {
            var obj = lightList.Where(x => x.id == 3).First();
            if (obj.is_green() || car.x > 340)
            {
                if (car.x < 460)
                {
                    car.move(10, 0);
                }
                else
                {
                    car.rotate();
                    car.move(0, -10);
                }
            }
        }

        public void path_left_to_down(Car car)
        {
            var obj = lightList.Where(x => x.id == 3).First();
            if (obj.is_green() || car.x > 340)
            {
                if (car.x < 360)
                {
                    car.move(10, 0);
                }
                else
                {
                    car.rotate();
                    car.move(0, +10);
                }
            }

        }

        public void path_down_to_left(Car car)
        {
            var obj = lightList.Where(x => x.id == 1).First();
            if (obj.is_green() || car.y < 460)
            {
                if (car.y > 335)
                {
                    car.move(0, -10);
                }
                else
                {
                    car.rotate();
                    car.move(-10, 0);
                }
            }

        }

        public void path_down_to_up(Car car)
        {
            var obj = lightList.Where(x => x.id == 2).First();
            if (obj.is_green() || car.y < 485)
                car.move(0, -10);
        }

        public void path_right_to_up(Car car)
        {
            var obj = lightList.Where(x => x.id == 1).First();
            var obj1 = lightList.Where(x => x.id == 4).First();
            if ((obj.is_green() && obj1.is_green()) || car.x < 490|| (car.x>610&&car.x<700))
            {
                if (car.x > 460)
                {
                    car.move(-10, 0);
                }
                else
                {
                    car.rotate();
                    car.move(0, -10);
                }
            }
        }

     
        // logika samochodów - trasy
        private void Form1_Paint(object sender, PaintEventArgs e)
        {
            Graphics g = e.Graphics;
            g.DrawImage(Image.FromFile("kocjana-kaliskiego.jpg"), 0, 0);

            // LINQ
            //carList_access.WaitOne();
            carList.ForEach(car =>
            {
                car.draw_vehicle(g);
            });

            //carList_access.Release();

            lightList.ForEach(light =>
            {
                light.draw_light(g);
            });

            tramList.ForEach(tram =>
            {
                tram.draw_vehicle(g);
            });
        }

        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                var x  = Math.Abs(Convert.ToInt32(textBox1.Text));
                for(int i=0;i<x;i++)
                {
                    addCar();
                    Thread.Sleep(10);
                }
            }
           catch(Exception)
            {
                ;
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            tramList.First().y = 760;
        }
    }
}
