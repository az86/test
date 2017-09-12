using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows; // for Point by zyj
using System.Windows.Media; // for PointCollection by zyj
using CLI;

namespace CSharp
{
    class Program
    {
        static void Main(string[] args)
        {
            ////////////Start by zyj/////////////////////////
            var mCol = new PointCollection { new Point(1, 1), new Point(2, 2) }; // collection initialize is recommended.
            var pathData = mCol.ToArray();
            var test = new CTestWrap { Edge = pathData }; // object initialize is recommended
            ///////////End by zyj/////////////////////

            var arr = test.GetArray(AWrap.All7Wrap);
            Console.WriteLine(arr.GetType());
            arr.ToList().ForEach(val => Console.Write("{0}, ", val));   // List has ForEach function. so convert array to list.

            //Test IntPtr address value
            var ptrAdd = test.GetCore();
            unsafe
            {
                var val = (short**)test.GetCore().ToPointer();
                Console.WriteLine("{0}, {1}", ptrAdd, (int)val);
            }
        }
    }
}
