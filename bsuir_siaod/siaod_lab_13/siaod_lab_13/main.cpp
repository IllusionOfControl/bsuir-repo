#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>


#define RUN_DEMONSTRATION


// подсчёт цифр в числе
int NumberOfDigits(int n) {
    std::ostringstream strs;

    strs << n;
    return strs.str().size();
}


// красивый вывод матрицы
void PrintMatrix(const std::vector<std::vector<int>>* matrix) {
    int matrix_size = matrix->size();
    std::vector<int> max_len_per_column(matrix_size);

    for (int i = 0; i < matrix_size; i++) {
        int max_len = 0;

        for (int j = 0; j < matrix_size; j++) {
            int num_length = NumberOfDigits((*matrix)[j][i]);
            if (num_length > max_len)
                max_len = num_length;
        }

        max_len_per_column[i] = max_len;
    }

    for (int i = 0; i < matrix_size; ++i)
        for (int j = 0; j < matrix_size; ++j)
            std::cout << (j == 0 ? "\n| " : "") << std::setw(max_len_per_column[j])
            << (*matrix)[i][j] << (j == matrix_size - 1 ? " |" : " ");

    std::cout << std::endl;
}


void AddVertex(std::vector<std::vector<std::pair<int, int>>>* graph, int id_source, int id_target, int length) {
#ifdef RUN_DEMONSTRATION
    printf("Adding vertex [%d, %d, %d]\n", id_source, id_target, length);
#endif
    (*graph)[id_source - 1].push_back(std::make_pair(id_target - 1, length));
    // (*graph)[id_target - 1].push_back(std::make_pair(id_target - 1, length));
}


std::vector<std::vector<int>> DoFloyd(std::vector<std::vector<std::pair<int, int>>>* graph) {
    // число вершин в графе 
    int vertex_count = graph->size();
    int const matrix_width = vertex_count;

    std::vector<std::vector<int>> matrix(matrix_width, std::vector<int>(matrix_width, INT_MAX));


    // перевод дерева графа в матрицу
    for (int index = 0; index < vertex_count; index++) {
        for (std::pair<int, int> edge : (*graph)[index]) {
            matrix[index][edge.first] = edge.second;
        }
    }

    // зануляем matrix[i,i]
    for (int index = 0; index < vertex_count; index++) {
        matrix[index][index] = 0;
    }

    // вычисляем расстояния
    for (int k = 0; k < matrix_width; k++)
        for (int i = 0; i < matrix_width; i++)
            for (int j = 0; j < matrix_width; j++)
                if (matrix[i][j] > (matrix[i][k] + matrix[k][j])
                    && (matrix[k][j] != INT_MAX && matrix[i][k] != INT_MAX))
                    matrix[i][j] = matrix[i][k] + matrix[k][j];

    // максимальные значения приводим к 0
    for (int index_r = 0; index_r < vertex_count; index_r++) {
        for (int index_c = 0; index_c < vertex_count; index_c++) {
            if (matrix[index_r][index_c] == INT_MAX)
                matrix[index_r][index_c] = 0;
        }
    }

    return matrix;

}

/*
    | 1| 2| 3| 4| 5| 6| 7| 8| 9|
    |--|--|--|--|--|--|--|--|--|
   1|  | 3|  |  |  |  |  |  |19|
   2|  |  |  |  | 3|  |  |  |  |
   3|  |  |  |  | 2|  |  |  |  |
   4| 2|  |  |  |  |  |  | 6|  |
   5|  |  |  | 3|  |  |  |  |  |
   6|  |  | 1|  |  |  |  |  |25|
   7|10|  |  |  |  |  |  |  |  |
   8|  |  |  |  | 4| 5|  |  |  |
   9|  |  |  |  |  |  |10|  |  |
*/


int main() {
#ifdef RUN_DEMONSTRATION
    std::cout << "!DEMONSTRATION MODE! \n " << std::endl;
    std::vector<std::vector<std::pair<int, int>>> graph_tree(
        9, std::vector<std::pair<int, int>>());
    AddVertex(&graph_tree, 1, 2, 3);
    AddVertex(&graph_tree, 1, 9, 19);
    AddVertex(&graph_tree, 2, 5, 3);
    AddVertex(&graph_tree, 3, 5, 2);
    AddVertex(&graph_tree, 4, 1, 2);
    AddVertex(&graph_tree, 4, 8, 6);
    AddVertex(&graph_tree, 5, 4, 3);
    AddVertex(&graph_tree, 6, 3, 1);
    AddVertex(&graph_tree, 6, 9, 25);
    AddVertex(&graph_tree, 7, 1, 10);
    AddVertex(&graph_tree, 8, 5, 4);
    AddVertex(&graph_tree, 8, 6, 5);
    AddVertex(&graph_tree, 9, 7, 10);

    std::cout << "\n========\n" << std::endl;
    std::cout << "Floyd matrix:" << std::endl;
    std::vector<std::vector<int>> matrix = DoFloyd(&graph_tree);
    PrintMatrix(&matrix);

#else
    int vertices = 0;
    int edges = int();
    std::cout << "Enter the number of vertices : ";
    std::cin >> vertices;
    std::cout << "Enter the number of edges : ";
    std::cin >> edges;

    std::vector<std::vector<std::pair<int, int>>> graph(
        vertices, std::vector<std::pair<int, int>>());

    // ввод графа
    std::cout << "Enter the vertices in the format : \n"
        << "<vertex_source> <vertex_target> <lenght>" << std::endl;
    int id_source = int(), id_target = int(), length = int();
    while (edges--) {   
        std::cin >> id_source >> id_target >> length;
        AddVertex(&graph, id_source, id_target, length);
    }

    int source = int(), target = int();
    std::cout << "Enter the source and target vertex in the format : \n"
        << "<vertex_source> <vertex_target>" << std::endl;
    std::cin >> source >> target;

    int dist = DoDijkstra(&graph, source, target);
    if (dist == -1) {
        std::cout << "Target not reachable from source" << std::endl;
    }
    else {
        std::cout << "Shortest Path Distance : " << dist << std::endl;
    }
#endif // RUN_DEMONSTRATION
    return 0;
}