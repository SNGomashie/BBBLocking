import rpyc
import numpy as np
import matplotlib.pyplot as plt


c = rpyc.connect("192.168.7.2", 18861)

c.root.pru_communicate("10000")

data = c.root.pru_read()

sin_array = np.asarray(data)

sin_array -= 32768

samp_freq = 10000  # Hz
freq = 100  # Hz
sample = len(sin_array)
x = np.arange(sample)

Aosin = 32768 * np.sin(2 * np.pi * freq * x / samp_freq)

plt.subplot(2, 1, 1)
plt.title("SIN generated by Python")
plt.plot(x, Aosin)
plt.subplot(2, 1, 2)
plt.title("SIN generated by beaglebone")
plt.plot(x, sin_array)
plt.tight_layout()
plt.show()

plt.title("FFT of SIN generated by Python (16-bit turnication)")
plt.magnitude_spectrum(Aosin, Fs=samp_freq, scale='dB', color='C1')
plt.xlim(0, 200)
plt.show()

plt.title("FFT of SIN generated by BeagleBone Black 16 bit, 256 sample LUT")
plt.magnitude_spectrum(sin_array, Fs=samp_freq, scale='dB', color='C2')
plt.xlim(0, 200)
plt.show()
