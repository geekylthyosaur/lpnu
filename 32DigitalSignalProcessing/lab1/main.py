import numpy as np
import matplotlib.pyplot as plt
import math
import json

# Define the original signal function
def f(t):
    t_mod = t % (2 * np.pi)
    if t_mod > np.pi:
        t_mod -= 2 * np.pi
    
    if -np.pi < t_mod <= 0:
        return t_mod
    elif 0 < t_mod < np.pi:
        return 2 * t_mod
    else:
        return 0

# Function to compute Fourier coefficients
def fourier_coefficients(f, N):
    a0 = (1/np.pi) * np.trapz([f(t) for t in np.linspace(-np.pi, np.pi, 1000)], np.linspace(-np.pi, np.pi, 1000))
    an = lambda n: (1/np.pi) * np.trapz([f(t) * np.cos(n*t) for t in np.linspace(-np.pi, np.pi, 1000)], np.linspace(-np.pi, np.pi, 1000))
    bn = lambda n: (1/np.pi) * np.trapz([f(t) * np.sin(n*t) for t in np.linspace(-np.pi, np.pi, 1000)], np.linspace(-np.pi, np.pi, 1000))
    coefficients = {'a0': a0, 'an': [an(n) for n in range(1, N+1)], 'bn': [bn(n) for n in range(1, N+1)]}
    return coefficients

# Function to approximate the signal using Fourier series
def fourier_series_approximation(t, coefficients, N):
    a0 = coefficients['a0']
    an = coefficients['an']
    bn = coefficients['bn']
    approximation = a0/2 + sum([an[n-1]*np.cos(n*t) + bn[n-1]*np.sin(n*t) for n in range(1, N+1)])
    return approximation

# Function to compute the mean absolute error of the approximation
def mean_absolute_error(original, approximation):
    return np.mean(np.abs(np.array(original) - np.array(approximation)))

# Function to save results to a file
def save_results(N, coefficients, error):
    with open("fourier_results.json", "w") as file:
        results = {'N': N, 'coefficients': coefficients, 'error': error}
        json.dump(results, file, indent=2)
        
# Main program
def main(start=-4*np.pi, end=4*np.pi, N=10):
    t_values = np.linspace(start, end, 1000)
    original_signal = [f(t) for t in t_values]
    coefficients = fourier_coefficients(f, N)
    approximation = [fourier_series_approximation(t, coefficients, N) for t in t_values]
    error = mean_absolute_error(original_signal, approximation)
    save_results(N, coefficients, error)
    
    # Visualization
    plt.figure(figsize=(10, 6))
    plt.plot(t_values, original_signal, label='Original Signal')
    plt.plot(t_values, approximation, label='Fourier Approximation', linestyle='--')
    plt.title(f'Fourier Series Approximation with N={N}')
    plt.legend()
    plt.show()

if __name__ == "__main__":
    main()

