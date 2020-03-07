import ctypes

def wrap_function(lib,funcname,restype,argtypes):
	''' Function to simplify wrapping functions '''
	func = lib.__getattr__(funcname)
	func.restype = restype
	func.argtypes = argtypes
	return func


# State structure {}
class State(ctypes.Structure):
	_fields_ = [('x',ctypes.c_float),
		    ('y',ctypes.c_float),
		    ('head',ctypes.c_float),
		    ('v',ctypes.c_float)]

	def __repr__(self):
		return '{0},{1},{2},{3}'.format(self.x,
					self.y,self.head,
					self.v)




if __name__ == '__main__':
	# load shared library into c types. needs to link to a *.so file

	libc = ctypes.CDLL("./libcontrol.so")

#---------------------------------------------------------------------
print("passing a struct into C")

print_state = wrap_function(libc,'print_state',None,[ctypes.POINTER(State)])
a = State(1,2,3,4)
print("state in python is",a)
print_state(a)

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



