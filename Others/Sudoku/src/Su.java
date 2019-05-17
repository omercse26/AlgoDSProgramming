import javax.swing.*;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.lang.reflect.InvocationTargetException;


public class Su extends JFrame {
	
	public static SuTextField txt[][];
	public static final int DIM = 9;
	JButton solve;
	JButton clear;
	Su() {		
		
		Container contentPane = getContentPane();
		contentPane.setLayout(new BorderLayout(0,0));
		// Grid with textfields;
		JPanel gridPane = new JPanel();				
		GridLayout grid = new GridLayout(DIM,DIM);
		gridPane.setLayout(grid);
		
		
		int array[][] = {{0,0,4,6,0,8,9,1,2},
            {0,7,2,0,0,0,3,4,8},
            {1,0,0,3,4,2,5,0,7},
            {0,5,9,7,0,1,4,2,0},
            {0,2,6,0,5,0,7,9,0},
            {0,1,3,9,0,4,8,5,0}, 
            {9,0,1,5,3,7,0,0,4},
            {2,8,7,0,0,0,6,3,0},
            {3,4,5,2,0,6,1,0,0}
          };
	
		txt = new SuTextField[DIM][DIM];
		for (int i=0; i<DIM; i++)
			for (int j=0; j<DIM; j++)
			{
				txt[i][j] = new SuTextField(1);
				int odd_even = (((i/3)*3)+j/3)%2;
				
				if (odd_even == 1)
				{
					txt[i][j].setBackground(new Color(0, 0, 0));
					txt[i][j].setForeground(Color.WHITE);
					
				}
				Su.txt[i][j].setText(Integer.toString(array[i][j]));
				gridPane.add (txt[i][j]);
			}
		
		add(gridPane, BorderLayout.CENTER);
		
		JPanel buttonPane = new JPanel();	
		solve = new JButton("solve");
		clear = new JButton("clear");
		
		solve.addActionListener(new ActionListener() {
								public void actionPerformed(ActionEvent e)
								{
									Solve sl = new Solve();
									try {
										sl.solve();
									} catch (NoSuchMethodException
											| SecurityException
											| IllegalAccessException
											| IllegalArgumentException
											| InvocationTargetException e1) {
										// TODO Auto-generated catch block
										e1.printStackTrace();
									}
									sl.repopulate();
								}
							}
		);
		
		clear.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e)
			{
				for (int i=0; i<DIM; i++)
					for (int j=0; j<DIM; j++)
					{						
						Su.txt[i][j].setText(Integer.toString(0));						
					}
			}
		}
);
		
		buttonPane.add (solve);
		buttonPane.add (clear);
		add(buttonPane, BorderLayout.SOUTH);
		pack();
		setSize(450, 450);		
		setVisible(true);
	}
	
	public static void main(String args[]) {
		
		new Su().addWindowListener(new WindowListener(){

			@Override
			public void windowActivated(WindowEvent arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void windowClosed(WindowEvent arg0) {
				System.exit(0);
				
			}

			@Override
			public void windowClosing(WindowEvent arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void windowDeactivated(WindowEvent arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void windowDeiconified(WindowEvent arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void windowIconified(WindowEvent arg0) {
				// TODO Auto-generated method stub
				
			}

			@Override
			public void windowOpened(WindowEvent arg0) {
				// TODO Auto-generated method stub
				
			}
			
		});
	}

}