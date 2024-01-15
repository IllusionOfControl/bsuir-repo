package org.illusion.examlist;

import android.content.Context;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class ExamCollection {
    private static ExamCollection instance;
    private List<Exam> exams;

    private ExamCollection() {
        exams = new ArrayList<>();
    }

    public static synchronized ExamCollection getInstance() {
        if (instance == null) {
            instance = new ExamCollection();
        }
        return instance;
    }

    public void loadExams(Context context) {
        exams = FileUtil.loadItemListFromJson(context);
    }

    public void addExam(Exam exam) {
        exams.add(exam);
    }

    public void removeExam(Exam exam) {
        exams.remove(exam);
    }

    public List<Exam> toList() {
        return exams;
    }

    public void sort() {
        Comparator<Exam> examComparator = new Comparator<Exam>() {
            @Override
            public int compare(Exam exam1, Exam exam2) {
                // Compare exams based on their marks
                return Integer.compare(exam2.getMark(), exam1.getMark());
            }
        };

        // Sort the exam list using the custom comparator
        Collections.sort(exams, examComparator);
    }

    public int getIndex(Exam exam) {
        return exams.indexOf(exam);
    }
}