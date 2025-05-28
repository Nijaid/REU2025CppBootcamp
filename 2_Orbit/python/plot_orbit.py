##################################################
## Python script to plot output of orbitExample ##
##################################################

import sys
import numpy as np
import matplotlib.pyplot as plt


if len(sys.argv) < 2:
    print("Please pass the name of the file.")
    sys.exit()

# Load the data
times, phi = np.loadtxt(
    sys.argv[1], dtype=np.float64, delimiter=" ", unpack=True
)

# Plot the non-dimensional effective one-body phi
plt.figure(figsize=(10, 8))

plt.plot(times, phi)
plt.xlabel(r"time [s]")
plt.ylabel(r"$\phi$")

plt.show()
