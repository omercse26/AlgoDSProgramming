from a import *
from CASESchemaGenerator import *

fndefn = """
def fn():
    options = {}
    options['filetypes'] = [('%(f)s', '%(ext)s') ,('all files', '.*')]
    options['multiple'] = %(mul)s                                            
    fl = tkFileDialog.askopenfilename(**options)
    print fl
    %(t)s.insert(INSERT, fl)
"""

start = """
def start():

    xsd = t1.get("1.0", END)
    boot = t2.get("1.0", END)
    fdb = t3.get("1.0", END)
    m = t4.get("1.0", END)
    n = t5.get("1.0", END)

    print (xsd, fdb, boot, m, n, var.get())    
"""

widget = {}          
def create_widgets (t,b, mul, f, e, row):
    widget[t] = { 'widget'   : { 'type' : 'Text', 'height' : '2', 'width' : '30'}, 
                   'grid'    : { 'row' : row, 'column' : '0', 'padx' : '10', 'pady' : '10'}
                }
    widget[b] = { 'widget'   : { 'type' : 'Button', 'height' : '2', 'width' : '10', 'text' : "\'"+f+"\'", 'command' : 'fn'}, 
                   'grid'    : { 'row' : row, 'column' : '2', 'padx' : '10', 'pady' : '10'},
                   'handler' : fndefn % {'mul':mul, 't': t, 'ext' : e, 'f': f},
                }

create_widgets ('t1', 'b1', 1, 'XSD files' , '.xsd', '0')
create_widgets ('t2', 'b2', 0, 'FDB files' , '.FDB', '1')
create_widgets ('t3', 'b3', 0, 'Boot files' , '.*', '2')

widget['t4'] = { 'widget' : { 'type' : 'Text', 'height' : '2', 'width' : '30'}, 
                 'grid'   : { 'row' : '3', 'column' : '0', 'padx' : '10', 'pady' : '10'}
               }    
widget['t5'] = { 'widget' : { 'type' : 'Text', 'height' : '2', 'width' : '30'}, 
                 'grid'   : { 'row' : '4', 'column' : '0', 'padx' : '10', 'pady' : '10'}
               }  
               
widget['c1'] = { 'widget' : { 'type' : 'Checkbutton', 'text' : "\'Create_DDL\'", 'variable' : 'var'}, 
                 'grid'   : { 'row' : '5', 'column' : '0', }
               }               

widget['b4'] =   { 'widget'  : { 'type' : 'Button', 'height' : '2', 'width' : '10', 'text' : "\'Start\'", 'command' : 'start'}, 
                   'grid'    : { 'row' : '6', 'column' : '1', 'padx' : '5', 'pady' : '5', 'columnspan' : '2'},
                   'handler' : start
                 }
                                   
                 
createGrid (widget)   

