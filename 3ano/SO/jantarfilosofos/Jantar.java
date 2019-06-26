/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jantarfilosofos;

import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.concurrent.Semaphore;

/**
 *
 * @author rgm35043
 */
public class Jantar extends Thread{
    
    int fil;
    
    Jantar(int x)
    {
        this.fil = x;
    }
    
    public static void think(int a){
        Uteis.state[a]=Uteis.THINKING;
        System.out.println("O filosofo "+a+" está pensando!\n------------------------------");
        try {
            Thread.sleep(1000);
        } catch (InterruptedException ex) {
            Logger.getLogger(JantarFilosofos.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public static void Hungryyy(int i)
    {
       Uteis.state[i]=Uteis.HUNGRY; /* Registra que o filósofo está faminto */
       System.out.println("Filosofo "+i+" diz: ESTOU FAMINTOOOO!!!! \n -------------------------------");
      
    }
    
    public static void take_forks(int i) { 
        /* i: número do filósofo de 0 a N-1 */
        Uteis.mutex.down();/* Entra na região critica */
        Hungryyy(i);
        test(i); /* tenta pegar os dois garfos */
        Uteis.mutex.up();/* Sai da região crítica */
        Uteis.s[i].down(); /* Bloqueia se os garfos não foram pegos */
    }
    
    public static void test(int i) { /* i: número do filósofo de 0 a N-1 */

        int LEFT = (i+Uteis.N-1)%Uteis.N;
        int RIGHT = (i+1)%Uteis.N;
        
        if(Uteis.state[i]==Uteis.HUNGRY && Uteis.state[LEFT]!=Uteis.EATING && Uteis.state[RIGHT]!=Uteis.EATING){
            eat(i);
            Uteis.s[i].up();
        }
    }
    
    public static void eat(int i){
        
        Uteis.state[i]=Uteis.EATING;
        System.out.println("O filosofo "+i+" está COMENDO hmm!!\n----------------------------");
        try {
            Thread.sleep(i * 700);
        } catch (InterruptedException ex) {
            Logger.getLogger(JantarFilosofos.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public static void put_forks(int i) { /* i: número do filósofo de 0 a N-1 */
        int LEFT = (i+Uteis.N-1)%Uteis.N;
        int RIGHT = (i+1)%Uteis.N;

        Uteis.mutex.down();/* Entra na região critica */
        think(i);
        test(LEFT); /* vê se o vizinho da esquerda pode comer agora */
        test(RIGHT); /* vê se o vizinho pode comer agora */
        Uteis.mutex.up();/* Sai da região crítica */
        
    }
    
    public void run()
    {
        think(this.fil); /* Filósofo está pensando */
        while (true){
            take_forks(this.fil); /* Pega dois garfos ou bloqueia */
            try {
                Thread.sleep(this.fil * 700);
            } catch (InterruptedException ex) {
                Logger.getLogger(Jantar.class.getName()).log(Level.SEVERE, null, ex);
            }
            put_forks(this.fil); /* Devolve os dois garfos à mesa */
        } 
    }
    
}
