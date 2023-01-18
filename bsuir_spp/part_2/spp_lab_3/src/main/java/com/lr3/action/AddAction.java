package main.java.com.lr3.action;

import com.opensymphony.xwork2.Action;
import main.java.com.lr3.entity.ToDoItem;
import main.java.com.lr3.entity.ToDoItemHolder;

public class AddAction implements Action {

    private String name;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    @Override
    public String execute() throws Exception {
        ToDoItemHolder.currentItems.add(new ToDoItem(name));
        return SUCCESS;
    }

}
