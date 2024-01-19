package org.example.events.comparators;

import org.example.events.Event;

import java.util.Comparator;

public class EventTimeComparator implements Comparator<Event> {

    @Override
    public int compare(Event event1, Event event2) {
        return Double.compare(event2.getTime(), event1.getTime());
    }
}
