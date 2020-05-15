import matplotlib.pyplot as plt
import numpy as np

from createfile import write_to_header_file
from createfile import write_to_source_file

from scipy import signal

t = np.linspace(0.25, 1.25, 120, endpoint=True)
offset = 3400
amp_label = [3600]
amp_coeff = [1820]

y = []
# results = [ resultpair[ lbl,[data] ] , ... ]

results = []

for n in range(len(amp_coeff)):

    resultpair = []
    resultpair.append(amp_label[n])

    data = []
    y = offset + amp_coeff[n] * signal.square(2 * np.pi * 1 * t)
    data.append(y)
    resultpair.append(data)

    results.append(resultpair)

for n in range(len(results)):
    # get the list containing the array
    data = results[n][1]
    # extract the array from the list and plot it with 'x' list
    plt.plot(t, data[0])

plt.xlabel('sample(n)')
plt.ylabel('voltage(V)')

plt.show()

write_to_header_file(results, "square", "pysquare.h")
write_to_source_file(results, "square", "pysquare.c", "pysquare.h")

