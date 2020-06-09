from random import randint

file = open('./data.txt' , 'w' )

nr_of_sizes = 256

nr_of_input = 100

init_bits = 32768

file.write( str(nr_of_sizes) )
file.write( '\n' )
file.write( str(nr_of_input) )
file.write( '\n' )

for j in range(nr_of_sizes):
    bits = init_bits+(j+1)
    a = 2**(bits-30)
    b = 2**bits - 1
    
    for i in range(2*nr_of_input):
        x = randint(int(a), int(b))
        file.write( str('{:x}'.format(int(x))) )
        file.write( '\n' )
        
file.close()
