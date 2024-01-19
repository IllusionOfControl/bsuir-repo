package org.example;

import java.util.ArrayList;
import java.util.List;

public class Main {
    private static final int numberOfSimulations = 100;


    public static void main(String[] args) {
        ModelSimulationConfig config = new ModelSimulationConfig();
        ModelSimulation model = new ModelSimulation(config);
        List<Metric> metrics = new ArrayList<>(numberOfSimulations);

        for (int i = 0; i < numberOfSimulations; i++) {
            var metric = model.simulate();
            metrics.add(metric);
        }

        System.out.println("Shared metrics: \n" + MetricUtils.processSharedMetric(metrics));
        System.out.println("Sample Avg metrics: \n" + MetricUtils.processSampleAvgMetric(metrics));
        System.out.println("Dispersion Avg metrics: \n" + MetricUtils.processDisperionAvgMetric(metrics, numberOfSimulations));
    }
}