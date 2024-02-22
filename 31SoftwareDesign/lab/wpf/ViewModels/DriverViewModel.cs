using Newtonsoft.Json;
using System;
using System.Collections.ObjectModel;
using System.Net.Http;
using System.Threading.Tasks;
using wpf.Commands;
using wpf.Models;

namespace wpf.ViewModels
{
    public class DriverViewModel : ViewModelBase
    {
        private ObservableCollection<Driver> _drivers;
        private Driver _selectedDriver;
        private DelegateCommand _deleteCommand;

        public ObservableCollection<Driver> Drivers
        {
            get { return _drivers; }
            set
            {
                if (_drivers != value)
                {
                    _drivers = value;
                    OnPropertyChanged(nameof(Drivers));
                }
            }
        }

        public Driver SelectedDriver
        {
            get { return _selectedDriver; }
            set
            {
                if (_selectedDriver != value)
                {
                    _selectedDriver = value;
                    OnPropertyChanged(nameof(SelectedDriver));
                    _deleteCommand.RaiseCanExecuteChanged();
                }
            }
        }

        public DelegateCommand DeleteCommand
        {
            get { return _deleteCommand ?? (_deleteCommand = new DelegateCommand(Delete, CanDelete)); }
        }

        public DriverViewModel()
        {
            Task.Run(async () => await LoadDriversAsync());
        }

        private bool CanDelete()
        {
            return SelectedDriver != null;
        }

        private void Delete()
        {
            Drivers.Remove(SelectedDriver);
        }

        private async Task LoadDriversAsync()
        {
            try
            {
                using (HttpClient client = new HttpClient())
                {
                    string apiUrl = "http://localhost:5000/Driver";

                    HttpResponseMessage response = await client.GetAsync(apiUrl);

                    if (response.IsSuccessStatusCode)
                    {
                        string json = await response.Content.ReadAsStringAsync();
                        Drivers = JsonConvert.DeserializeObject<ObservableCollection<Driver>>(json);
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
