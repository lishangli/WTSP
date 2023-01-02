import random
import sys
f = open(sys.argv[1],'w')

for i in range((int)(sys.argv[2])):
    x=random.randint(0,100)
    y = random.randint(0,100)
    r = random.randint(10,100)
    f.write(str(x)+' '+str(y)+' '+str(r)+'\n')

