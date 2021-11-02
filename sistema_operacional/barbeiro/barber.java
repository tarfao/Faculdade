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

public class barber extends Thread {
    
    //static boolean cortando = false;
    //static boolean dormindo = false;
    
    public void cortarCabelo()
    {
        System.out.println("Cortando Cabelo");
        //cortando = true;
         try {
             Thread.sleep(3000);
             System.out.println("Terminou");
             //cortando = false;
             //Thread.sleep(1000);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    
    public void barbers()
    {
        while(true)
        {
            //System.out.println(Uteis.waiting);
            if(Uteis.waiting <= 0)
            {
                System.out.println("Dormindo");
                //dormindo = true;
                Uteis.customers.down();
            }else{
                Uteis.mutex.down();
                Uteis.waiting--;
                Uteis.barbers.up();
                Uteis.mutex.up();
                //dormindo = false;
                cortarCabelo();
            }
        }
    }
    
    public void run()
    {
        while(true)
        {
            barbers();
        }
    }
    /*static synchronized public void down() throws InterruptedException
    {
        synchronized(Uteis.b){
            if(Uteis.customers == 0)
            {

                Uteis.b.wait();
                Uteis.customers--;

            }else{
                Uteis.customers--;
            }
        }
    }*/
    
    
    
}
