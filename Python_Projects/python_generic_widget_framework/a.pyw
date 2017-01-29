from Tkinter import *
import tkFileDialog 

class GridBuilder(Frame):
  
    def __init__(self, parent, w):
        Frame.__init__(self, parent, background="white")   
         
        self.parent = parent
        self.xmap = []
        
        self.initUI(w)
    
    def initUI(self, w):                      
        global handlerdict
        global retdict
        handlerdict = dict()
        retdict = dict()
        widgetmap = dict()
            
        widgets = w
        
        for i in widgets:            
            handlerdict[i] = None            
            widgetmap[i] = "handlerdict[\'"+i+"\']"
            
        for i in widgets:                                                
            
            if 'handler' in widgets[i]:
                str = (widgets[i]['handler'])
                exec (str, globals())
            
            widgetprops = widgets [i] ['widget']
            
            method = widgetprops['type']
            
            command =  '' 
            
            for attr in widgetprops:
            
                if attr == 'variable':
                    chkboxvar = 'global ' + widgetprops[attr] + '\n'
                    chkboxvar += (widgetprops[attr] + ' = IntVar()')
                    exec (chkboxvar)
                    print chkboxvar
                    command += (attr + '=' + widgetprops[attr] + ',')
                    
                elif attr != 'type':
                    command += (attr + '=' + widgetprops[attr] + ',')
                    
                
                    
            command = method + '(' + command + ')'
            print command
          
            
            exec ( 'global '+i+'\n'+ i +' = ' + command)
            #handlerdict[i] = ret
            
            grid_command = ''
            
            for attr in widgets[i]['grid']:
                grid_command += (attr + '=' + widgets[i]['grid'][attr] + ',')
                
            grid_command = i + '.grid (' + grid_command + ')'
            
           
            exec (grid_command)
            

def getWidget(w):
    return handlerdict[w]
    
def putValue(k,v):
    retdict[k] = v
    
def getValue(k):
    return retdict[k]    

def createGrid(w):
  
    global root
    root = Tk()   
    app = GridBuilder(root, w)
    root.mainloop()  


if __name__ == '__main__':
    main()  
