package org.illusion.examlist;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;

import android.content.DialogInterface;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class ExamEditActivity extends AppCompatActivity {
    private EditText titleEditText;
    private EditText subjectEditText;
    private EditText markEditText;
    private EditText examinerEditText;
    private EditText semesterEditText;
    private EditText locationEditText;

    private Button saveButton;
    private Button cancelButton;

    private int position;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_exam_edit_detail);

        position = getIntent().getIntExtra("position", 0);
        Exam exam = ExamCollection.getInstance().toList().get(position);

        examinerEditText = findViewById(R.id.examinerEditText);
        semesterEditText = findViewById(R.id.semesterEditText);
        locationEditText = findViewById(R.id.locationEditText);
        titleEditText = findViewById(R.id.titleEditText);
        subjectEditText = findViewById(R.id.subjectEditText);
        markEditText = findViewById(R.id.markEditText);

        saveButton = findViewById(R.id.saveButton);
        cancelButton = findViewById(R.id.cancelButton);

        examinerEditText.setText(exam.getExaminer());
        semesterEditText.setText(String.valueOf(exam.getSemester()));
        locationEditText.setText(exam.getLocation());
        titleEditText.setText(exam.getTitle());
        subjectEditText.setText(exam.getSubject());
        markEditText.setText(String.valueOf(exam.getMark()));

        saveButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showConfirmationSaveDialog();
            }
        });

        cancelButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(ExamEditActivity.this, MainActivity.class);
                startActivity(intent);
            }
        });
    }

    private void showConfirmationSaveDialog() {
        AlertDialog.Builder builder = new AlertDialog.Builder(this);
        builder.setTitle("Confirm");
        builder.setMessage("Are you sure you want to proceed?");

        builder.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                Exam exam = ExamCollection.getInstance().toList().get(position);
                exam.setTitle(titleEditText.getText().toString());
                exam.setSubject(subjectEditText.getText().toString());
                exam.setExaminer(examinerEditText.getText().toString());
                exam.setSemester(Integer.parseInt(semesterEditText.getText().toString()));
                exam.setMark(Integer.parseInt(markEditText.getText().toString()));
                exam.setLocation(locationEditText.getText().toString());

                Intent intent = new Intent(ExamEditActivity.this, MainActivity.class);
                startActivity(intent);
            }
        });

        builder.setNegativeButton("No", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                // Handle the negative button click (e.g., cancel the chosen action)
                // ...
            }
        });

        AlertDialog dialog = builder.create();
        dialog.show();
    }
}