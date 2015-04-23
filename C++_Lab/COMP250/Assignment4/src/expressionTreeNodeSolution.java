import java.lang.*;

class expressionTreeNodeSolution {
    private String value;
    private expressionTreeNodeSolution leftChild, rightChild, parent;

    expressionTreeNodeSolution() {
        value = null; 
        leftChild = rightChild = parent = null;
    }

    // Constructor
    /* Arguments: String s: Value to be stored in the node
                  expressionTreeNodeSolution l, r, p: the left child, right child, and parent of the node to created      
       Returns: the newly created expressionTreeNodeSolution               
     */
    expressionTreeNodeSolution(String s, expressionTreeNodeSolution l, expressionTreeNodeSolution r, expressionTreeNodeSolution p) {
        value = s; 
        leftChild = l; 
        rightChild = r;
        parent = p;
    }

    /* Basic access methods */
    String getValue() { return value; }

    expressionTreeNodeSolution getLeftChild() { return leftChild; }

    expressionTreeNodeSolution getRightChild() { return rightChild; }

    expressionTreeNodeSolution getParent() { return parent; }


    /* Basic setting methods */ 
    void setValue(String o) { value = o; }

    // sets the left child of this node to n
    void setLeftChild(expressionTreeNodeSolution n) { 
        leftChild = n; 
        n.parent = this;    // refers to current expressionTreeNodeSolution
    }

    // sets the right child of this node to n
    void setRightChild(expressionTreeNodeSolution n) { 
        rightChild = n; 
        n.parent=this; // refers to current expressionTreeNodeSolution
    }


    // Returns the root of the tree describing the expression s
    // Watch out: it makes no validity checks whatsoever!
    expressionTreeNodeSolution(String s) {
        // check if s contains parentheses. If it doesn't, then it's a leaf
        if (s.indexOf("(")==-1) setValue(s);
        else {  // it's not a leaf

            /* break the string into three parts: the operator, the left operand,
               and the right operand. ***/
            setValue( s.substring( 0 , s.indexOf( "(" ) ) );
            // delimit the left operand 2008
            int left = s.indexOf("(")+1;
            int i = left;
            int parCount = 0;
            // find the comma separating the two operands
            while (parCount>=0 && !(s.charAt(i)==',' && parCount==0)) {
                if ( s.charAt(i) == '(' ) parCount++;
                if ( s.charAt(i) == ')' ) parCount--;
                i++;
            }
            int mid=i;
            if (parCount<0) mid--;

            // recursively build the left subtree
            setLeftChild(new expressionTreeNodeSolution(s.substring(left,mid)));

            if (parCount==0) {
                // it is a binary operator
                // find the end of the second operand.F13
                while ( ! (s.charAt(i) == ')' && parCount == 0 ) )  {
                    if ( s.charAt(i) == '(' ) parCount++;
                    if ( s.charAt(i) == ')' ) parCount--;
                    i++;
                }
                int right=i;
                setRightChild( new expressionTreeNodeSolution( s.substring( mid + 1, right)));
            }
        }
    }

    // Returns a copy of the subtree rooted at this node... 2014
    expressionTreeNodeSolution deepCopy() {
        expressionTreeNodeSolution n = new expressionTreeNodeSolution();
        n.setValue( getValue() );
        if ( getLeftChild()!=null ) n.setLeftChild( getLeftChild().deepCopy() );
        if ( getRightChild()!=null ) n.setRightChild( getRightChild().deepCopy() );
        return n;
    }

    // Returns a String describing the subtree rooted at a certain node.
    public String toString() {
        String ret = value;
        if ( getLeftChild() == null ) return ret;
        else ret = ret + "(" + getLeftChild().toString();
        if ( getRightChild() == null ) return ret + ")";
        else ret = ret + "," + getRightChild().toString();
        ret = ret + ")";
        return ret;
    } 


    // Returns the value of the expression rooted at a given node
    // when x has a certain value
    double evaluate(double x) throws Exception {
    	// if the tree contains only a single node (is a leaf) it contains only a value,
    	// which is to be returned; these are our base cases
        if (getLeftChild() == null && getRightChild() == null){
            if (value.equals("x")) return x;
            else return Double.parseDouble(value);
        }
        // else the tree is an expression, and we make recursive calls to evaluate on
        // the subtrees until a value is returned
        else {
            double firstOperand = getLeftChild().evaluate(x);
            double secondOperand = 0;
            // for unary operators, we assume that the operand is contained in the left child
            // and do not use secondOperand
            if (getRightChild() != null) secondOperand = getRightChild().evaluate(x);
            String operator = value;
            // a particular operation is performed depending on the value contained in the 
            // root of the current tree
            switch (operator) {
	            case "add":
	                return firstOperand + secondOperand;
	            case "sub":
	                return firstOperand - secondOperand;
	            case "mult":
	                return firstOperand * secondOperand;
	            case "sin":
	                return Math.sin(firstOperand);
	            case "cos":
	                return Math.cos(firstOperand);
	            case "exp":
	                return Math.exp(firstOperand);
	            default:
	                throw new Exception("Invalid operator");
            }
        }
    }                                                 

    /* returns the root of a new expression tree representing the derivative of the
       original expression */
    expressionTreeNodeSolution differentiate() throws Exception {
    	// we copy the original tree so that the method does not alter the original tree,
    	// preserving it for potential later use, and create a new copied tree
    	expressionTreeNodeSolution diffTree = this.deepCopy(); 	
    	expressionTreeNodeSolution left = diffTree.getLeftChild();
    	expressionTreeNodeSolution right = diffTree.getRightChild();
    	String diffValue = diffTree.getValue();
    	
    	// if the tree contains only a single node (is a leaf) it contains only a value,
    	// which is to be differentiated; these are our base cases
    	if (left == null && right == null){
            if (diffValue.equals("x")){
                diffTree.setValue("1");
            }
            else{
                diffTree.setValue("0");
            }
        }
    	// else the tree is an expression, and we make recursive calls to differentiate on
        // the subtrees until a value is returned
        else{
            expressionTreeNodeSolution firstOperand = left.differentiate();
            expressionTreeNodeSolution secondOperand = null;
            // for unary operators, we assume that the operand is contained in the left child
            // and do not use secondOperand
            if (right != null) secondOperand = right.differentiate();
            // a particular operation is performed depending on the value contained in the 
            // root of the current tree
            switch (diffValue) {
            	// addition and subtraction require the same set of changes to the new tree
	            case "add":
	            case "sub":
	            	diffTree.setLeftChild(firstOperand);
	            	diffTree.setRightChild(secondOperand);
	            	break;
	            // all other operators require a call to the constructor, which creates a new
	            // differentiated tree and assigns it to the new tree
	            case "mult":
	                diffTree = new expressionTreeNodeSolution("add(mult(" + right + "," + firstOperand + "),mult(" + left + "," + secondOperand + "))");
	                break;
	            case "sin":
	                diffTree = new expressionTreeNodeSolution("mult(" + firstOperand + ",cos(" + leftChild + "))");
	                break;
	            case "cos":
	            	diffTree = new expressionTreeNodeSolution("sub(0,mult(" + firstOperand + ",sin(" + leftChild + ")))");
	                break;
	            case "exp":
	            	diffTree = new expressionTreeNodeSolution("mult(" + firstOperand + ",exp(" + leftChild + "))");
	                break;
	            default:
	                throw new Exception("Invalid operator");
            }
        }
        return diffTree;
    }


    public static void main(String args[]) throws Exception {
    	expressionTreeNodeSolution e = new expressionTreeNodeSolution("mult(add(2,x),cos(x))");
        System.out.println(e);
        System.out.println(e.evaluate(1));
        System.out.println(e.differentiate());
    }
}