from a import *

browsehandler = """
def browse():
    options = {}
    options['filetypes'] = [('text files', '.txt') ,('all files', '.*')]
    options['multiple'] = 0                             
    fl = tkFileDialog.askopenfilename(**options)
    print fl    
    txt1.insert(INSERT, fl)
"""

widget = {} 

widget['txt1'] =  { 'widget' : { 'type' : 'Text', 'height' : '2', 'width' : '30'}, 
                    'grid'   : { 'row' : '0', 'column' : '0', 'padx' : '10', 'pady' : '10'}
                  }  
               
widget['butt'] =  { 'widget'   : { 'type' : 'Button', 'height' : '2', 'width' : '10', 'text' : "\'Browse\'", 'command' : 'browse'}, 
                    'grid'     : { 'row' : '0', 'column' : '2', 'padx' : '10', 'pady' : '10'},
                    'handler'  : browsehandler,
                  }     

createGrid (widget)                   