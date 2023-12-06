using Newtonsoft.Json;
using System;
using System.Collections.ObjectModel;
using System.Net.Http;
using System.Threading.Tasks;
using wpf.Commands;
using wpf.Models;

namespace wpf.ViewModels
{
    public class StopViewModel : ViewModelBase
    {
        private ObservableCollection<Stop> _stops;
        private Stop _selectedStop;
        private DelegateCommand _deleteCommand;

        public ObservableCollection<Stop> Stops
        {
            get { return _stops; }
            set
            {
                if (_stops != value)
                {
                    _stops = value;
                    OnPropertyChanged(nameof(Stops));
                }
            }
        }

        public Stop SelectedStop
        {
            get { return _selectedStop; }
            set
            {
                if (_selectedStop != value)
                {
                    _selectedStop = value;
                    OnPropertyChanged(nameof(SelectedStop));
                    _deleteCommand.RaiseCanExecuteChanged();
                }
            }
        }

        public DelegateCommand DeleteCommand
        {
            get { return _deleteCommand ?? (_deleteCommand = new DelegateCommand(Delete, CanDelete)); }
        }

        public StopViewModel()
        {
            Task.Run(async () => await LoadStopsAsync());
        }

        private bool CanDelete()
        {
            return SelectedStop != null;
        }

        private void Delete()
        {
            Stops.Remove(SelectedStop);
        }

        private async Task LoadStopsAsync()
        {
            try
            {
                using (HttpClient client = new HttpClient())
                {
                    string apiUrl = "http://localhost:5000/Stop";

                    HttpResponseMessage response = await client.GetAsync(apiUrl);

                    if (response.IsSuccessStatusCode)
                    {
                        string json = await response.Content.ReadAsStringAsync();
                        Stops = JsonConvert.DeserializeObject<ObservableCollection<Stop>>(json);
                    }
                    else
                    {
                        Console.WriteLine("Error");
                    }
                }
            }
            catch (Exception ex)
            {
                Console.WriteLine("Error");
            }
        }
    }
}
