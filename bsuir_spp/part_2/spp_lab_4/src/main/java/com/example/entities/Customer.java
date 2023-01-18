package com.example.entities;

import java.util.UUID;

public class Customer {

    private String id;
    private String name;

    public Customer(String name) {
        id = UUID.randomUUID().toString();
        this.name = name;
    }

    public String getId() {
        return id;
    }

    public String getName() {
        return name;
    }
}
