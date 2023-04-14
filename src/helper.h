

bool containsInt(int hey[], int needle ) { 
    int n = sizeof(hey) / sizeof(hey[0]);
    for (int i=0; i <= n;i++) {
        Serial.printf("i=%d, hey=%d, needle=%d, n=%d\n", i, hey[i], needle,n);
        if (hey[i] == needle) return true;
    }
    return false;
};