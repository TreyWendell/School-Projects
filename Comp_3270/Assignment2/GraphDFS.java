import java.util.*;

public class GraphDFS {
    // Adjacency list to represent the graph
    private Map<String, List<String>> graph = new HashMap<>();
    private int nodesVisited = 0; // Tracks the total nodes visited

    // Method to add an edge to the graph
    public void addEdge(String node1, String node2) {
        graph.computeIfAbsent(node1, k -> new ArrayList<>()).add(node2);
        graph.computeIfAbsent(node2, k -> new ArrayList<>()).add(node1); // Since it's undirected
    }

    // Method to compute distances and paths using DFS
    public Map<String, Result> calculateDistances(String startNode) {
        Map<String, Result> results = new HashMap<>();
        Set<String> visited = new HashSet<>();
        Map<String, String> parent = new HashMap<>(); // To reconstruct paths

        // Start traversal timer
        long traversalStart = System.nanoTime();

        // Perform DFS
        dfs(startNode, visited, parent, results);

        // Add the start node with its total time taken
        long totalTime = (System.nanoTime() - traversalStart) / 1000;
        results.get(startNode).timeTaken = totalTime;

        return results;
    }

    private void dfs(String currentNode, Set<String> visited, Map<String, String> parent, Map<String, Result> results) {
        visited.add(currentNode);
        nodesVisited++; // Increment nodes visited

        // Start time for this node
        long nodeStartTime = System.nanoTime();

        // Calculate the path back to N_0
        List<String> path = new ArrayList<>();
        String temp = currentNode;
        while (temp != null) {
            path.add(temp);
            temp = parent.get(temp);
        }
        Collections.reverse(path);

        // Record time taken for this node in microseconds
        long timeTaken = (System.nanoTime() - nodeStartTime) / 1000;

        // Save results for this node
        results.put(currentNode, new Result(nodesVisited, path, timeTaken));

        // Recursively visit all unvisited neighbors
        for (String neighbor : graph.getOrDefault(currentNode, new ArrayList<>())) {
            if (!visited.contains(neighbor)) {
                parent.put(neighbor, currentNode); // Set the parent for path reconstruction
                dfs(neighbor, visited, parent, results);
            }
        }
    }

    public static void main(String[] args) {
        // Create the graph
        GraphDFS graphDFS = new GraphDFS();

        // Define edges as per the graph in the image
        graphDFS.addEdge("N_0", "N_1");
        graphDFS.addEdge("N_1", "N_2");
        graphDFS.addEdge("N_2", "N_3");
        graphDFS.addEdge("N_1", "N_6");
        graphDFS.addEdge("N_6", "N_5");
        graphDFS.addEdge("N_5", "N_10");
        graphDFS.addEdge("N_10", "N_11");
        graphDFS.addEdge("N_11", "N_16");
        graphDFS.addEdge("N_6", "N_15");
        graphDFS.addEdge("N_15", "N_20");
        graphDFS.addEdge("N_20", "N_21");
        graphDFS.addEdge("N_6", "N_7");
        graphDFS.addEdge("N_7", "N_12");
        graphDFS.addEdge("N_12", "N_17");
        graphDFS.addEdge("N_17", "N_22");
        graphDFS.addEdge("N_22", "N_23");
        graphDFS.addEdge("N_12", "N_18");
        graphDFS.addEdge("N_18", "N_19");
        graphDFS.addEdge("N_19", "N_24");
        graphDFS.addEdge("N_12", "N_13");
        graphDFS.addEdge("N_13", "N_14");
        graphDFS.addEdge("N_13", "N_8");
        graphDFS.addEdge("N_8", "N_9");
        graphDFS.addEdge("N_9", "N_4");

        // Compute distances and their computation times from the starting node N_0
        Map<String, Result> results = graphDFS.calculateDistances("N_0");

        // Output the results
        System.out.println("Results for each node:");
        for (Map.Entry<String, Result> entry : results.entrySet()) {
            String node = entry.getKey();
            Result result = entry.getValue();
            System.out.println(node + " -> Nodes Visited: " + result.distance + ", Path: " + result.path +
                    ", Time Taken: " + result.timeTaken + " µs");
        }
    }

    // Helper class to store results for each node
    static class Result {
        int distance; // Total nodes visited
        List<String> path;
        long timeTaken; // Time in microseconds

        public Result(int distance, List<String> path, long timeTaken) {
            this.distance = distance;
            this.path = path;
            this.timeTaken = timeTaken;
        }
    }
}
