package com.example.spp_lab_1;

import java.io.*;
import javax.servlet.RequestDispatcher;
import javax.servlet.ServletException;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "MovieList", value = "/movies")
public class MovieListServlet extends HttpServlet {
    private String[] movieList;

    public void init() {
        movieList = new String[]{"Hello World!", "Terminator 2", "Avatar", "Naruto"};
    }

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        // создаём обработчик JSTL
        RequestDispatcher view = request.getRequestDispatcher("scratch.jsp");
        // задаём атрибут списка фильмов
        request.setAttribute("movieList", movieList);
        // передаём обработку запроса
        view.forward(request, response);
    }

    public void destroy() {
    }
}
