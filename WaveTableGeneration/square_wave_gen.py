import matplotlib.pyplot as plt
import numpy as np

from createfile import write_to_header_file
from createfile import write_to_source_file

from scipy import signal

t = np.linspace(0.25, 1.25, 120, endpoint=True)
offset = 3072
amplitude = 383
y = offset + amplitude * signal.square(2 * np.pi * 1 * t)
plt.plot(t, y)

plt.show()

write_to_header_file(y, "square", "pysquare.h")
write_to_source_file(y, "square", "pysquare.c", "pysquare.h")

