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
public class DormirAcordar {
    
    private int valor;
    
    public DormirAcordar(int v)
    {
        this.valor = v;
    }
    
    public synchronized void down()
    {
        while(valor <= 0)
        {
            try {
                wait();
            } catch (Exception e) {
            }
        }
        valor--;
    }
    
    public synchronized void up() {
        ++valor;
        notify(); //acorda proccesso
    }
}
