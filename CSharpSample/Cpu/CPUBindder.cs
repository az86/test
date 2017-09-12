using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Threading;

namespace NMS.PPC.Tools
{
    public class CPUBindder
    {
        public static int m_UsedCPUCount = 0;

        public static int GetFreeThreeCPUNum()
        {
            return Environment.ProcessorCount - m_UsedCPUCount;
        }

        public static bool BindCPUsToProcess(Process process, int cpuCount)
        {
            uint cpuMask = GetMask(cpuCount);
            return SetProcessAffinityMask(process.Handle, cpuMask);
        }

        public static uint GetMask(int count)
        {
            if (count > GetFreeThreeCPUNum())
            {
                throw new ArgumentException("There is not enough processors!");
            }
            uint cpuMask = 0;
            for (int i = 0; i != count; ++i )
            {
                cpuMask <<= 1;
                cpuMask |= 1;
            }
            for (int i = 0; i != m_UsedCPUCount; ++i)
            {
                cpuMask <<= 1;
            }
            return cpuMask;
        }

        [DllImport("Kernel32.dll")]
        public static extern bool GetProcessGroupAffinity(IntPtr hProcess, UIntPtr GroupCount, UIntPtr GroupArray);

        [DllImport("Kernel32.dll")]
        public static extern bool SetProcessAffinityMask(IntPtr hProcess, uint dwProcessAffinityMask);

        [DllImport("Kernel32.dll")]
        public static extern UIntPtr SetThreadAffinityMask(IntPtr hThread, uint dwThreadAffinityMask);

    }
}
