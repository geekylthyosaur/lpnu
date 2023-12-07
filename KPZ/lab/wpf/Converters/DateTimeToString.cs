using System;
using System.Collections.Generic;
using System.Globalization;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Data;

namespace wpf.Converters
{
    [ValueConversion(typeof(DateTime), typeof(string))]
    class DateTimeToString : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, CultureInfo culture)
        {
            DateTime? dateTime = value as DateTime?;
            return dateTime?.ToString("dd-MM-yyyy, hh:mm");
        }

        public object ConvertBack(object value, Type targetType, object parameter, CultureInfo culture)
        {
            string s = value as string;
            if (DateTime.TryParse(s, out DateTime result))
            {
                return result;
            }
            return DependencyProperty.UnsetValue;
        }
    }
}
