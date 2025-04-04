bool check(int x) {
    return true;
}

int binarySearch(int l, int r, int goal) {
    int ret = -1;
    while (l <= r) {
        int mid = l + ((r - l) >> 1);
        if (check(mid)) {
            ret = mid, r = mid - 1;
            // ret = mid, l = mid + 1;
        } else {
            l = mid + 1;
            // r = mid - 1;
        }
    }
    return ret;
}