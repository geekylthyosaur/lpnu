namespace wpf.ViewModels
{
    public class MainViewModel : ViewModelBase
    {
        private DriverViewModel _driverViewModel;

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

        public MainViewModel()
        {
            // Initialize the view models
            DriverViewModel = new DriverViewModel();
            // Add other view models as needed for "Stops" and "Routes" tabs
        }
    }
}
