
// Function to calculate n choose k (binomial coefficient)
int nChooseK(int n, int k) {
    if (k > n) {
        return 0;
    }
    if (k == 0 || k == n) {
        return 1;
    }
    int result = 1;
    for (int i = 1; i <= k; i++) {
        result *= (n - i + 1);
        result /= i;
    }
    return result;
}

void printVec(const std::vector<int>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

void printVec(const std::vector<double>& vec) {
    for (const auto& element : vec) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}
