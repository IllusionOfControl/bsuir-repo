package org.example;

import java.util.List;
import java.util.function.ToDoubleFunction;

public class MetricUtils {
    private static double getAvg(List<Metric> metrics, ToDoubleFunction<Metric> mapper) {
        return metrics.stream()
                .mapToDouble(mapper)
                .average()
                .orElse(0);
    }

    private static double getDispersionAvg(List<Metric> metrics, int numberOfSimulations, double avg, ToDoubleFunction<Metric> mapper) {
        return metrics.stream()
                .mapToDouble(m -> Math.pow(avg - mapper.applyAsDouble(m), 2))
                .sum() / (numberOfSimulations - 1);
    }

    private static double getShared(List<Metric> metrics, ToDoubleFunction<Metric> mapper) {
        return metrics.stream()
                .mapToDouble(mapper)
                .sum();
    }

    public static Metric processSharedMetric(List<Metric> metrics) {
        return new Metric(
                getShared(metrics, Metric::getInputTasks),
                getShared(metrics, Metric::getProcessedTasks),
                getShared(metrics, Metric::getMissedTasks),
                getShared(metrics, Metric::getLeavedTasks),
                getShared(metrics, Metric::getDowntime),
                getShared(metrics, Metric::getProbabilityOfProcessing),
                getShared(metrics, Metric::getProbabilityOfFailure)
        );
    }

    public static Metric processSampleAvgMetric(List<Metric> metrics) {
        return new Metric(
                getAvg(metrics, Metric::getInputTasks),
                getAvg(metrics, Metric::getProcessedTasks),
                getAvg(metrics, Metric::getMissedTasks),
                getAvg(metrics, Metric::getLeavedTasks),
                getAvg(metrics, Metric::getDowntime),
                getAvg(metrics, Metric::getProbabilityOfProcessing),
                getAvg(metrics, Metric::getProbabilityOfFailure)
        );
    }

    public static Metric processDisperionAvgMetric(List<Metric> metrics, int numberOfSimulations) {
        var sampleAvgMetric = processSampleAvgMetric(metrics);

        return new Metric(
                getDispersionAvg(metrics, numberOfSimulations, sampleAvgMetric.getInputTasks(), Metric::getInputTasks),
                getDispersionAvg(metrics, numberOfSimulations, sampleAvgMetric.getProcessedTasks(), Metric::getProcessedTasks),
                getDispersionAvg(metrics, numberOfSimulations, sampleAvgMetric.getMissedTasks(), Metric::getMissedTasks),
                getDispersionAvg(metrics, numberOfSimulations, sampleAvgMetric.getLeavedTasks(), Metric::getLeavedTasks),
                getDispersionAvg(metrics, numberOfSimulations, sampleAvgMetric.getDowntime(), Metric::getDowntime),
                getDispersionAvg(metrics, numberOfSimulations, sampleAvgMetric.getProbabilityOfProcessing(), Metric::getProbabilityOfProcessing),
                getDispersionAvg(metrics, numberOfSimulations, sampleAvgMetric.getProbabilityOfFailure(), Metric::getProbabilityOfFailure)
        );
    }
}
