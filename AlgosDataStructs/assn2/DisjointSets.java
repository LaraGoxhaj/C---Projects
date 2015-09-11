import java.io.*;
import java.util.*;

/****************************
*
* COMP251 template file
*
* Assignment 2, Question 1
*
*****************************/

public class DisjointSets {

    private int[] par;
    
    /* constructor: creates a partition of n elements. */
    /* Each element is a separate disjoint set */
    DisjointSets(int n) {
        if (n>0) {
            par = new int[n];
            for (int i=0; i<this.par.length; i++) {
                par[i] = i;
            }
        }
    }
    
    public String toString(){
        int pari,countsets=0;
        String output = "";
        String[] setstrings = new String[this.par.length];
        /* build string for each set */
        for (int i=0; i<this.par.length; i++) {
            pari = find(i);
            if (setstrings[pari]==null) {
                setstrings[pari] = String.valueOf(i);
                countsets+=1;
            } else {
                setstrings[pari] += "," + i;
            }
        }
        /* print strings */
        output = countsets + " set(s):\n";
        for (int i=0; i<this.par.length; i++) {
            if (setstrings[i] != null) {
                output += i + " : " + setstrings[i] + "\n";
            }
        }
        return output;
    }
    
    /* find representative of element i */
    /* path compression */
    public int find(int i) {
    	if (par[i] == i) return i;	// if parent of i is i, return i
    	else {						
    		par[i] = find(par[i]);	// else recursively find the parent of i and compress the path
    		return par[i];
    	}
    }

    /* merge sets containing elements i and j */
    /* root of tree containing i becomes child of root of tree containing j */
    /* return representative (as an integer) of the new merged set */
    public int union(int i, int j) {
    	int p0 = find(j);
    	int p1 = find(i);
    	if (p0 != p1) {		// if sets containing i and j do not have same rep
    		par[p1] = p0;	// make i's rep the child of j's rep
    	}
        return p0;			// return rep of the set
    }
    
    public static void main(String[] args) {
        
        DisjointSets myset = new DisjointSets(6);
        System.out.println(myset);
        System.out.println("-> Union 2 and 3");
        myset.union(2,3);
        System.out.println(myset);
        System.out.println("-> Union 2 and 3");
        myset.union(2,3);
        System.out.println(myset);
        System.out.println("-> Union 2 and 1");
        myset.union(2,1);
        System.out.println(myset);
        System.out.println("-> Union 4 and 5");
        myset.union(4,5);
        System.out.println(myset);
        System.out.println("-> Union 3 and 1");
        myset.union(3,1);
        System.out.println(myset);
        System.out.println("-> Union 2 and 4");
        myset.union(2,4);
        System.out.println(myset);
        
    }
}
