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

namespace MyCtls
{
    /// <summary>
    /// RangeNumTextBox.xaml 的交互逻辑
    /// </summary>
    public partial class RangeNumTextBox : UserControl
    {
        public bool IsValueLawful
        {
            get { return (bool) GetValue(IsValueLawfulProperty); }
            set { SetValue(IsValueLawfulProperty, value); }
        }

        public bool IsShowRangeInformation
        {
            get { return (bool) GetValue(IsShowRangeInformationProperty); }
            set { SetValue(IsShowRangeInformationProperty, value); }
        }

        public String MaxVal
        {
            get { return (String)GetValue(MaxValProperty); }
            set { SetValue(MaxValProperty, value); }
        }

        public String MinVal
        {
            get { return (String)GetValue(MinValProperty); }
            set { SetValue(MinValProperty, value); }
        }

        public static readonly DependencyProperty MaxValProperty;

        public static readonly DependencyProperty MinValProperty;

        public static readonly DependencyProperty IsValueLawfulProperty;

        public static readonly DependencyProperty IsShowRangeInformationProperty;

        private static void PropertyChangedCallback(DependencyObject d, DependencyPropertyChangedEventArgs e)
        {

        }

        static RangeNumTextBox()
        {
            MaxValProperty = DependencyProperty.Register("MaxVal", typeof(String), typeof(RangeNumTextBox), new PropertyMetadata("MaxVal", PropertyChangedCallback));
            MinValProperty = DependencyProperty.Register("MinVal", typeof(String), typeof(RangeNumTextBox), new PropertyMetadata("MinVal", PropertyChangedCallback));
            IsValueLawfulProperty = DependencyProperty.Register("IsValueLawful", typeof(Boolean), typeof(RangeNumTextBox), new FrameworkPropertyMetadata(false, PropertyChangedCallback));
            IsShowRangeInformationProperty = DependencyProperty.Register("IsShowRangeInformation", typeof(Boolean), typeof(RangeNumTextBox), new FrameworkPropertyMetadata(true, PropertyChangedCallback));
        }

        public RangeNumTextBox()
        {
            InitializeComponent();
        }

        private void contentText_TextChanged(object sender, TextChangedEventArgs e)
        {
            var tb = sender as TextBox;
            if (tb == null) return;
            try
            {
                var val = Convert.ToDouble(tb.Text);
                if (val >= Convert.ToDouble(MinVal) && val <= Convert.ToDouble(MaxVal))
                {
                    tb.Background = Brushes.White;
                    SetValue(IsValueLawfulProperty, true);
                }
                else
                {
                    tb.Background = Brushes.Red;
                    SetValue(IsValueLawfulProperty, false);
                }
            }
            catch (Exception ex)
            {
                tb.Background = Brushes.Red;
                SetValue(IsValueLawfulProperty, false);
            }
        }
    }
}
