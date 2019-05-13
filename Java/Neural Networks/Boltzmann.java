/*
 * Boltzmann.java
 *
 * Created on April 28, 2007, 11:59 AM
 *
 * To change this template, choose Tools | Template Manager
 * and open the template in the editor.
 */

/**
 *
 * @author naseeha
 */
import java.io.*;
import java.util.Random;

class Initialize
{
    Network network;
    public Initialize()
    {
        
    }
    
    public Network formNetwork(int n) throws IOException
    {
        /*BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        network = new Network(n);
        int num;
        System.out.println("Enter the Input");
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                num = br.read();           
                network.makeNetwork(num,i,j);
            }
        }
        
        return network;*/
        BufferedReader br = new BufferedReader(new FileReader("Input.txt"));
        network = new Network(n);
        char num;
        System.out.println(" Input from File");
        for(int i=1;i<=n;i++)
        {
            for(int j=1;j<=n;j++)
            {
                do{
                num = (char)br.read(); 
                }while(num=='\r' || num == '\n');
                
                System.out.println("reading file :i :"+i+" j :"+j+" num :"+num);
                network.makeNetwork(num,i,j,true);
            }
        }
        
        return network;
     }
    
    public Network Fillup(Network network)
    {
        return network.Fillup();
    }
    
    public Weight formWeight(int n,Network network,int penalty,int bonus)
    {
        Weight initial = new Weight(n);
        return initial.formWeight(network,penalty,bonus);
    }
    
    
}

class UnitWeight
{
    
  int weight ;
  char weight_avail;
}


class Weight
{
    UnitWeight unit[][];
    int weight_dimension;
    int network_dimension;
    float total_energy = 0;
    public Weight(int n)
    {
       network_dimension = n;
       weight_dimension = n*n;
       unit = new UnitWeight[weight_dimension+1][weight_dimension+1];
       for(int i=1;i<=weight_dimension;i++)
       {
           for(int j=1;j<=weight_dimension;j++)
           {
               unit[i][j] = new UnitWeight();
           }
       }
    }
    
    public Weight formWeight(Network network,int penalty,int bonus)
    {
        System.out.println("in formWeight");
        System.out.println("weight dim :"+weight_dimension);
        for(int i=1;i<=weight_dimension;i++)
        {
            for(int j=1;j<=weight_dimension;j++)
            {
                //System.out.println("i :"+i+"j :"+j);
                int x1 = xaxis(i);
                int x2 = xaxis(j);
                
                
                int y1 = yaxis(i);
                int y2 = yaxis(j);
                //System.out.println("x1 :"+x1+"y1 :"+y1);
                //System.out.println("x2 :"+x2+"y2 :"+y2);
                
                int bx1 = block(x1);
                int by1 = block(y1);
                
                
                int bx2 = block(x2);
                int by2 = block(y2);
                //System.out.println("bx1 :"+bx1+"by1 :"+by1);
                //System.out.println("bx2 :"+bx2+"by2 :"+by2);
                
                
                
                if(i == j)
                {
                    unit[i][j].weight = 0;
                    unit[i][j].weight_avail = 'N';
                }
                else if(x1 == x2)
                {
                    unit[i][j].weight_avail = 'Y';
                    if (network.node[x1][y1].data == network.node[x2][y2].data )
                    {
                        unit[i][j].weight = penalty ;
                    }
                    else
                    {
                        unit[i][j].weight = bonus ;
                    }
                }
                else if (y1 == y2)
                {
                    unit[i][j].weight_avail = 'Y';
                    if (network.node[x1][y1].data == network.node[x2][y2].data )
                    {
                        unit[i][j].weight = penalty ;
                    }
                    else
                    {
                        unit[i][j].weight = bonus ;
                    }
                }
                else if (bx1 == bx2 && by1 == by2)
                {
                    if(unit[i][j].weight_avail != 'Y'){
                    unit[i][j].weight_avail = 'Y';
                    if (network.node[x1][y1].data == network.node[x2][y2].data )
                    {
                        //System.out.println("for block i :"+i+"j :"+j);
                        unit[i][j].weight = penalty ;
                    }
                    else
                    {
                        unit[i][j].weight = bonus ;
                    }
                   }
                }
            }//for j
        }// for int 
        return this;
    }
    
    public void showWeight()
    {
       for(int i=1;i<=weight_dimension;i++)
       {
           for(int j=1;j<=weight_dimension;j++)
           {
               System.out.println("i :"+i+" j :"+j+" weight :"+this.unit[i][j].weight);
           }
       }
    
    }
    
    public int xaxis(int i)
    {
        return ((i-1)/network_dimension)+1;
    }
    
    public int yaxis(int i)
    {
        return ((i-1)%network_dimension)+1;
    }
    
    public int block(int i)
    {
        int root = (int)Math.sqrt(network_dimension);
        int diff = root - (i%root);
        if (diff == root)
        {
            diff = 0;
        }
        return ((i+diff)/root);
    }
    
    public float totalEnergy()
    {
        
        for(int i=1;i<=weight_dimension;i++)
        {
            for(int j=1;j<=weight_dimension;j++)
            {
                total_energy = total_energy + unit[i][j].weight;
            }
           // System.out.println("i :"+i+ " energy :"+total_energy);
        }
        
        total_energy = total_energy/2;
        return total_energy;
    }
    
    public float idealEnergy(int bonus)
    {
        float no_of_neighbors = (network_dimension-1)+2*(network_dimension - (float)Math.sqrt(network_dimension));
        float E_ideal = ((network_dimension * network_dimension) * (bonus * no_of_neighbors))/2;
        return E_ideal;
    }
    
    
    
    
    
}



class Node
{
    public char data;
    public boolean clamped;
}



class Network
{
    Node node[][];
    int dimension;
    public Network(int n)
    {
        dimension = n;
        node = new Node[dimension+1][dimension+1];
        for(int i=1;i<=dimension;i++)
        {
            for(int j=1;j<=dimension;j++)
            {
                node[i][j] = new Node();
            }
        }
    }// end of constructor
    
    public void makeNetwork(char input,int i,int j,boolean cl)
    {
        node[i][j].data = input;
        node[i][j].clamped = cl;
    }
    
    public void showNetwork()
    {
        for(int i=1;i<=dimension;i++)
        {
            for(int j=1;j<=dimension;j++)
            {
                System.out.print(node[i][j].data) ;
                System.out.println(node[i][j].clamped);
            }
        }
    }
    
    public Network Fillup()
    {
        for(int i=1;i<=dimension;i++)
        {
            for(int j=1;j<=dimension;j++)
            {
                if(this.node[i][j].data == '*')
                {   
                    int rand;
                    Random r = new Random();
                    do{
                    rand = r.nextInt(dimension);
                    }while(rand == 0);
                    this.node[i][j].data = Character.forDigit(rand,10);
                    this.node[i][j].clamped = false;
                }
            }
        }
        return this;
    }
    
}


 class Boltzmann {
    
    
    /** Creates a new instance of Boltzmann */
    public Boltzmann() {
    }
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) throws IOException{
        // TODO code application logic here
         
         int dimension;
         int penalty;
         int bonus;
         int alpha;
         int beta;
         int initial_temperature;
         float total_energy;
         float ideal_energy;
         int rand1;
         int rand2;
         int rand3;
         Random r1 = new Random();
         
         String temp;
         
         BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
         Initialize initialize = new Initialize();
         Network accepted_Network;
         Network temporary_Network;
         Weight accepted_Weight;
         Weight temporary_Weight;
         
         System.out.println("Enter the dimension");
         temp = br.readLine();
         dimension = Integer.parseInt(temp);
         
         System.out.println("Enter the penalty");
         temp = br.readLine();
         penalty = Integer.parseInt(temp);
         
         System.out.println("Enter the bonus");
         temp = br.readLine();
         bonus = Integer.parseInt(temp);
         
         System.out.println("Enter the alpha");
         temp = br.readLine();
         alpha = Integer.parseInt(temp);
         
         System.out.println("Enter the beta");
         temp = br.readLine();
         beta = Integer.parseInt(temp);
         
         System.out.println("Enter the initial_temperature");
         temp = br.readLine();
         initial_temperature = Integer.parseInt(temp);
         
         System.out.println(dimension+" "+penalty+" "+bonus);
         System.out.println("Finished");
         
         //make the first network
         accepted_Network = initialize.formNetwork(dimension);
         System.out.println("Showing network");
         accepted_Network.showNetwork();
         
         //Fill up initail Network
         accepted_Network = initialize.Fillup(accepted_Network);
         System.out.println("After fill up");
         accepted_Network.showNetwork();
         
         //Make Initial weight
         System.out.println("Starting weight formation");
         accepted_Weight = initialize.formWeight(dimension,accepted_Network,penalty,bonus);
         System.out.println("Show weight");
         accepted_Weight.showWeight();
         total_energy = accepted_Weight.totalEnergy();
         ideal_energy = accepted_Weight.idealEnergy(bonus);
         System.out.println("total :"+total_energy);
         System.out.println("ideal :"+ideal_energy);
         int count = 0;
         do{
         do{
         rand1 = r1.nextInt(dimension);
         rand2 = r1.nextInt(dimension);
         rand3 = r1.nextInt(dimension);
         }while(rand1==0 || rand2==0 || rand3==0 || accepted_Network.node[rand1][rand2].clamped == true);         
         System.out.println(rand1+" "+rand2);
         accepted_Network.node[rand1][rand2].data =Character.forDigit(rand3,10);
         accepted_Weight = accepted_Weight.formWeight(accepted_Network,penalty,bonus);
         total_energy = accepted_Weight.totalEnergy();
         System.out.println("total :"+count+" :"+total_energy);
         }while(count++ < 100);         
         accepted_Network.showNetwork();         
  }
}
