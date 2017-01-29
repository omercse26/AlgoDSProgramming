import re
stack = []
operators = ('+', '-', '*', '/')

def isoperator(input):
    if input in operators:
        return True
    
    return False
    
def getpriority(i):
    if i in ['+', '-']:
        return 1
    else:
        return 2
    
def isopenparen(i):
    return i == '('
    
def iscloseparen(i):
    return i == ')'

def popopstack(c, checkpriority=False):
    while stack and isopenparen(stack[-1]) == False and (checkpriority == False or getpriority(stack[-1]) > getpriority(c)):
        print stack.pop(),      

def intopost(input):
    for c in input:
        if re.match('[a-z]', c):
            print c,
        elif isoperator(c):
            popopstack(c, True)                
            stack.append(c)
        elif iscloseparen(c):            
            popopstack(c)
            stack.pop()
                
        else:
            stack.append(c)
            
    while stack:
        print stack.pop(),
                
        
intopost('a+b*c+d')            