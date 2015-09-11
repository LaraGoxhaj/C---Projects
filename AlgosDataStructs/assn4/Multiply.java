import java.util.*;
import java.io.*;

public class Multiply{

    private static int randomInt(int size) {
        int maxval = (1 << size) - 1;
        return (int)(Math.random()*maxval);
    }
    
    /* naive, Karatsuba:
     * size - size of integers x and y that is defined as number of bits used to encode them
     * we assume x and y have the same size;
     * result[0] = result of multiplication
     * result[1] = size of ints (bits) * number of operations + costs from recursive calls
     */
    
    public static int[] naive(int size, int x, int y) {
    	int[] result = new int[2];
    	
    	// base case
    	if (size == 1) {
    		result[0] = x * y;
    		result[1] = 1;
    	}
    	
    	else {   	
	    	int m = (int) Math.ceil(size / 2.0);
	    	// use bit-shifting to compute the 4 terms
	    	int a = (int) Math.floor(x >> m);
	    	int b = (int) (x % Math.pow(2, m));
	    	if (b < 0)
	    		b += Math.pow(2, m);
	    	int c = (int) Math.floor(y >> m);
	    	int d = (int) (y % Math.pow(2, m));
	    	if (d < 0)
	    		d += Math.pow(2, m);
	    	
	    	int[] temp = naive(m, a, c);
	    	int e = temp[0];
	    	result[1] += temp[1];
	    	
	    	temp= naive(m, b, d);
	    	int f = temp[0];
	    	result[1] += temp[1];
	    	
	    	temp = naive(m, b, c);
	    	int g = temp[0];
	    	result[1] += temp[1];
	    	
	    	temp = naive(m, a, d);
	    	int h = temp[0];
	    	result[1] += temp[1];
	    	
	    	result[0] = (int) (Math.pow(2, 2*m) * e + Math.pow(2, m) * (g + h) + f);
	    	result[1] += 3*m;
    	}
    	
    	return result;
    }

    public static int[] karatsuba(int size, int x, int y) {
    	int[] result = new int[2];
    	
    	// base case
    	if (size == 1) {
    		result[0] = x * y;
    		result[1] = 1;
    	}
    	
    	// induction case
    	else {   	
	    	int m = (int) Math.ceil(size / 2.0);
	    	// use bit-shifting to compute the 4 terms
	    	int a = (int) Math.floor(x >> m);
	    	int b = (int) (x % Math.pow(2, m));
	    	if (b < 0)
	    		b += Math.pow(2, m);
	    	int c = (int) Math.floor(y >> m);
	    	int d = (int) (y % Math.pow(2, m));
	    	if (d < 0)
	    		d += Math.pow(2, m);

	    	int[] temp = karatsuba(m, a, c);
	    	int e = temp[0];
	    	result[1] += temp[1];
	    	
	    	temp = karatsuba(m, b, d);
	    	int f = temp[0];
	    	result[1] += temp[1];
	    	
	    	temp = karatsuba(m, a-b, c-d);
	    	int g = temp[0];
	    	result[1] += temp[1];

	    	result[0] = (int) (Math.pow(2, 2*m) * e + Math.pow(2, m) * (e + f - g) + f);
	    	result[1] += 6*m;
    	}
    	
    	return result;
    }
    
    public static void main(String[] args){

        try{
            int maxRound = 20;
            int maxIntBitSize = 16;
            for (int size=1; size<maxIntBitSize; size++) {
                int sumOpNaive = 0;
                int sumOpKaratsuba = 0;
                for (int round=0; round<maxRound; round++) {
                    int x = randomInt(size);
                    int y = randomInt(size);
                    int[] resNaive = naive(size,x,y);
                    int[] resKaratsuba = karatsuba(size,x,y);
            
                    if (resNaive[0] != resKaratsuba[0]) {
                        throw new Exception("Return values do not match! (x=" + x + "; y=" + y + "; Naive=" + resNaive[0] + "; Karatsuba=" + resKaratsuba[0] + ")");
                    }
                    
                    if (resNaive[0] != (x*y)) {
                        int myproduct = x*y;
                        throw new Exception("Evaluation is wrong! (x=" + x + "; y=" + y + "; Your result=" + resNaive[0] + "; True value=" + myproduct + ")");
                    }
                    
                    sumOpNaive += resNaive[1];
                    sumOpKaratsuba += resKaratsuba[1];
                }
                int avgOpNaive = sumOpNaive / maxRound;
                int avgOpKaratsuba = sumOpKaratsuba / maxRound;
                System.out.println(size + "," + avgOpNaive + "," + avgOpKaratsuba);
            }
        }
        catch (Exception e){
            System.out.println(e);
        }

   } 
}