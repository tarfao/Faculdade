/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package patterson;

import java.util.logging.Level;
import java.util.logging.Logger;
import static patterson.Uteis.N;
import java.util.Random;

/**
 *
 * @author fpperez
 */
public class consumidor extends Thread {

    public synchronized void regiaoCritica()
    {
        if(Uteis.N > 0){
            System.out.println("Consumi "+Uteis.BUFFER[Uteis.N-1]);
            Uteis.N--;
        }else{
            try {
                Uteis.c.wait();
            } catch (InterruptedException ex) {
                Logger.getLogger(consumidor.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
    }
    
    public void regiaoNCritica()
    {
        Random gerador = new Random();
        
        try {
            Thread.sleep((gerador.nextInt(5)+ 1)*1000);
        } catch (InterruptedException ex) {
            Logger.getLogger(consumidor.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
          
    
    @Override
    public void run() {
        while (true) {
            Uteis.mostra.consumidor();
            regiaoCritica();
            regiaoNCritica();
            
            /*System.out.println("Consumidor");
            try {
                Thread.sleep(500);
                synchronized (Uteis.c) {
                    Uteis.c.wait();
                }
            } catch (InterruptedException ex) {
                Logger.getLogger(consumidor.class.getName()).log(Level.SEVERE, null, ex);
            }*/

        }
    }
}
