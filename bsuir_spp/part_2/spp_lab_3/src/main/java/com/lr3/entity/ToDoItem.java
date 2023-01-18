package main.java.com.lr3.entity;

import java.util.Date;
import java.util.UUID;

public class ToDoItem {

   public UUID id;

   public String name;

   public Date created;
   public Boolean checked;

   public ToDoItem(String name) {
      this.id = UUID.randomUUID();
      this.name = name;
      this.created = new Date();
      this.checked = false;
   }

   public ToDoItem(UUID id, Date created, String name, Boolean checked) {
      this.id = id;
      this.created = created;
      this.name = name;
      this.checked = checked;
   }

   @Override
   public String toString() {
      return "id=" + id +
              ", created=" + created +
              ", name='" + name + '\'' +
              ", checked=" + checked;
   }
}
