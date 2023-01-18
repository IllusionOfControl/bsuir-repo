package main.java.com.lr3.action;

import com.opensymphony.xwork2.Action;
import main.java.com.lr3.entity.UserEntity;
import main.java.com.lr3.entity.UserHolder;

public class LoginAction implements Action {

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

		UserEntity user = new UserEntity(name, password);
		String result = null;

		for (UserEntity currentUser : UserHolder.currentUsers) {
			if (currentUser.equals(user)) {
				result = "SUCCESS";
				break;
			}
		}
		if (result == null) {
			result = "ERROR";
		}
		return result;
	}
	
}
