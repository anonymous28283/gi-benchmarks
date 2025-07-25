long getSum(int* nums, int numsSize, int divizor){
    long result = 0;
    for (int i = 0; i < numsSize; i++){
        int value = nums[i] / divizor;
        if (value * divizor != nums[i]){
            value++;
        }

        result += value;
    }

    return result;
}




int smallestDivisor(int* nums, int numsSize, int threshold){
    int maxNum = 0;
    for (int i = 0; i < numsSize; i++){
        maxNum = max(maxNum, nums[i]);
    }

    int left = 1;
    int right = maxNum;
    while (left <= right){
        int middle = (left + right) / 2;
        long middleSum = getSum(nums, numsSize, middle);
        if (middleSum <= threshold && (middle == 1 || getSum(nums, numsSize, middle - 1) > threshold)){
            return middle;
        }

        if (middleSum > threshold){
            left = middle + 1;
        }
        else{
            right = middle - 1;
        }
    }

    return -1;
}
