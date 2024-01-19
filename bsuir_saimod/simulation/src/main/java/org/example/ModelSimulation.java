package org.example;

import org.example.events.Event;
import org.example.events.EventStack;
import org.example.events.EventType;

public class ModelSimulation {
    private Memory memory;
    private EventStack eventStack;
    private Metric metric;
    private double currentTime;
    private Event lastEvent;
    ModelSimulationConfig config;

    private boolean isBusy;
    private boolean isFinished;

    public ModelSimulation(ModelSimulationConfig config) {
        this.config = config;
    }

    public void generateEvent(EventType type) {
        switch (type) {
            case ACCEPT_FIRST_TASK -> eventStack.addEvent(new Event(currentTime, EventType.ACCEPT_FIRST_TASK));
            case ACCEPT_NEW_TASK -> {
                var randomInterval = new RandomExp(config.acceptTaskInterval).getNext();
                eventStack.addEvent(new Event(currentTime + randomInterval, EventType.ACCEPT_NEW_TASK));
            }
            case FINISH_PROCESS_TASK -> {
                var randomInterval = new RandomExp(config.finishTaskInterval).getNext();
                eventStack.addEvent(new Event(currentTime + randomInterval, EventType.FINISH_PROCESS_TASK));
            }
            case FINISH_MODELLING -> {
                eventStack.addEvent(new Event(config.maxModellingTime, EventType.FINISH_MODELLING));
            }
        }
    }

    private void resetSimulation() {
        this.memory = new Memory(config.memorySize);
        this.eventStack = new EventStack();
        this.metric = new Metric();
        this.currentTime = 0;
        this.isBusy = false;
        this.isFinished = false;
    }

    private void processEvents() {
        Event event = eventStack.getNextEvent();

        switch (event.getEventType()) {
            case ACCEPT_FIRST_TASK -> {
                generateEvent(EventType.ACCEPT_NEW_TASK);
            }
            case ACCEPT_NEW_TASK -> {
                metric.incInputTasks();
                if (!memory.push()) {
                    metric.incMissedTasks();
                    return;
                }

                currentTime = event.getTime();
                generateEvent(EventType.ACCEPT_NEW_TASK);

                if (!isBusy) {
                    var delta = currentTime - lastEvent.getTime();
                    metric.incDowntime(delta);
                    isBusy = true;
                    generateEvent(EventType.FINISH_PROCESS_TASK);
                }
            }
            case FINISH_PROCESS_TASK -> {
                metric.incProcessedTasks();
                memory.pop();
                currentTime = event.getTime();

                if (memory.isEmpty()) {
                    isBusy = false;
                } else {
                    generateEvent(EventType.FINISH_PROCESS_TASK);
                }
            }
            case FINISH_MODELLING -> {
                if (isBusy) {
                    memory.pop();
                    metric.incProcessedTasks();
                    while (memory.pop()) {
                        metric.incLeavedTasks();
                    }
                }
                isBusy = false;
                isFinished = true;
            }
        }
        lastEvent = event;
    }

    public Metric simulate() {
        resetSimulation();

        generateEvent(EventType.ACCEPT_FIRST_TASK);
        generateEvent(EventType.FINISH_MODELLING);

        while (!isFinished) processEvents();
        return metric;
    }
}
