package org.illusion.examlist;

import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.widget.TextView;

public class ExamDetailsActivity extends AppCompatActivity {

    private TextView titleTextView;
    private TextView subjectTextView;
    private TextView markTextView;
    private TextView examinerTextView;
    private TextView semesterTextView;
    private TextView locationTextView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_exam_details);

        titleTextView = findViewById(R.id.titleTextView);
        subjectTextView = findViewById(R.id.subjectTextView);
        markTextView = findViewById(R.id.markTextView);
        examinerTextView = findViewById(R.id.examinerTextView);
        semesterTextView = findViewById(R.id.semesterTextView);
        locationTextView = findViewById(R.id.locationTextView);

        String title = getIntent().getStringExtra("title");
        String subject = getIntent().getStringExtra("subject");
        String mark = getIntent().getStringExtra("mark");
        String examiner = getIntent().getStringExtra("examiner");
        String semester = getIntent().getStringExtra("semester");
        String location = getIntent().getStringExtra("location");

        titleTextView.setText("Title: " + title);
        subjectTextView.setText("Subject: " + subject);
        markTextView.setText("Mark: " + mark);
        examinerTextView.setText("Examiner: " + examiner);
        semesterTextView.setText("Semester: " + semester);
        locationTextView.setText("Location: " + location);
    }
}