import matplotlib.pyplot as plt
import numpy as np
from createfile import write_to_header_file, write_to_source_file

N = 320
# x1 = np.geomspace(start=30, stop=110,  num=N, endpoint=True, dtype=int)
x1 = np.geomspace(start=2000, stop=65535,  num=N, endpoint=True, dtype=int)
x2 = np.linspace(start=2000, stop=65535, num=N, endpoint=True, dtype=int)
# x2 = np.geomspace(start=1024, stop=48,  num=N, endpoint=True, dtype=int)
# x3 = np.concatenate([x1, x2])
# y = np.zeros(N)
y = np.zeros(N)
plt.plot(x1, y, 'o')
# plt.plot(x2, y, 'o')

# plt.ylim([-0.5, 1])
hex_array1 = [hex(x) for x in x1]
hex_array2 = [hex(x) for x in x2]
plt.show()

plt.plot(x2, y, 'o')
plt.show()

write_to_header_file(hex_array1, "fade_log_seq", "fade_log_seq.h")
write_to_source_file(hex_array1, "fade_log_seq", "fade_log_seq.c", "fade_log_seq.h")
write_to_header_file(hex_array2, "fade_lin_seq", "fade_lin_seq.h")
write_to_source_file(hex_array2, "fade_lin_seq", "fade_lin_seq.c", "fade_lin_seq.h")
