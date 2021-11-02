/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jantarfilosofos;

import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author rgm35043
 */
public class SemaforoX {
    int value;

    public SemaforoX(int x) {
        this.value = x;
    }
    
    @SuppressWarnings("empty-statement")
    public synchronized void down()
    {
        while(this.value <= 0){
            try {
                wait(1000);
            } catch (InterruptedException ex) {
                Logger.getLogger(SemaforoX.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        this.value--;
    }
    
    public synchronized void up() {
        ++this.value;
        if(this.value - 1 <= 0)
        {
            notify();
        }
    }
    
}
