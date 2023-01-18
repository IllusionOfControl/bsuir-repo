package com.example.entities;

import java.util.ArrayList;
import java.util.List;
import java.util.UUID;

public class Doctor {

    private String id;
    private String userName;
    private String password;
    private List<Visit> visitList;

    public Doctor(String userName, String password) {
        id = UUID.randomUUID().toString();
        this.userName = userName;
        this.password = password;
        visitList = new ArrayList<Visit>();
    }

    public String getId() {
        return id;
    }

    public String getPassword() {
        return password;
    }

    public String getOrderName() {
        return userName;
    }

    public List<Visit> getVisitList() {
        return visitList;
    }

    public void addVisit(Visit visit) {
        visitList.add(visit);
    }

    public void removeVisit(String visitId) {
        for (int i = 0; i < visitList.size(); i++) {
            if (visitList.get(i).getId().equals(visitId)) {
                visitList.remove(visitList.get(i));
                break;
            }
        }
    }
}
