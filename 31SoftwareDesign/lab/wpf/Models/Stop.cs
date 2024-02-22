using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace wpf.Models
{
    public class Stop
    {
        public int Id { get; set; }

        public string Name { get; set; }

        public decimal Lat { get; set; }

        public decimal Lon { get; set; }

        Stop()
        {

        }

        Stop(int id, string name, decimal lat, decimal lon)
        {
            Id = id;
            Name = name;
            Lat = lat;
            Lon = lon;
        }
    }
}
