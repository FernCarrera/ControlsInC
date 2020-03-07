from ctypes import c_float

PI = c_float(3.141593)
MAX_STEERING_ANGLE =  c_float(40*(3.141593/180))
DT =  c_float(0.1)
WHEEL_BASE = c_float(1.9)
K = c_float(0.5) # Stanley control gain


