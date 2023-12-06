using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace wpf.Models
{
    class Route
    {
        public int Id { get; set; }

        public string Name { get; set; }

        public int FirstStopId { get; set; }

        public int LastStopId { get; set; }

        Route()
        {

        }

        Route(int id, string name, int firstStopId, int lastStopId) 
        {
            Id = id;
            Name = name;
            FirstStopId = firstStopId;
            LastStopId = lastStopId;
        }
    }
}
