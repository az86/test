using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;

namespace TestParallel
{
    class Program
    {
        static void Main(string[] args)
        {
            var tArray = new int[1024*1024*10];
            int i = 0;
            Parallel.For(0, 1024*1024*10, (index) =>
                {
                   tArray[index] = System.Threading.Interlocked.Increment(ref i);
                });
            Console.WriteLine(tArray.Max());
            Console.WriteLine(1024*1024*10);
        }
    }
}
