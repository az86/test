using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using NMS.PPC.Tools;

namespace Cpu
{
    class Program
    {
        static void Main(string[] args)
        {
            CPUBindder.m_UsedCPUCount = 3;
            Console.WriteLine(CPUBindder.GetMask(4));
        }
    }
}
