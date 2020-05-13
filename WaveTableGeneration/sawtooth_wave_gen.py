import matplotlib.pyplot as plt
import numpy as np

from createfile import write_to_header_file
from createfile import write_to_source_file

from scipy import signal

t = np.linspace(0.25, 1.25, 120, endpoint=True)
offset = 3072
amplitude = 383
y = offset + amplitude * signal.sawtooth(2 * np.pi * 1 * t, 1)
plt.plot(t, y)

plt.show()

write_to_header_file(y, "saw", "pysaw.h")
write_to_source_file(y, "saw", "pysaw.c", "pysaw.h")

y = offset + amplitude * signal.sawtooth(2 * np.pi * 1 * t, 0)
plt.plot(t, y)

plt.show()

write_to_header_file(y, "saw_rev", "pysaw_rev.h")
write_to_source_file(y, "saw_rev", "pysaw_rev.c", "pysaw_rev.h")

y = offset + amplitude * signal.sawtooth(2 * np.pi * 1 * t, 0.5)
plt.plot(t, y)

plt.show()

write_to_header_file(y, "triangle", "pytriangle.h")
write_to_source_file(y, "triangle", "pytriangle.c", "pytriangle.h")

