import java.util.*;
class ex{
	
	   // for recurse(3) it would take all of the recurse(2) sequences (1, 12, 2) and then it would take
	   // them again and add itself (3) to all of them so you would get (13, 123, 23) and then at the end
	   // you add itself to the list (3). So when you add them all together you get (1, 12, 2, 13, 123, 23, 3)
	
    public static ArrayList<String> foo(int n){
    	ArrayList<String> a = new ArrayList<String>();
    	Integer i = new Integer(n);
    	
        if(n==1){											//base case
            a.add("1");
            return a;
        }
        
        ArrayList<String> withOutN = foo(n-1);
        ArrayList<String> out = new ArrayList<String>();
        Iterator<String> it = withOutN.iterator();
        
        while(it.hasNext()){
            String s = it.next();
            out.add(s);
            s = s.concat("," + i.toString());
            out.add(s);
        }
        
        out.add(i.toString());
        return out;
    }

    public static void main(String[] args){
        int n=4;
        ArrayList<String> out = new ArrayList<String>();

        out = (ArrayList<String>) foo(n);

       for (int k=0; k<out.size(); k++){
        	System.out.println(out.get(k));
        }

    }
}