package main.java.com.lr3.action;

import com.opensymphony.xwork2.Action;
import main.java.com.lr3.entity.ToDoItem;
import main.java.com.lr3.entity.ToDoItemHolder;

import java.util.UUID;

public class DeleteAction implements Action {

    private UUID id;

    public UUID getId() {
        return id;
    }

    public void setId(String id) {
        if (id != null) {
            this.id = UUID.fromString(id);
        }
    }

    @Override
    public String execute() throws Exception {
        if (id != null) {
            ToDoItem item = null;
            for (ToDoItem currentItem : ToDoItemHolder.currentItems) {
                if (currentItem.id.equals(id)) {
                    item = currentItem;
                    break;
                }
            }
            if (item != null) {
                ToDoItemHolder.currentItems.remove(item);
            }
        }
        return SUCCESS;
    }
}
