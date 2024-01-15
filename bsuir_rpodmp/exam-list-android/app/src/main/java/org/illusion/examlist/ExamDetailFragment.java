package org.illusion.examlist;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

/**
 * A simple {@link Fragment} subclass.
 * Use the {@link ExamDetailFragment#newInstance} factory method to
 * create an instance of this fragment.
 */
public class ExamDetailFragment extends Fragment {
    private int examId;

    public void setExam(int examId) {
        this.examId = examId;
    }

    public ExamDetailFragment() {
        // Required empty public constructor
    }

    public static ExamDetailFragment newInstance(String param1, String param2) {
        ExamDetailFragment fragment = new ExamDetailFragment();
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if(savedInstanceState == null){
            // Get back arguments
            if(getArguments() != null) {
                examId = getArguments().getInt("position", 0);
            }
        }
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {

        return inflater.inflate(R.layout.fragment_exam_detail, container, false);
    }

    @Override
    public void onStart() {
        super.onStart();
        View view = getView();
        if (view != null) {
            // TODO установка полей
            Exam exam = ExamCollection.getInstance().toList().get(examId);
            TextView titleTextView = (TextView) view.findViewById(R.id.titleTextView);
            TextView subjectTextView = (TextView) view.findViewById(R.id.subjectTextView);
            TextView locationTextView = (TextView) view.findViewById(R.id.locationTextView);
            TextView examinerTextView = (TextView) view.findViewById(R.id.examinerTextView);
            TextView markTextView = (TextView) view.findViewById(R.id.markTextView);
            TextView semesterTextView = (TextView) view.findViewById(R.id.semesterTextView);

            titleTextView.setText(exam.getTitle());
            subjectTextView.setText(exam.getSubject());
            locationTextView.setText(exam.getLocation());
            examinerTextView.setText(exam.getExaminer());
            markTextView.setText(String.valueOf(exam.getMark()));
            semesterTextView.setText(String.valueOf(exam.getSemester()));
        }
    }
}