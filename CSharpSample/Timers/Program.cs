using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Timers
{
    class Program
    {
        static void Main(string[] args)
        {
            var p = new Program();
            p.TestTimer();
            Console.WriteLine(DateTime.Now);
            System.Threading.Thread.Sleep(10000000);
            Console.ReadKey();
        }

        private void TestTimer()
        {
            var t0 = new System.Threading.Timer(ThreadingTimerWorker, null, 3000, 1000);
            //var t1 = new System.Timers.Timer(1000);
            // t1.Elapsed += TimerTimerWorer;
            // t1.Start();
        }



        private int _workerIndex;

        void ThreadingTimerWorker(object obj)
        {
            var workerIndex = _workerIndex++;
            Console.WriteLine("worker:{0} time:{1} Enter:ThreadingTimerFunc, ID:{2}", workerIndex, DateTime.Now, System.Threading.Thread.CurrentThread.ManagedThreadId);
            //System.Threading.Thread.Sleep(10000);
            Console.ReadKey();
            Console.WriteLine("worker:{0} time:{1} Leave:ThreadingTimerFunc, ID:{2}", workerIndex, DateTime.Now, System.Threading.Thread.CurrentThread.ManagedThreadId);
        }

        void TimerTimerWorer(object sender, System.Timers.ElapsedEventArgs e)
        {
            var workerIndex = _workerIndex++;
            Console.WriteLine("worker:{0} time:{1} Enter:ThreadingTimerFunc, ID:{2}", workerIndex, DateTime.Now, System.Threading.Thread.CurrentThread.ManagedThreadId);
            System.Threading.Thread.Sleep(50000);
            Console.WriteLine("worker:{0} time:{1} Leave:ThreadingTimerFunc, ID:{2}", workerIndex, DateTime.Now, System.Threading.Thread.CurrentThread.ManagedThreadId);
        }
    }
}
