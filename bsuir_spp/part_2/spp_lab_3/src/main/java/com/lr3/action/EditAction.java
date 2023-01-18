package main.java.com.lr3.action;

import com.opensymphony.xwork2.Action;
import main.java.com.lr3.entity.ToDoItem;
import main.java.com.lr3.entity.ToDoItemHolder;

import java.util.UUID;

public class EditAction implements Action {

    private UUID id;
    private String name;
    private Boolean done;

    public UUID getId() {
        return id;
    }

    public void setId(String id) {
        if (id != null) {
            this.id = UUID.fromString(id);
        }
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public Boolean getDone() {
        return done;
    }

    public void setDone(Boolean done) {
        this.done = done;
    }

    @Override
    public String execute() throws Exception {
        String result = ERROR;
        if (id != null) {
            for (ToDoItem currentItem : ToDoItemHolder.currentItems) {
                if (currentItem.id.equals(id)) {
                    currentItem.checked = done;
                    currentItem.name = name;
                    result = SUCCESS;
                    break;
                }
            }
        }
        return result;
    }
}
