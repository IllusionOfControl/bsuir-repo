package org.illusion.examlist;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

public class CreateExamThirdActivity extends AppCompatActivity {

    private TextView titleTextView;
    private TextView subjectTextView;
    private TextView markTextView;
    private TextView examinerTextView;
    private TextView semesterTextView;
    private TextView locationTextView;

    private Button saveButton;
    private Button cancelButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create_exam_third);

        titleTextView = findViewById(R.id.titleTextView);
        subjectTextView = findViewById(R.id.subjectTextView);
        markTextView = findViewById(R.id.markTextView);
        examinerTextView = findViewById(R.id.examinerTextView);
        semesterTextView = findViewById(R.id.semesterTextView);
        locationTextView = findViewById(R.id.locationTextView);

        saveButton = findViewById(R.id.saveButton);
        cancelButton = findViewById(R.id.cancelButton);

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

        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                // Save the values to an object and collection
                // For example:
                Exam exam = new Exam(title,subject, examiner, Integer.parseInt(mark), Integer.parseInt(semester), location);
                ExamCollection.getInstance().addExam(exam);

                Intent intent = new Intent(CreateExamThirdActivity.this, MainActivity.class);
                startActivity(intent);
            }
        });

        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(CreateExamThirdActivity.this, MainActivity.class);
                startActivity(intent);
            }
        });
    }
}