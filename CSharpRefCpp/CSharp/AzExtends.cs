using System;
using System.Collections.Generic;
using System.Linq;

namespace CSharp
{
    static class AzExtends
    {
        /// <summary>
        /// 对List<int> 扩展一个求方差的方法
        /// </summary>
        /// <param name="data">要求方差的数组</param>
        /// <returns>方差</returns>
        public static double GetVariance(this List<int> data)
        {
            var avg = data.Average();
            var variance = data.Select(val => Math.Pow(val - avg, 2)).Average();
            return variance;
        }
    }
}
