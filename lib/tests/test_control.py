#print('__file__={0:<35} | __name__={1:<20} | __package__={2:<20}'.format(__file__,__name__,str(__package__)))
import unittest
import ctypes
import numpy as np
import sys
sys.path.append('/Users/ferncarrera/Documents/Dev/gnc_code/lib')

from wrapper import Data,short_hypo

# 12 typedef struct Data{
# 13         int loc;
# 14         float err_f_axle;
# 15         float* dx;
# 16         float* dy;
# 17 }Data;
#static void short_hypo(Data* data,float fx,float fy,float* cx,float* cy,int size)


'''
x = [1,2,3,4,5]
y = [1,2,3,4,5]
dx = [0,0,0,0,0]
dy = [0,0,0,0,0]
list_float = ctypes.c_float*len(dx)
dx = list_float(*dx)
dy = list_float(*dy)
data = Data(0,0.0,dx,dy)
'''
class TestWrapper(unittest.TestCase):
	

	def test_short_hypo(self):
		# create python c type data struct
		dx = [0,0,0,0,0]
		dy = [0,0,0,0,0]
		list_float = ctypes.c_float*len(dx)
		dx = list_float(*dx)
		dy = list_float(*dy)
		data = Data(0,0.0,dx,dy)
		

		cx = [6,15,6,8]
		cy = [9,3,5,7]
		map_float = ctypes.c_float*len(cx)

		fx = 1 + 2
		fy = 2 + 0

		og_dx = [fx - icx for icx in cx]
		og_dy = [fy - icy for icy in cy]
		d = np.hypot(og_dx,og_dy)
		og_idx = np.argmin(d)

		cx = map_float(*cx)
		cy = map_float(*cy)
		l = ctypes.c_int(4)
		short_hypo(data,fx,fy,cx,cy,4)
		
		print("python:",og_idx)
		print("C:",data.loc)
		print(data.dx, "\n")
		print(data.dy,"\n")
		
		self.assertEqual(og_idx,data.loc)


		
if __name__ == "__main__":
	unittest.main()
