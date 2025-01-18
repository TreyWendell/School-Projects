import java.util.*;

public class GraphBFS {
    // Adjacency list to represent the graph
    private Map<String, List<String>> graph = new HashMap<>();

    // Method to add an edge to the graph
    public void addEdge(String node1, String node2) {
        graph.computeIfAbsent(node1, k -> new ArrayList<>()).add(node2);
        graph.computeIfAbsent(node2, k -> new ArrayList<>()).add(node1); // Since it's undirected
    }

    // Method to compute distances and paths using BFS
    public Map<String, Result> calculateDistances(String startNode) {
        Map<String, Result> results = new HashMap<>();
        Queue<String> queue = new LinkedList<>();
        Set<String> visited = new HashSet<>();
        Map<String, String> parent = new HashMap<>(); // To reconstruct the path

        // Initialize BFS
        queue.add(startNode);
        visited.add(startNode);

        // To count total nodes visited so far
        int nodesVisited = 0;

        // Start traversal timer
        long traversalStart = System.nanoTime();

        while (!queue.isEmpty()) {
            String current = queue.poll();
            nodesVisited++;

            // Start time for this node
            long nodeStartTime = System.nanoTime();

            for (String neighbor : graph.getOrDefault(current, new ArrayList<>())) {
                if (!visited.contains(neighbor)) {
                    queue.add(neighbor);
                    visited.add(neighbor);
                    parent.put(neighbor, current);

                    // Calculate the path back to N_0
                    List<String> path = new ArrayList<>();
                    String temp = neighbor;
                    while (temp != null) {
                        path.add(temp);
                        temp = parent.get(temp);
                    }
                    Collections.reverse(path);

                    // Record time taken for this node in microseconds
                    long timeTaken = (System.nanoTime() - nodeStartTime) / 1000;

                    // Save results for this node
                    results.put(neighbor, new Result(nodesVisited, path, timeTaken));
                }
            }
        }

        // Add the start node with its total time taken
        long totalTime = (System.nanoTime() - traversalStart) / 1000;
        results.put(startNode, new Result(1, Arrays.asList(startNode), totalTime));

        return results;
    }

    public static void main(String[] args) {
        // Create the graph
        GraphBFS graphBFS = new GraphBFS();

        // Define edges as per the graph in the image
        graphBFS.addEdge("N_0", "N_1");
        graphBFS.addEdge("N_1", "N_2");
        graphBFS.addEdge("N_2", "N_3");
        graphBFS.addEdge("N_1", "N_6");
        graphBFS.addEdge("N_6", "N_5");
        graphBFS.addEdge("N_5", "N_10");
        graphBFS.addEdge("N_10", "N_11");
        graphBFS.addEdge("N_11", "N_16");
        graphBFS.addEdge("N_6", "N_15");
        graphBFS.addEdge("N_15", "N_20");
        graphBFS.addEdge("N_20", "N_21");
        graphBFS.addEdge("N_6", "N_7");
        graphBFS.addEdge("N_7", "N_12");
        graphBFS.addEdge("N_12", "N_17");
        graphBFS.addEdge("N_17", "N_22");
        graphBFS.addEdge("N_22", "N_23");
        graphBFS.addEdge("N_12", "N_18");
        graphBFS.addEdge("N_18", "N_19");
        graphBFS.addEdge("N_19", "N_24");
        graphBFS.addEdge("N_12", "N_13");
        graphBFS.addEdge("N_13", "N_14");
        graphBFS.addEdge("N_13", "N_8");
        graphBFS.addEdge("N_8", "N_9");
        graphBFS.addEdge("N_9", "N_4");

        // Compute distances and their computation times from the starting node N_0
        Map<String, Result> results = graphBFS.calculateDistances("N_0");

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
