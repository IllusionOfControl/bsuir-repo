package org.illusion.examlist;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import androidx.appcompat.app.AppCompatActivity;

public class CreateExamFirstActivity extends AppCompatActivity {
    private static final int REQUEST_CODE_SECOND_ACTIVITY = 1;
    private EditText titleEditText;
    private EditText subjectEditText;
    private EditText markEditText;
    private Button nextButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_create_exam_first);

        titleEditText = findViewById(R.id.titleEditText);
        subjectEditText = findViewById(R.id.subjectEditText);
        markEditText = findViewById(R.id.markEditText);
        nextButton = findViewById(R.id.nextButton);

        nextButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String title = titleEditText.getText().toString();
                String subject = subjectEditText.getText().toString();
                String mark = markEditText.getText().toString();

                Intent intent = new Intent(CreateExamFirstActivity.this, CreateExamSecondActivity.class);
                intent.putExtra("title", title);
                intent.putExtra("subject", subject);
                intent.putExtra("mark", mark);
                startActivityForResult(intent, REQUEST_CODE_SECOND_ACTIVITY);
            }
        });
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_CODE_SECOND_ACTIVITY && resultCode == RESULT_OK) {
            titleEditText.setText(data.getStringExtra("title"));
            subjectEditText.setText(data.getStringExtra("subject"));
        }
    }
}


