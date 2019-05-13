from a import *

widgets = {} 

widgets['txt1'] =  { 'widget' : { 'type' : 'Text', 'height' : '2', 'width' : '30'}, 
                     'grid'   : { 'row' : '0', 'column' : '0', 'padx' : '10', 'pady' : '10'}
                   }  
               
widgets['butt'] =  { 'widget'   : { 'type' : 'Button', 'height' : '2', 'width' : '10', 'text' : "\'Browse\'"}, 
                     'grid'     : { 'row' : '0', 'column' : '2', 'padx' : '10', 'pady' : '10'}                
                   }     

createGrid (widgets)                   