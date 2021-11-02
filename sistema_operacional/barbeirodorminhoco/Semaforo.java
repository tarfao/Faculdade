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
public class Semaforo {
    
    private int value;

    public Semaforo(int v) {
        value = v;
    }

    public synchronized void down() {
        while (value <= 0) {
            try {
                wait();
            } catch (Exception e) {
                System.out.println("Erro na espera");
            }
        }
        value--;
    }

    public synchronized void up() {
        ++value;
        notify(); //acorda proccesso
}
    
}
