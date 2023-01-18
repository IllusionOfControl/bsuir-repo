package main.java.com.lr3.action;

import com.opensymphony.xwork2.ActionSupport;
import main.java.com.lr3.entity.ToDoItem;
import main.java.com.lr3.entity.ToDoItemHolder;

import java.util.List;

public class TableAction extends ActionSupport {

    public List<ToDoItem> items = ToDoItemHolder.currentItems;

    @Override
    public String execute() throws Exception {
        return SUCCESS;
    }
}
