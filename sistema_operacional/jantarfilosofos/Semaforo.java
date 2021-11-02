/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jantarfilosofos;

/**
 *
 * @author rgm35043
 */
public class Semaforo {
    private int value;
    
    public Semaforo ()
    {
        this.value = 0;
    }
    
    public Semaforo(int v)
    {
        this.value = v;
    }
    
    public int getValue()
    {
        return this.value;
    }
    
    public synchronized void down()
    {
        while(this.value == 0)
        {
            try {
                wait();
            } catch (Exception e) {
            }
        }
        this.value--;
    }
    
    public synchronized void down(int x)
    {
        while(this.value == 0)
        {
            try {
                wait();
            } catch (InterruptedException e) {
            }
        }
        this.value--;
    }
    
    public synchronized void up() {
        this.value++;
        notify(); //acorda proccesso
    }
    
    public synchronized void up(int x) {
        this.value++;
        notify(); //acorda proccesso
    }
    
}
