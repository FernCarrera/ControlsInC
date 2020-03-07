import ctypes
import const

def wrap_function(lib,funcname,restype,argtypes):
	''' Function to simplify wrapping functions '''
	func = lib.__getattr__(funcname)
	func.restype = restype
	func.argtypes = argtypes
	return func


# State structure {}
class State(ctypes.Structure):
	'''Wraps the state struct as a python class '''

	_fields_ = [('x',ctypes.c_float),
		    ('y',ctypes.c_float),
		    ('head',ctypes.c_float),
		    ('v',ctypes.c_float)]

	def __repr__(self):
		return '{0},{1},{2},{3}'.format(self.x,
					self.y,self.head,
					self.v)


class Data(ctypes.Structure):
	''' wrap for Data struct '''

	_fields_ = [('loc',ctypes.c_float),
		    ('err_f_axle',ctypes.c_float),
		    ('dx',ctypes.POINTER(ctypes.c_float)),
		    ('dy',ctypes.POINTER(ctypes.c_float)),]

	def __repr__(self):
		return '{0},{1},{2},{3}'.format(self.loc,
					self.err_f_axle,
					self.dx,self.dy)

class Control(ctypes.Structure):
	''' wrap for Control struct '''
	
	_fields_ = [('Kp',ctypes.c_float),
		    ('Ki',ctypes.c_float),
		    ('Kd',ctypes.c_float),
		    ('delta',ctypes.c_float),
		    ('p_lat_err',ctypes.c_float),
		    ('p_state',ctypes.c_float),
		    ('p_err',ctypes.c_float),
		    ('p_time',ctypes.c_float)]

	def __repr__(self):
		return '{0},{1},{2},{3},{4},{5},{6},{7}'.format(
			self.Kp,self.Ki,self.Kd,self.delta,
			self.p_lat_err,self.p_state,self.p_err,
			self.p_time)



if __name__ == '__main__':
	# load shared library into c types. needs to link to a *.so file

	libc = ctypes.CDLL("./libcontrol.so")

#---------------------------------------------------------------------
print("passing a struct into C")

print_state = wrap_function(libc,'print_state',None,[ctypes.POINTER(State)])
a = State(1,2,3,4)
#print("state in python is",a)
#print_state(a)

#---------------------------------------------------------------------

update = wrap_function(libc,'update',None,
			[ctypes.POINTER(State),
			 ctypes.c_float,
			 ctypes.c_float,])
print("new position")
update(a,10.0,4.0)
print("position in python is",a)
print()
print("position in C is")
print_state(a)

#---------------------------------------------------------------------

# void stanley(State* state,float* cx,float* cy,int last_trgt);

stanley = wrap_function(libc,'stanley',None,
			[ctypes.POINTER(State),
			 ctypes.POINTER(ctypes.c_float),
			 ctypes.POINTER(ctypes.c_float),
			 ctypes.c_int])


#---------------------------------------------------------------------

#float pid_control(Control*, float,float,float lat_err,float time);

pid_control = wrap_function(libc,'pid_control',ctypes.c_float,
			    [ctypes.POINTER(Control),
			     ctypes.c_float,
			     ctypes.c_float,
			     ctypes.c_float,
			     ctypes.c_float])
pid = Control(1,1,1,0,0,0,0,0)
correction = pid_control(pid,5,0,3,2)				
pid_control(pid,5,2,4,5)
print('correction',correction)
print('control state',pid)


