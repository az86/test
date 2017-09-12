using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;


namespace Exception
{
    class Program
    {
        static void Main(string[] args)
        {
            const int testTime = 1000000000;
            Console.WriteLine("TryFor:");
            TryFor(testTime);

            Console.WriteLine("ForTry:");
            ForTry(testTime);

        }

        static void ExFunc(int para)
        {
            if ((para & 0x3FF) == 0)
            {
                throw new OverflowException("sq define exception");
            }
        }

        static void ForTry(int time)
        {
            using (var fs = new FileStream("ForTry.txt", FileMode.Create))
            {
                var sw = new StreamWriter(fs);
                var startTime = DateTime.Now;
                for (var i = 0; i != time; ++i)
                {
                    try
                    {
                        ExFunc(i);
                    }
                    catch (System.OverflowException ex)
                    {
                        sw.WriteLine(ex.Message);
                    }
                }
                var endTime = DateTime.Now;
                Console.WriteLine(endTime - startTime);
            }
        }

        static void TryFor(int time)
        {
            using (var fs = new FileStream("TryFor.txt", FileMode.Create))
            {
                var sw = new StreamWriter(fs);
                var startTime = DateTime.Now;
                var i = 0;
                while (i != time)
                {
                    try
                    {
                        for (; i != time; ++i)
                        {
                            ExFunc(i);
                        }
                    }
                    catch (System.OverflowException ex)
                    {
                        i++;
                        sw.WriteLine(ex.Message);
                    }
                }

                var endTime = DateTime.Now;
                Console.WriteLine(endTime - startTime);
            }
        }
    }
}
