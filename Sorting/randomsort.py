from random import randint
import copy

olst = [1,2,3,4]
    
broken = True
itr = 0

while broken:
    lst = copy.deepcopy(olst)
    newlist = []
    broken = False
    
    while len(lst) > 0:
        i = randint (0, len(lst)-1)   
        
        #if item to be added is less than previous element, break the loop prematurely
        if len(newlist) > 0 and newlist[-1] > lst[i]:
            broken = True
            break
            
        newlist.append(lst[i])
        del lst[i]   
        
    itr = itr + 1    
    
print itr, newlist 

