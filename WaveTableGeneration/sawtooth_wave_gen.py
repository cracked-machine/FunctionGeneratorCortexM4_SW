import matplotlib.pyplot as plt
import numpy as np

from createfile import write_to_header_file
from createfile import write_to_source_file

from scipy import signal

t = np.linspace(0.25, 1.25, 120, endpoint=True)

offset = 3050
amp_label = [1300]
amp_coeff = [860]


y = []
# results = [ resultpair[ lbl,[data] ] , ... ]

saw_results = []

for n in range(len(amp_coeff)):

    resultpair = []
    resultpair.append(amp_label[n])

    data = []
    y = offset + amp_coeff[n] * signal.sawtooth(2 * np.pi * 1 * t, 1)
    data.append(y)
    resultpair.append(data)

    saw_results.append(resultpair)

for n in range(len(saw_results)):
    # get the list containing the array
    data = saw_results[n][1]
    # extract the array from the list and plot it with 'x' list
    plt.plot(t, data[0])

plt.show()

write_to_header_file(saw_results, "saw", "pysaw.h")
write_to_source_file(saw_results, "saw", "pysaw.c", "pysaw.h")


rsaw_results = []

for n in range(len(amp_coeff)):

    resultpair = []
    resultpair.append(amp_label[n])

    data = []
    y = offset + amp_coeff[n] * signal.sawtooth(2 * np.pi * 1 * t, 0)
    data.append(y)
    resultpair.append(data)

    rsaw_results.append(resultpair)

for n in range(len(rsaw_results)):
    # get the list containing the array
    data = rsaw_results[n][1]
    # extract the array from the list and plot it with 'x' list
    plt.plot(t, data[0])

plt.show()


write_to_header_file(rsaw_results, "saw_rev", "pysaw_rev.h")
write_to_source_file(rsaw_results, "saw_rev", "pysaw_rev.c", "pysaw_rev.h")


tri_results = []

for n in range(len(amp_coeff)):

    resultpair = []
    resultpair.append(amp_label[n])

    data = []
    y = offset + amp_coeff[n] * signal.sawtooth(2 * np.pi * 1 * t, 0.5)
    data.append(y)
    resultpair.append(data)

    tri_results.append(resultpair)

for n in range(len(tri_results)):
    # get the list containing the array
    data = tri_results[n][1]
    # extract the array from the list and plot it with 'x' list
    plt.plot(t, data[0])

plt.show()

write_to_header_file(tri_results, "triangle", "pytriangle.h")
write_to_source_file(tri_results, "triangle", "pytriangle.c", "pytriangle.h")

