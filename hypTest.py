# Program to find measure of expected significance as a function
# of a cut value x_cut applied to measured variable x.
# G. Cowan / RHUL Physics / December 2022

import numpy as np
import scipy.stats as stats
import matplotlib.pyplot as plt
plt.rcParams["font.size"] = 14

#  Plot the pdfs
def f_s(x):
    return 3.*(1-x)**2
def f_b(x):
    return 3.*x**2
x = np.linspace(0., 1., 201)
fs = f_s(x)
fb = f_b(x)
fig = plt.figure(figsize=(5,5))
plt.plot(x, fs, color='orange', label=r'$f(x|s)$')
plt.plot(x, fb, color='dodgerblue', label=r'$f(x|b)$')
plt.xlabel(r'$x$')
plt.ylabel(r'$f(x)$')
plt.xlim(0., 1.)
plt.ylim(0., 3.)
plt.legend(loc='upper center', frameon=False)
plt.subplots_adjust(left=0.15, right=0.9, top=0.9, bottom=0.15)
plt.show()

# Add code here:

# Find x_cut for size alpha = 0.05


# Find power with respect to s hypothesis for this x_cut


# Calculate s, b, signficance for x_cut=0.1, s_tot=10, b_tot=100


# Find s, b, significance versus x_cut


# Plot s, b versus x_cut


# Plot Z_A versus x_cut


# Find x_cut that maximizes Z_A


# Repeat for case where b is uncertain

