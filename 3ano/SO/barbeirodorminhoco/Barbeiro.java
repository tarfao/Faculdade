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
public class Barbeiro extends Thread {
     static final int CADEIRAS = 5;
    static Semaforo cliente = new Semaforo(0);//Esperando para cortar
    static Semaforo barbeiro = new Semaforo(0);//Cortando ou dormindo
    static Semaforo mutex = new Semaforo(1);//Exclusão mútua
    static int waiting = 0;
    //int i = 0;
    static boolean cortando = false;
    static boolean dormindo = false;
    //FrmBarbeiroDorminhoco fbd = new FrmBarbeiroDorminhoco();
    
    public void cortarCabelo() {
        System.out.println("Cortando cabelo");
        cortando = true;
        try {
            Thread.sleep(1000); 
            System.out.println("Terminou");
            cortando = false;
            Thread.sleep(1000);
        }
        catch(Exception e){e.printStackTrace();}
    }
    
    public void barbers() {
            while(true) {
                System.out.println(waiting);
                if(waiting <= 0) {
                    System.out.println("Dormindo");
                    dormindo = true;
                    cliente.down();
                } else {
                    mutex.down();
                    waiting --;
                    barbeiro.up();
                    mutex.up();
                    dormindo = false;
                    cortarCabelo();
                }
            }
    }
    
    public void run() {
        while(true) {
            //customers();
            barbers();
        }
    }
}
