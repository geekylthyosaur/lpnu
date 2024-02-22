using Newtonsoft.Json;
using System;
using System.Collections.ObjectModel;
using System.Net.Http;
using System.Threading.Tasks;
using wpf.Commands;
using wpf.Models;

namespace wpf.ViewModels
{
    public class RouteViewModel : ViewModelBase
    {
        private ObservableCollection<Route> _routes;
        private Route _selectedRoute;
        private DelegateCommand _deleteCommand;

        public ObservableCollection<Route> Routes
        {
            get { return _routes; }
            set
            {
                if (_routes != value)
                {
                    _routes = value;
                    OnPropertyChanged(nameof(Routes));
                }
            }
        }

        public Route SelectedRoute
        {
            get { return _selectedRoute; }
            set
            {
                if (_selectedRoute != value)
                {
                    _selectedRoute = value;
                    OnPropertyChanged(nameof(SelectedRoute));
                    _deleteCommand.RaiseCanExecuteChanged();
                }
            }
        }

        public DelegateCommand DeleteCommand
        {
            get { return _deleteCommand ?? (_deleteCommand = new DelegateCommand(Delete, CanDelete)); }
        }

        public RouteViewModel()
        {
            Task.Run(async () => await LoadRoutesAsync());
        }

        private bool CanDelete()
        {
            return SelectedRoute != null;
        }

        private void Delete()
        {
            Routes.Remove(SelectedRoute);
        }

        private async Task LoadRoutesAsync()
        {
            try
            {
                using (HttpClient client = new HttpClient())
                {
                    string apiUrl = "http://localhost:5000/Route"; // Update API endpoint for routes

                    HttpResponseMessage response = await client.GetAsync(apiUrl);

                    if (response.IsSuccessStatusCode)
                    {
                        string json = await response.Content.ReadAsStringAsync();
                        Routes = JsonConvert.DeserializeObject<ObservableCollection<Route>>(json);
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
