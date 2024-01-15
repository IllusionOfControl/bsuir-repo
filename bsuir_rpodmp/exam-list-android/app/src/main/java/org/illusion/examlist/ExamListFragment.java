package org.illusion.examlist;

import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.res.Configuration;
import android.os.Bundle;

import androidx.appcompat.app.AlertDialog;
import androidx.appcompat.app.AppCompatActivity;
import androidx.appcompat.widget.Toolbar;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentManager;
import androidx.fragment.app.FragmentTransaction;
import androidx.recyclerview.widget.RecyclerView;

import android.view.ContextMenu;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.Button;
import android.widget.Toast;


public class ExamListFragment extends Fragment {
    private Toolbar toolbar;
    private RecyclerView recyclerView;
    private ExamCollection examCollection = ExamCollection.getInstance();
    private ExamAdapter examAdapter;
    private IOnExamSelectListener listener;

    public ExamListFragment() {
        // Required empty public constructor
    }

    public static ExamListFragment newInstance() {
        ExamListFragment fragment = new ExamListFragment();
        return fragment;
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
    }

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View view = inflater.inflate(R.layout.fragment_exam_list, container, false);

        recyclerView = view.findViewById(R.id.examList);

        IOnExamClickListener examClickListener = new IOnExamClickListener() {
            @Override
            public void onExamClick(Exam exam) {
                int index = ExamCollection.getInstance().getIndex(exam);
                listener.onPizzaItemSelected(index);
            }
        };

        examAdapter = new ExamAdapter(view.getContext(), examCollection.toList(), examClickListener);
        recyclerView.setAdapter(examAdapter);

        toolbar = view.findViewById(R.id.toolbar);
        ((AppCompatActivity)getActivity()).setSupportActionBar(toolbar);
        setHasOptionsMenu(true);

        Button createButton = view.findViewById(R.id.createButton);
        createButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                showCreateExamFirstActivity();
            }
        });

        registerForContextMenu(recyclerView);

        return view;
    }

    @Override
    public void onCreateOptionsMenu(Menu menu, MenuInflater inflater) {
        inflater.inflate(R.menu.main_menu, menu);
//        super.onCreateOptionsMenu(menu, inflater);
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        int itemId = item.getItemId();

        if (itemId == R.id.action_about) {
            Intent intent = new Intent(getActivity(), AboutActivity.class);
            startActivity(intent);
            return true;
        }
        if (itemId == R.id.action_export) {
            FileUtil.saveItemListToJson(examCollection.toList(), getContext());
            Toast.makeText(getActivity(), "Saved!", Toast.LENGTH_SHORT).show();
            return true;
        }
        if (itemId == R.id.action_export) {
            showCreateExamFirstActivity();
            return true;
        }
        return super.onOptionsItemSelected(item);
    }


    private void showExamDetailActivity(Exam exam) {
        FragmentManager fm = getActivity().getSupportFragmentManager();
        ExamDetailFragment examDetailFragment = new ExamDetailFragment();
        examDetailFragment.setExam(1);

        fm.beginTransaction()
                .remove(this)
                .commit();
    }

    @Override
    public void onResume() {
        super.onResume();
        recyclerView.getAdapter().notifyDataSetChanged();
    }

    @Override
    public void onCreateContextMenu(ContextMenu menu, View v, ContextMenu.ContextMenuInfo menuInfo) {
        super.onCreateContextMenu(menu, v, menuInfo);

        MenuInflater inflater = getActivity().getMenuInflater();
        inflater.inflate(R.menu.context_menu, menu);
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
        Exam selectedExam = examCollection.toList().get(examAdapter.getPosition());
        if (item.getItemId() == R.id.context_view) {
            int index = ExamCollection.getInstance().getIndex(selectedExam);
            listener.onPizzaItemSelected(index);
        }
        if (item.getItemId() == R.id.context_edit) {
            showExamEditActivity(examAdapter.getPosition());
        }
        if (item.getItemId() == R.id.context_remove) {
            showConfirmationRemoveDialog();
        }

        return true;
    }


    private void showAboutActivity() {
        // Replace AboutActivity.class with your actual About activity
        Intent intent = new Intent(getContext(), AboutActivity.class);
        startActivity(intent);
    }

    private void saveExamData() {
        FileUtil.saveItemListToJson(examCollection.toList(), getContext());
        Toast.makeText(getContext(), "Saved!", Toast.LENGTH_SHORT).show();
    }

    private void showCreateExamFirstActivity() {
        Intent intent = new Intent(getContext(), CreateExamFirstActivity.class);
        startActivity(intent);
    }

    private void showExamEditActivity(int position) {
        Intent intent = new Intent(getContext(), ExamEditActivity.class);
        intent.putExtra("position", position);
        startActivity(intent);
    }

    private void showConfirmationRemoveDialog() {
        AlertDialog.Builder builder = new AlertDialog.Builder(getContext());
        builder.setTitle("Confirm");
        builder.setMessage("Are you sure you want to proceed?");

        builder.setPositiveButton("Yes", new DialogInterface.OnClickListener() {
            @Override
            public void onClick(DialogInterface dialog, int which) {
                Exam selectedExam = examCollection.toList().get(examAdapter.getPosition());
                examCollection.removeExam(selectedExam);
                recyclerView.getAdapter().notifyDataSetChanged();
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

    //--OnItemSelectedListener listener;
    // This event fires 1st, before creation of fragment or any views
    // The onAttach method is called when the Fragment instance is associated with an Activity.
    // This does not mean the Activity is fully initialized.
    @Override
    public void onAttach(Context context) {
        super.onAttach(context);
        if(context instanceof IOnExamSelectListener){      // context instanceof YourActivity
            this.listener = (IOnExamSelectListener) context; // = (YourActivity) context
        } else {
            throw new ClassCastException(context.toString()
                    + " must implement ExamMenuFragment.OnItemSelectedListener");
        }
    }


    // Define the events that the fragment will use to communicate
    public interface OnItemSelectedListener {
        // This can be any number of events to be sent to the activity
        void onPizzaItemSelected(int position);
    }
}