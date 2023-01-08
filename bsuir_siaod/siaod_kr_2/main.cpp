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


int DoDijkstra(std::vector<std::vector<std::pair<int, int>>>* graph, int id_source, int id_target) {
    // число вершин в графе 
    int vertex_count = graph->size();

    // установка всех дистанций в INT_MAX
    std::vector<int> distances(vertex_count, INT_MAX);

    // создаём кучу, используя приоритетную очередь
    // первый элемент пары содержит дистанцию 
    // второй содержит вершину
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
        std::greater<std::pair<int, int>>> pq;

    // Пушим вершину источника с дистанцией 0 в кучу
    pq.push(std::make_pair(0, id_source - 1));

    // делаем расстояние до источника равное 0
    distances[id_source - 1] = 0;

    while (!pq.empty()) {
        // маркировка расстояния до источника в качестве второго элемента пары обозначает узел / вершину
        int currentNode = pq.top().second;

        // первый элемент пары - расстояние
        int currentDist = pq.top().first;

        pq.pop();

        // для всех достижимых вершин из исследуемой в данный момент вершины
        // пробуем минимизировать расстояние
        for (std::pair<int, int> edge : (*graph)[currentNode]) {
            // находим минимальное расстояние
            if (currentDist + edge.second < distances[edge.first]) {
                distances[edge.first] = currentDist + edge.second;
                pq.push(std::make_pair(distances[edge.first], edge.first));
            }
        }
    }
    if (distances[id_target - 1] != INT_MAX) {
        return distances[id_target - 1];
    }
    return -1;
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


int main() {
#ifdef RUN_DEMONSTRATION
    std::cout << "!DEMONSTRATION MODE! \n " << std::endl;
    std::vector<std::vector<std::pair<int, int>>> graph_tree(
        5, std::vector<std::pair<int, int>>());
    AddVertex(&graph_tree, 1, 2, 4);
    AddVertex(&graph_tree, 1, 3, 2);
    AddVertex(&graph_tree, 2, 3, 2);
    AddVertex(&graph_tree, 3, 2, 1);
    AddVertex(&graph_tree, 2, 4, 2);
    AddVertex(&graph_tree, 3, 5, 4);
    AddVertex(&graph_tree, 5, 4, 1);
    AddVertex(&graph_tree, 2, 5, 3);
    AddVertex(&graph_tree, 3, 4, 4);

    int from = 1, to = 4;
    int short_distance = DoDijkstra(&graph_tree, from, to);

    printf("\nDijkstra short path from %d to %d\n", from, to);

    if (short_distance == -1) {
        std::cout << "Target not reachable from source" << std::endl;
    }
    else {
        std::cout << "Shortest Path Distance : " << short_distance << std::endl;
    }
    std::cout << "\n========\n" << std::endl;
    std::cout << "Floyd matrix: " << short_distance << std::endl;
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