/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package barbeiro;

/**
 *
 * @author rgm35043
 */
public class cliente extends Thread {
    
    public synchronized void customers()
    {
        Uteis.mutex.down();
        
        if(Uteis.waiting < Uteis.CADEIRAS)
        {
            Uteis.waiting++;
            Uteis.customers.up();
            Uteis.mutex.up();
            System.out.println("Cheguei \n Clientes = "+Uteis.waiting);
        }else {
            System.out.println("----------\nCadeiras cheias\n----------");
            Uteis.mutex.up();
        }
        
    }
    
    public void run()
    {
        while(true) {
            customers();
            
            try {
                Thread.sleep((long) (Math.random() * 3000));
            } catch (InterruptedException ex) {
                System.err.print(ex);
            }
        }
    }
}
