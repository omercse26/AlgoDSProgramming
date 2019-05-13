strs = ["hers", "his", 'she']

tabmap = {}
state = 0
states = set()
allprefixes = []
prefixmap = {}
invprefixmap = {}

def build():
    global state
    for st in strs:
        curr = 0
        for ch in st:
            try:                
                curr = tabmap[curr][ch]              
            except KeyError:
                state = state+1
                if curr not in tabmap:
                    tabmap[curr] = {ch:state}
                else:
                    tabmap[curr][ch] = state
                curr = state
                
def printstates():
    a = [k for k in tabmap]
    b = [tabmap[k][i] for k in tabmap for i in tabmap[k]]
    states.update(a)
    states.update(b)        
    print states
    
def getallprefixes(node=0, prefix=""):
    if node not in tabmap:
        return
        
    for ch in tabmap[node]:
        allprefixes.append(prefix+ch)
        prefixmap[tabmap[node][ch]] = prefix+ch 
        invprefixmap[prefix+ch] = tabmap[node][ch]
        getallprefixes(tabmap[node][ch], prefix+ch)
        
def findfailstates():
    failstates = [0] * len(states)
    
    for state in states:
        if state == 0 or state == 1:
            continue
            
        prefixforstate = prefixmap[state]
        suffixes = []
        
        for i in range(1, len(prefixforstate)):
            suffixes.append(prefixforstate[i:])
            
        print '---->', state, suffixes
        for suffix in suffixes:
            if suffix in allprefixes:
                failstates[state] = invprefixmap[suffix] 
                break
    
    
    print failstates
    
def getfailstates(state=0, strs=[]):
    if state not in tabmap:
        return
        
    for ch in tabmap[state]:
    
        suffixes = []
        
        if state != 0:            
            suffixes = [ch] if len(strs) == 0 else [i+ch for i in strs] + [ch]
            
            for suffix in suffixes:
                if suffix in allprefixes:
                    print 'failstate for ', tabmap[state][ch], invprefixmap[suffix] 
                    break
            
        getfailstates(tabmap[state][ch], suffixes)
        
    
        
build()
print tabmap
printstates()  
getallprefixes()    
print allprefixes     
findfailstates()     
getfailstates()    

