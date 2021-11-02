/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package jantarfilosofos;

import java.util.concurrent.Semaphore;

/**
 *
 * @author rgm35043
 */
public class Uteis {
    static final int N = 5;
    static int THINKING = 0;
    static int HUNGRY = 1;
    static int EATING = 2;
    static int state[] = new int[N];
    public static Semaforo mutex = new Semaforo(1);
    static Semaforo[] s = new Semaforo[N]; //Um semáforo para cada filósofo 
    
    static Jantar[] f = new Jantar[N];
    
}
