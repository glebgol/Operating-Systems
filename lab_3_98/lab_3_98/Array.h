struct Array {
    int size;
    int* Arr;
};

bool allZero(const int* threads, int emount)
{
    for (size_t i = 0; i < emount; i++)
    {
        if (threads[i] == 1)
        {
            return false;
        }
    }
    return true;
}
