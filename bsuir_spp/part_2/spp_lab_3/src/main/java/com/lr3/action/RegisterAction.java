package main.java.com.lr3.action;

import com.opensymphony.xwork2.Action;
import main.java.com.lr3.entity.UserEntity;
import main.java.com.lr3.entity.UserHolder;

public class RegisterAction implements Action {

    private String name;
    private String password;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    @Override
    public String execute() throws Exception {
        UserHolder.currentUsers.add(new UserEntity(name, password));
        return "SUCCESS";
    }

}
