#print('__file__={0:<35} | __name__={1:<20} | __package__={2:<20}'.format(__file__,__name__,str(__package__)))
import unittest
import ctypes
import numpy as np
import sys
sys.path.append('/Users/ferncarrera/Documents/Dev/gnc_code/lib')

from study import calc_target_index,State
from wrapper import State as cState,Data,short_hypo,to_array, calc_target_index as cti

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
		
		d_list = to_array([dx,dy],"float")
		
		data = Data(0,0.0,d_list[0],d_list[1])
		

		cx = [6.2,15.5,6.2,8]
		cy = [9,3,5,7]
		
		c_list = to_array([cx,cy],"float")

		fx = 1 + 2
		fy = 2 + 0

		og_dx = [fx - icx for icx in cx]
		og_dy = [fy - icy for icy in cy]
		d = np.hypot(og_dx,og_dy)
		og_idx = np.argmin(d)

	
		short_hypo(data,fx,fy,c_list[0],c_list[1],4)
		
		print("python:",og_idx)
		print("C:",data.loc)
		#print(data.dx[0:4],"\n")
		#print(data.dy[0:4],"\n")
		
		self.assertEqual(og_idx,data.loc)

	def test_calc_target_index(self):
		dx = [0,0,0,0,0]
		dy = [0,0,0,0,0]
		
		d_list = to_array([dx,dy],"float")
		
		data = Data(0,0.0,d_list[0],d_list[1])


		og = State() 
		c_state = cState(0.0,0.0,0.0,0.0)
		
		# map coordinates
		cx = [6.2,15.6,6,8]
		cy = [9,3,5.4,7]
		c_list = to_array([cx,cy],"float")

		cti(c_state,data,c_list[0],c_list[1],len(cx))
		_,error_front = calc_target_index(og,cx,cy)

		print("python",error_front)
		print("C",data.err_f_axle)

		self.assertAlmostEqual(error_front,round(data.err_f_axle,6))
		
if __name__ == "__main__":
	unittest.main()
