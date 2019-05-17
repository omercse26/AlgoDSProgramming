from random import randint

def getbday():
  return randint(1,365)

NUM_OF_SEEDS = 10000

def birthday():
    n = 1
    
    while n <= 100:
        s = 0
        for k in range(NUM_OF_SEEDS):        
            currbday = {}
            for i in range(n):
                bday = getbday()
                if bday in currbday:
                    currbday[bday] += 1
                else:
                    currbday[bday] = 1
            lst = [i for i in currbday if currbday[i] > 1]
            #print 'for', n, ':', lst, len(lst)
            if len(lst) != 0:
                s += 1
        print 'prob for no of people-', n , ':', s/float(NUM_OF_SEEDS)
            
        n+=1
            
    
birthday()
        
