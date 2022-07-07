[![MCHP](images/microchip.png)](https://www.microchip.com)

# Demo of Digital filters on AVR® EA using Microchip Studio

Digital filters are useful for signal processing. The application can range from smoothing signals to estimating future values based on other analog signals. In this collection of examples you can find filter demos based on finding the median, fast fourier transfom, infinite impulse response, and a *Kalman* filter algorithm. 

[Median Filter](median/README.md)

The Median filter is a simple idea to smooth a signal by removing spikes from the signal. The median filter can be used both on images and on 1-dimensional signal problems. Here, the latter is covered. 

[Fast Fourier Transform](fft/README.md)

The Fast Fourier Transformation (FFT) is a versatile tool for signal analysis. The general idea, in terms of electronic signals, is to de-compose a given signal (in the time domain) into sinus-shaped components (in the frequency domain). Each component has a handful of parameters (amplitude, frequency and phase) that help analyzing the input signal.

[Infinite Impulse Response](iir/README.md)

Infinite Impulse Response (IIR) filters are a class of filters that are feedback-based, i.e. the previous output plays a role in the current output. The demo will cover *Band Pass Filter* and *Low Pass Filter*. The library also supports *High Pass Filter*, *Notch Filter*, *Peaking Band EQ Filter*, *Low Shelf Filter* and *High Shelf Filter*.

[Kalman](kalman/README.md)

The Kalman filter, also called linear quadratic estimation (LQE), is an algorithm that uses a series of measurements to estimate unknown variables in the future. State estimation can for example be used to predict the placement of a robotic vacuum cleaner to avoid hitting into walls, or for creating a balancing robot.

    
## Related Documentation

- [Microchip Application Note AN4515: "Processing Analog Sensor Data with Digital Filtering"](https://ww1.microchip.com/downloads/en/Appnotes/ProcessAnalogSensorDataDigitalFiltering-DS00004515.pdf)
- [The Road to Median Filter Mastery](https://blog.eddyfi.com/en/the-road-to-median-filter-mastery)
- [FFT Visualization and Explanation](https://www.karlsims.com/fft.html)
- [Digital Filters and IIR](http://musicweb.ucsd.edu/~trsmyth/filters/Digital_Filters.html)
- [Kalman Filter For Dummies](http://bilgin.esme.org/BitsAndBytes/KalmanFilterforDummies)


## Software Used
- [Microchip Studio IDE v7.0.2594](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio) or newer
- [MPLAB® Xpress IDE](https://www.microchip.com/xpress) (alternative to MPLAB X IDE)
- [XC8 Compiler v2.40](https://www.microchip.com/en-us/tools-resources/develop/mplab-xc-compilers) or newer
- [Microchip AVR64EA48 Device Support Pack AVR-Dx_DFP 2.2.56](https://packs.download.microchip.com/) or newer

## Hardware Used

* [AVR64EA48 Curiosity Nano](https://www.microchip.com/DevelopmentTools/ProductDetails/PartNO/EV66E56A)

## Setup

<!-- Explain how to connect hardware and set up software. Depending on complexity, step-by-step instructions and/or tables and/or images can be used -->
All code examples were created using an AVR64EA48 Curiosity Nano Evaluation Kit and the MPLAB X IDE. Refer to the AVR64EA48 Curiosity Nano Hardware User Guide for using the evaluation kit together with the IDE.

## Operation

<!-- Explain how to operate the example. Depending on complexity, step-by-step instructions and/or tables and/or images can be used -->
Refer to the individual filter examples on how to configure and use the filters.


## Summary
After going through these use cases, you should better understand how to use the mentioned filters in an AVR context. This includes how this can be used together with the MPLAB® Code Configurator called Melody and also measuring the speed of the filters.


