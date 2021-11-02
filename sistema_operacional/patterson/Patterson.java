/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package patterson;

/**
 *
 * @author fpperez
 */
public class Patterson {
    
    
    
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Uteis.p = new produtor();
        Uteis.c = new consumidor();
        
        Uteis.p.start();
        Uteis.c.start();
        
        Uteis.mostra.setVisible(true);
                
    }
    
}
