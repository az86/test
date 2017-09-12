using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace AdornerSimple
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();

            var tb = new TextBox { Width = 100, Height = 100 };
            var sss = new AdornerDecorator { Child = tb };
            Content = sss;

            sss.AdornerLayer.Add(new SimpleCircleAdorner(tb));
            //AdornerLayer.GetAdornerLayer(tb).Add(new SimpleCircleAdorner(tb)); // same code
        }
    }
}
