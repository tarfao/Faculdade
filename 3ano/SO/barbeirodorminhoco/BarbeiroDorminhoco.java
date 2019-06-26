/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package barbeirodorminhoco;

import java.awt.Color;
import java.awt.HeadlessException;
import javax.swing.JOptionPane;

/**
 *
 * @author tarfao
 */
public class BarbeiroDorminhoco extends javax.swing.JFrame {
    static Barbeiro barbe = new Barbeiro();
    static Clientes clie = new Clientes();
    
    public static void main(String[] args) {
        clie.start();
        barbe.start();
    }
    
    
}
