import java.util.*;



public class BellmanFord{
	
    private int[] distances;
    private int[] predecessors;
    private int source;


    BellmanFord(WGraph g, int source) throws Exception {
    	 /* Constructor, input a graph and a source
         * Computes the Bellman Ford algorithm to populate the
         * attributes 
         *  distances - at position "n" the distance of node "n" to the source is kept
         *  predecessors - at position "n" the predecessor of node "n" on the path
         *                 to the source is kept
         *  source - the source node
         *
         *  If the node is not reachable from the source, the
         *  distance value must be Integer.MAX_VALUE
         */
    	
    	distances = new int [g.getNbNodes()];		// contains immediate shortest-path estimates
    	predecessors = new int [g.getNbNodes()];	// contains immediate predecessor estimates
    	
    	distances[source] = 0;
    	// initialize distances to infinity
    	for (int i = 1; i < distances.length; i++) {
    		distances[i] = Integer.MAX_VALUE;
    	}
    	predecessors[source] = source;
    	
    	ArrayList<Edge> edges = g.getEdges();
    	    	
    	// relax edges
   		for (Edge e : edges) {
			if (distances[e.nodes[1]] > (distances[e.nodes[0]] + e.weight)) {
				distances[e.nodes[1]] = distances[e.nodes[0]] + e.weight;
				predecessors[e.nodes[1]] = e.nodes[0];
			}
   		}

    	// throw exception if a negative-weight cycle is found
    	for (Edge e : edges) {
    		if (distances[e.nodes[1]] > distances[e.nodes[0]] + e.weight)
    			throw new Exception("The graph contains a cycle");
    	}
    	
    }
    
    

    public int[] shortestPath(int destination) throws Exception {
        /*Returns the list of nodes along the shortest path from 
         * the object source to the input destination
         * If no path exists an Error is thrown
         */
    	
    	// throw exception if path DNE
       	if (this.distances[destination] == Integer.MAX_VALUE)
    		throw new Exception("The node is unreachable from the source");
       	

       	Stack<Integer> path = new Stack<Integer>();			// holds node path
       	path.push(destination);
       	
       	int added = 1;
       	
       	// construct integer path
       	int current = destination;
       	while (current != source) {
       		current = predecessors[current];
       		path.add(current);
       		added++;
       	}
       	
       	// store integer path in array
       	int[] toRet = new int[added];
       	for (int i = 0; i < added; i++) {
       		toRet[i] = path.pop();
       	}
       	
        return toRet;
    }

    public void printPath(int destination){
        /*Print the path in the format s->n1->n2->destination
         *if the path exists, else catch the Error and prints it
         */
        try {
            int[] path = this.shortestPath(destination);
            for (int i = 0; i < path.length; i++){
                int next = path[i];
                if (next == destination){
                    System.out.println(destination);
                }
                else {
                    System.out.print(next + "-->");
                }
            }
        }
        catch (Exception e){
            System.out.println(e);
        }
    }

    public static void main(String[] args){
        String file = args[0];
        WGraph g = new WGraph(file);
        try{
            BellmanFord bf = new BellmanFord(g, g.getSource());
            bf.printPath(g.getDestination());
        }
        catch (Exception e){
            System.out.println(e);
        }

   } 
}