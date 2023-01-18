package com.example.entities;

import java.util.ArrayList;
import java.util.List;

public class Data {
    public static List<Customer> customerList = new ArrayList<Customer>();

    static {
        customerList.add(new Customer("Сustomer1"));
        customerList.add(new Customer("Сustomer2"));
        customerList.add(new Customer("Сustomer3"));
    }

    public static List<Doctor> doctorList = new ArrayList<Doctor>();
    public static Doctor order = null;

    public static List<Visit> getVisitList() {
        if (order == null) return new ArrayList<Visit>();
        else return order.getVisitList();
    }
}

