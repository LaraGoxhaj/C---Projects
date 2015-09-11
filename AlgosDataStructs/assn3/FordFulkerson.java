import java.io.*;
import java.util.*;

public class FordFulkerson {

	
	public static ArrayList<Integer> getNeighbors(Integer current, WGraph graph){
		
		ArrayList<Edge> edges = graph.listOfEdgesSorted();
		ArrayList<Integer> neighbors = new ArrayList<Integer>();
		
		for (int i = 0; i < edges.size(); i++) {
			if (edges.get(i).nodes[0] == current) {
				neighbors.add(0, edges.get(i).nodes[1]);
			}
		}

		return neighbors;
	}
	
	
	
	public static ArrayList<Integer> pathDFS(Integer source, Integer destination, WGraph graph){
		
		ArrayList<Integer> Stack = new ArrayList<Integer>();
		
		Stack<Integer> path = new Stack<Integer>();
		ArrayList<Integer> neighbors = new ArrayList<Integer>();
		ArrayList<Integer> visited = new ArrayList<Integer>();

		Integer current = source;
		path.push(current);

		// if no paths left, break out of loop
		while(!path.isEmpty()) {
			current = path.pop();
			
			// if current node not on stack, add it to the visited array
			if (!visited.contains(current)) {
				visited.add(current);
			}
			
			// if reached destination, end;
			if (current == destination) {
				break;
			}
			
			neighbors = FordFulkerson.getNeighbors(current, graph);
			
			// add all unvisited, weighted neighbors to stack
			for (int i = 0; i < neighbors.size(); i++) {
				if (!visited.contains(neighbors.get(i))) {
					if (graph.getEdge(current, neighbors.get(i)).weight != 0)
						path.push(neighbors.get(i));
				}
			}
			
		}
		
		for (int i = visited.size()-1; i > 0; i--) {
			if (graph.getEdge(visited.get(i-1), visited.get(i)) == null) {
				visited.remove(i-1);
			}
		}
		
		if (visited.get(visited.size()-1) == destination) {
			for (int i = 0; i < visited.size()-1; i++) {
				if (graph.getEdge(visited.get(i), visited.get(i+1)) != null) {
					int weight = graph.getEdge(visited.get(i), visited.get(i+1)).weight;
					if (weight != 0) {
						Stack.add(visited.get(i));
					}
				}
				else {
					visited.remove(i+1);
				}
			}
			Stack.add(destination);
		}
		
		return Stack;
	}
	

/*	
	public static ArrayList<Integer> pathDFS(Integer source, Integer destination, WGraph graph){
		ArrayList<Integer> Stack = new ArrayList<Integer>();
		ArrayList<Edge> edgeList = graph.listOfEdgesSorted();
		boolean[] visited = new boolean[graph.getNbNodes()];
		
		for (int i = 0; i < graph.getNbNodes(); i++) {
			if (i == source) {
				visited[i] = true;
			}
			else {
				visited[i] = false;
			}
		}
		
		Integer current = source;
		Stack.add(current);
		
		while (current != destination) {
			
			int added = 0;
			
			for (Edge x : edgeList) {
				System.out.println("current: " + current);
				if (x.nodes[0] == current && visited[x.nodes[1]] == false) {
					added++;
					current = x.nodes[1];
					visited[current] = true;
					Stack.add(current);
				}
			}
			
			if (added == 0) {
				current = Stack.remove(Stack.size()-1);
				if (current == source) {
					break;
				}
			}
		}
		
		
		

		boolean started = false;
		// build up the path in the stack 
		Integer current = source;
		while (current != destination) {
			System.out.print("current: " + current + " ");
			int validNeighbors = 0;					// marker 
			for (Edge x : edgeList) {
				started = true;
				System.out.print("(" + x.nodes[0] + "," + x.nodes[1] + ")  ");
				if (x.nodes[0] == current) {/// && !(visited[current])) {// && !edgeStack.contains(x)) {			// get neighbor edges that do not create a cycle
					validNeighbors++;				// update marker
					edgeStack.push(x);				// push edge onto stack
					current = x.nodes[1];			// update current
					System.out.println("?: " + visited[current]);
					visited[current] = true;
					//break;
				}
				System.out.println();
				System.out.println("N" + validNeighbors);
				if (validNeighbors == 0) {				// if current edge has no neighbors
					if (current == source) 				// if we've returned to the source, no valid path exists
						return Stack;					// return empty list						
					current = edgeStack.pop().nodes[0];	// else pop edge, set current back a step
					System.out.println("pop: " + current);
				}
			}
		}
		System.out.println();
		
		
		// build up stack
		Stack.add(source);
		while (!edgeStack.isEmpty()) {
			Stack.add(edgeStack.removeLast().nodes[1]);
		}
		
		
		//build up stack
		while (!pathStack.isEmpty()) {
			Stack.add(pathStack.removeLast());
		}
		
		
		return Stack;
	}
	*/
	
	
	public static void fordfulkerson(Integer source, Integer destination, WGraph graph, String filePath){
		String answer="";
		String myMcGillID = "260574574"; 				// Please initialize this variable with your McGill ID
		int maxFlow = 0;								// Initialize max flow to 0
		// assume initial flow on all edges = 0
		
		// residual graph contains flows
		WGraph res = new WGraph(graph);	
		ArrayList<Integer> path = pathDFS(source, destination, res);
		
		while (!path.isEmpty()) {
		
			int min = res.getEdge(path.get(0), path.get(1)).weight;
			
			// find bottleneck
			for (int i = 1; i < path.size()-1; i++) {
				int n0 = path.get(i);
				int n1 = path.get(i+1);
				if (res.getEdge(n0,n1).weight < min)
					min = res.getEdge(n0,n1).weight;
			}
			
			maxFlow += min;
			
			// augment original and residual graphs
			for (int i = 0; i < path.size()-1; i++) {
				int n0 = path.get(i);
				int n1 = path.get(i+1);
				
				// augment residual graph (holds max flows)
				//res.setEdge(n0, n1, graph.getEdge(n0,n1).weight - min);
				
				// augment residual graph (holds flows)				
				if (graph.getEdge(n0, n1) != null) {			// forward edge
					graph.setEdge(n0, n1, graph.getEdge(n0, n1).weight - min);
					res.setEdge(n0, n1, min);
				}
				else {											
					if (graph.getEdge(n0, n1).weight != 0) {	// backward edge
						Edge e = new Edge(n1, n0, res.getEdge(n0, n1).weight - min);
						res.addEdge(e);
					}
				}
			}
		
			path = pathDFS(source, destination, graph);
		}
		
		ArrayList<Edge> edges = graph.listOfEdgesSorted();
		for (Edge e : edges) {
			int w = res.getEdge(e.nodes[0], e.nodes[1]).weight;
			graph.setEdge(e.nodes[0], e.nodes[1], w);
		}
		
		
		
		answer += maxFlow + "\n" + graph.toString();	
		writeAnswer(filePath+myMcGillID+".txt",answer);
		System.out.println(answer);
	}
	
	
	public static void writeAnswer(String path, String line){
		BufferedReader br = null;
		File file = new File(path);
		// if file doesnt exists, then create it
		
		try {
		if (!file.exists()) {
			file.createNewFile();
		}
		FileWriter fw = new FileWriter(file.getAbsoluteFile(),true);
		BufferedWriter bw = new BufferedWriter(fw);
		bw.write(line+"\n");	
		bw.close();
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (br != null)br.close();
			} catch (IOException ex) {
				ex.printStackTrace();
			}
		}
	}
	
	 public static void main(String[] args){
		 File here = new File(".");
		 System.out.println(here.getAbsolutePath());
		 String file = args[0];
		 File f = new File(file);
		 WGraph g = new WGraph(file);
		 fordfulkerson(g.getSource(),g.getDestination(),g,f.getAbsolutePath().replace(".txt",""));
	 }
}
