print('testuje poprawnosc...')

file_in = open('./test1.txt' , 'r' )
results = open('./results1.txt' , 'r' )
nr_of_sizes = int( file_in.readline() )
nums_per_size = int( file_in.readline() )
flag_w = 0

for x in range(nr_of_sizes*nums_per_size):
	a = int(file_in.readline(), base=16)
	b = int(file_in.readline(), base=16)
	r = int(results.readline(), base=16)
	if a*b != r:
		flag_w += 1;		
		print( x, " bad ", r)
	else:
		1+1
		#print( x, " good ", r)


#print("mnozenie bits= ", bits)
print("wrong : ", flag_w)
file_in.close()
results.close()
