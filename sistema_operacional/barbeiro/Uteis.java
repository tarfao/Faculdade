package barbeiro;

import java.util.concurrent.Semaphore;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author rgm35043
 */
public class Uteis {
    static int CADEIRAS = 5;
    static DormirAcordar customers = new DormirAcordar(0);
    static DormirAcordar barbers = new DormirAcordar(0);
    static DormirAcordar mutex = new DormirAcordar(1);
    static int waiting = 0;
    
    static barber b = new barber();
    static cliente c = new cliente();
}
