namespace wpf.ViewModels
{
    public class MainViewModel : ViewModelBase
    {
        private DriverViewModel _driverViewModel;
        private StopViewModel _stopViewModel;
        private RouteViewModel _routeViewModel;

        public DriverViewModel DriverViewModel
        {
            get { return _driverViewModel; }
            set
            {
                if (_driverViewModel != value)
                {
                    _driverViewModel = value;
                    OnPropertyChanged(nameof(DriverViewModel));
                }
            }
        }

        public StopViewModel StopViewModel
        {
            get { return _stopViewModel; }
            set
            {
                if (_stopViewModel != value)
                {
                    _stopViewModel = value;
                    OnPropertyChanged(nameof(StopViewModel));
                }
            }
        }

        public RouteViewModel RouteViewModel
        {
            get { return _routeViewModel; }
            set
            {
                if (_routeViewModel != value)
                {
                    _routeViewModel = value;
                    OnPropertyChanged(nameof(RouteViewModel));
                }
            }
        }

        public MainViewModel()
        {
            DriverViewModel = new DriverViewModel();
            StopViewModel = new StopViewModel();
            RouteViewModel = new RouteViewModel();
        }
    }
}
