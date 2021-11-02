/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package barbeirodorminhoco;

/**
 *
 * @author tarfao
 */
public class Clientes extends Thread {
    public void customers() {
        Barbeiro.mutex.down();
        
        if(Barbeiro.waiting < Barbeiro.CADEIRAS) {
            Barbeiro.waiting ++;
            Barbeiro.cliente.up();
            Barbeiro.mutex.up();
            //Barbeiro.down();
        } else {
            Barbeiro.mutex.up();
        }
    }
    public void run() {
        while(true) {
            customers();
            
            try {
                System.out.println("Cliente +");
                Thread.sleep((long) (Math.random() * 8000));
            } catch (InterruptedException ex) {
                System.err.print(ex);
            }
        }
}
}
