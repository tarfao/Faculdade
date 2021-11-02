/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

package jantarfilosofos;

import java.util.concurrent.Semaphore;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author rgm35043
 */
public class JantarFilosofos {
   
    
    /**
     * @param args the command line arguments
     */
    
    
    public static void main (String[] argc) {
        
        //Inicializando semaforo de todos os Filósofos
        for (int i = 0; i < Uteis.N; i++)
        {
            Uteis.state[i] = 0;
            Uteis.s[i] = new Semaforo(0);
            Uteis.f[i] = new Jantar(i);
            Uteis.f[i].start();
        }
        
        
        
       
    }
    
}
