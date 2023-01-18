package com.example.entities;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.UUID;

public class Visit {
    private final String id;
    private final Date date;
    private final String description;
    private final Customer customer;

    public Visit(String description, Customer customer) {
        id = UUID.randomUUID().toString();
        date = new Date();
        this.description = description;
        this.customer = customer;
    }

    public String getId() {
        return id;
    }

    public Date getDate() {
        return date;
    }

    public String getDescription() {
        return description;
    }

    public String getOrderName() {
        return customer.getName();
    }

    public String getDisplayDate() {
        DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
        return dateFormat.format(date);
    }
}
