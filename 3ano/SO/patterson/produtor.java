/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package patterson;
import java.util.Random;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author fpperez
 */
public class produtor extends Thread {
    static Random gerador = new Random();
    
    static synchronized void regiaoCritica()
    {
        Uteis.BUFFER[Uteis.N] = gerador.nextInt(30);
        System.out.println("Produzi "+Uteis.BUFFER[Uteis.N]);
        Uteis.N++;
        if(Uteis.N == 1)
            synchronized(Uteis.c){
                Uteis.c.notifyAll();   
            }
    }
    
    public void regiaoNCritica ()
    {
        Random gera = new Random();
        
        try {
            Thread.sleep((gera.nextInt(5)+ 1)*1000);
        } catch (InterruptedException ex) {
            Logger.getLogger(produtor.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    @Override
    public void run() {
        while (true) {
            Uteis.mostra.produtor();
            regiaoCritica();
            regiaoNCritica();
            /*System.out.println("Produtor");
            try {
                Thread.sleep(2000);
            } catch (InterruptedException ex) {
                Logger.getLogger(produtor.class.getName()).log(Level.SEVERE, null, ex);
            }
            synchronized (Uteis.c) {
                Uteis.c.notifyAll();
            }*/
        }
    }
}
