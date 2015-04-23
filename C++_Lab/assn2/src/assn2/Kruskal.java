package assn2;
import java.util.*;

public class Kruskal{

	/* takes a graph object of class WGraph as input, returns another WGraph object
	 * which will be the MST of the input graph */
    public static WGraph kruskal(WGraph g){
    	WGraph w = new WGraph();							// instantiate a new empty graph
    	
    	int nodes = g.getNbNodes();							// # nodes of graph
    	DisjointSets V = new DisjointSets(nodes);			// initialise a set V of #nodes empty disjoint sets for g 
    	ArrayList<Edge> edgeList = g.listOfEdgesSorted();	// sort edges of graph into nondecreasing order by weight
    														// thus assure that first edges put into g are of least weight
    	for (Edge e : edgeList) {							// iterate through edges
    		if (IsSafe(V, e)) 	w.addEdge(e);				// add safe edge to the newly instantiated graph
    	}
    	return w;
    }

    /* considers a partition of the nodes p and and edge e
     * returns TRUE if safe to add edge e to MST, FALSE otherwise */
    public static Boolean IsSafe(DisjointSets p, Edge e){
    	int u = e.nodes[0];									// endpoints of each edge
    	int v = e.nodes[1];
    	if (p.find(u) != p.find(v)) {						// if each node is not in the node of the edge is not in the same component
    		p.union(u, v);									// unify the components in Disjoint sets
    		return true;									// the edge is safe to add
    	}
    	else return false;
    }

    public static void main(String[] args){

        String file = args[0];
        WGraph g = new WGraph(file);
        WGraph t = kruskal(g);
        System.out.println(t);

   } 
}