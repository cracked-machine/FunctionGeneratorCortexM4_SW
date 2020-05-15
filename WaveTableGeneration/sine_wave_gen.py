import matplotlib.pyplot as plt
import numpy as np

from createfile import write_to_header_file
from createfile import write_to_source_file

Fs = 120
freq = 1
sample = 120
offset = 3400

# 860   = 1.3Vpp
# 770   = 1.2Vpp
# 710   = 1.1Vpp
# 650   = 1.0Vpp
# 590   = 0.9Vpp
# 530   = 0.8Vpp
# 460   = 0.7Vpp
# 395   = 0.6Vpp
# 327   = 0.5Vpp
# 257   = 0.4Vpp
# 192   = 0.3Vpp
# 120   = 0.2Vpp
# 56    = 0.1Vpp

# amp_label = [100, 200, 300, 400, 500, 600, 700,
#             800, 900, 1000, 1100, 1200, 1300]
# amp_coeff = [56, 120, 192, 257, 327, 395, 460, 530, 590, 650, 710, 770, 860]

amp_label = [1300, 3600]
amp_coeff = [860, 1820]


x = np.arange(sample)

y = []
# results = [ resultpair[ lbl,[data] ] , ... ]

results = []

for n in range(len(amp_coeff)):

    resultpair = []
    resultpair.append(amp_label[n])

    data = []
    y = offset + amp_coeff[n] * np.sin(2 * np.pi * freq * x / Fs)
    data.append(y)
    resultpair.append(data)

    results.append(resultpair)

# res = 5
# print(results[res][0])     # list containging single 'vpp' value
# print(results[res][0])     # list containing data array
# f = np.sin(x)
for n in range(len(results)):
    # get the list containing the array
    data = results[n][1]
    # extract the array from the list and plot it with 'x' list
    plt.plot(x, data[0])

plt.xlabel('sample(n)')
plt.ylabel('voltage(V)')

plt.show()

write_to_header_file(results, "sine", "pysine.h")
write_to_source_file(results, "sine", "pysine.c", "pysine.h")
