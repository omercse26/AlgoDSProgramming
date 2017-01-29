a = 1234

li = [["", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"],
      ["", "", "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety"],
     ]
     
def three(num):
    count = 0
    str = ""
    while num and count < 3:
        curr = num%10
        
        if curr != 0:                        
            if count == 0:
                str = li[count][curr]
            elif count == 1:
                if curr == 1:
                    str = li[0][curr*10+prev]
                else:
                    str = li[count][curr] + " " + str
            else:            
                if len(str) > 0:
                    str = li[0][curr] + " hundred and " + str
                else:
                    str = li[0][curr] + " hundred"
                
        prev = curr
        num = num/10
        count = count + 1
            
    return num, str
    
while a < 1000001:
    num = a
    s = ""
    i = 0
    while num:
        num, str = three(num)
        if i>0:
            s = str + " thousand " + s
        else:
            s = str + " " + s
        
        i = i+1
            
    print s
    a = a+1
