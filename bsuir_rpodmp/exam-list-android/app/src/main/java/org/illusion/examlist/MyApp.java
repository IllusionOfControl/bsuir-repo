package org.illusion.examlist;

import android.app.Application;

public class MyApp extends Application {
    @Override
    public void onCreate() {
        super.onCreate();

        ExamCollection examCollection = ExamCollection.getInstance();
        examCollection.loadExams(this);
    }
}
