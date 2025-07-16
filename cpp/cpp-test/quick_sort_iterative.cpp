









namespace sorting {

int partition(std::vector<int> &arr, int start, int end)
{
    int pivot = arr[end];
    int index = start - 1;

    for (int j = start; j < end; j++) {
        if (arr[j] <= pivot) {
            std::swap(arr[++index], arr[j]);
        }
    }

    std::swap(arr[index + 1], arr[end]);
    return index + 1;
}


void iterativeQuickSort(std::vector<int> &arr)
{
    std::stack<int> stack;
    int start = 0;
    int end = arr.size()-1;
    stack.push(start);
    stack.push(end);

    while(!stack.empty())
    {
        end = stack.top();
        stack.pop();
        start = stack.top();
        stack.pop();

        int pivotIndex = partition(arr,start,end);

        if(pivotIndex -1 > start)
        {
            stack.push(start);
            stack.push(pivotIndex-1);
        }

        if(pivotIndex+1<end)
        {
            stack.push(pivotIndex+1);
            stack.push(end);
        }
    }
}

}

void tests()
{

    std::vector<int> case1={100,534,1000000,553,10,61,2000,238,2756,9,12,56,30};
    std::cout<<"TEST 1\n";
    std::cout<<"Before: \n";
    for(auto x : case1) std::cout<<x<<",";
    std::cout<<"\n";
    sorting::iterativeQuickSort(case1);
    assert(std::is_sorted(std::begin(case1),std::end(case1)));
    std::cout<<"Test 1 succesful!\n";
    std::cout<<"After: \n";
    for(auto x : case1) std::cout<<x<<",";
    std::cout<<"\n";


    std::vector<int> case2={-10,-2,-5,-2,-3746,-785,-123, -452, -32456};
    std::cout<<"TEST 2\n";
    std::cout<<"Before: \n";
    for(auto x : case2) std::cout<<x<<",";
    std::cout<<"\n";
    sorting::iterativeQuickSort(case2);
    assert(std::is_sorted(std::begin(case2),std::end(case2)));
    std::cout<<"Test 2 succesful!\n";
    std::cout<<"After: \n";
    for(auto x : case2) std::cout<<x<<",";
    std::cout<<"\n";
}



int main()
{
    tests();
    return 0;
}
