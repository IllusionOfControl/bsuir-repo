package org.illusion.examlist;

import android.content.Context;
import android.content.Intent;

import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class FileUtil {

    public static void saveItemListToJson(List<Exam> itemList, Context context) {
        // Convert the itemList to JSON
        JSONArray jsonArray = new JSONArray();
        for (Exam item : itemList) {
            JSONObject jsonObject = new JSONObject();
            try {
                jsonObject.put("title", item.getTitle());
                jsonObject.put("subject", item.getSubject());
                jsonObject.put("examiner", item.getExaminer());
                jsonObject.put("semester", item.getSemester());
                jsonObject.put("mark", item.getMark());
                jsonObject.put("location", item.getLocation());
                jsonArray.put(jsonObject);
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }
        String jsonString = jsonArray.toString();

        // Get the app's internal storage directory
        File directory = context.getFilesDir();

        // Create the JSON file
        File jsonFile = new File(directory, "items.json");

        // Write the JSON string to the file
        try {
            BufferedWriter writer = new BufferedWriter(new FileWriter(jsonFile));
            writer.write(jsonString);
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static List<Exam> loadItemListFromJson(Context context) {
        List<Exam> itemList = new ArrayList<>();

        // Get the app's internal storage directory
        File directory = context.getFilesDir();

        // Create the JSON file
        File jsonFile = new File(directory, "items.json");

        // Read the contents of the JSON file
        StringBuilder jsonString = new StringBuilder();
        try {
            BufferedReader reader = new BufferedReader(new FileReader(jsonFile));
            String line;
            while ((line = reader.readLine()) != null) {
                jsonString.append(line);
            }
            reader.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

        // Parse the JSON string
        try {
            JSONArray jsonArray = new JSONArray(jsonString.toString());
            for (int i = 0; i < jsonArray.length(); i++) {
                JSONObject jsonObject = jsonArray.getJSONObject(i);

                String title = jsonObject.getString("title");
                String subject = jsonObject.getString("subject");
                String examiner = jsonObject.getString("examiner");
                int semester = jsonObject.getInt("semester");
                int mark = jsonObject.getInt("mark");
                String location = jsonObject.getString("location");

                Exam item = new Exam(title, subject, examiner, semester, mark, location);
                itemList.add(item);
            }
        } catch (JSONException e) {
            e.printStackTrace();
        }

        return itemList;
    }
}
