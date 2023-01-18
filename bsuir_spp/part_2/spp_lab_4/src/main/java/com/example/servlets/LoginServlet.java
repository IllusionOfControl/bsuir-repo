package com.example.servlets;

import com.example.entities.Data;
import com.example.entities.Doctor;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class LoginServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        String login = req.getParameter("name");
        String password = req.getParameter("password");
        for (Doctor doctor : Data.doctorList) {
            if (doctor.getOrderName().equals(login) && doctor.getPassword().equals(password)) {
                Data.order = doctor;
                resp.getWriter().write("{}");
                return;
            }
        }
        Data.order = null;
        throw new ServletException();
    }

    @Override
    protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
        getServletContext().getRequestDispatcher("/index.jsp").forward(req, resp);
    }
}
